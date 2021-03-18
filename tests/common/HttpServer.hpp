//
// Copyright (c) 2015-2020 Microsoft Corporation and Contributors.
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include "Common.hpp"
#include "SocketTools.hpp"
#include "Reactor.hpp"

// #define ENABLE_HTTP_DEBUG

#ifdef ENABLE_HTTP_DEBUG
#ifdef  LOG_TRACE
#undef  LOG_TRACE
#define LOG_TRACE(x, ...) printf(x "\n" , __VA_ARGS__)
#endif
#endif

using namespace SocketTools;

namespace testing {

// Simple HTTP server
// Goals:
//   - Support enough of HTTP to be used as a mock
//   - Be flexible to allow creating various test scenarios
// Out of scope:
//   - Performance
//   - Full support of RFC 7230-7237
class HttpServer : private Reactor::Callback
{
  public:
    struct Request {
        std::string client;
        std::string method;
        std::string uri;
        std::string protocol;
        std::map<std::string, std::string> headers;
        std::string content;
    };

    struct Response {
        int code;
        std::string message;
        std::map<std::string, std::string> headers;
        std::string content;
    };

    class Callback {
      public:
        virtual int onHttpRequest(Request const& request, Response& response) = 0;
    };

  protected:
    struct Connection {
        Socket socket;
        std::string receiveBuffer;
        std::string sendBuffer;
        enum { Idle, ReceivingHeaders, Sending100Continue, ReceivingBody, Processing, SendingHeaders, SendingBody, Closing } state;
        size_t contentLength;
        bool keepalive;
        Request request;
        Response response;
    };

  protected:
    std::string m_serverHost;
    bool allowKeepalive { true };
    Reactor m_reactor;
    std::list<Socket> m_listeningSockets;
    std::list<std::pair<std::string, Callback*>> m_handlers;
    std::map<Socket, Connection> m_connections;
    size_t m_maxRequestHeadersSize, m_maxRequestContentSize;

	// Map of killed token to kill duration of that token
	// Ideally we need a map of string --> std::pair<std::string /* suffix */, uint64_t /* duration */
	std::map<std::string, uint64_t> m_killedTokens;

  public:

	void setKilledToken(std::string token, uint64_t duration)
	{
		m_killedTokens[token] = duration;
	};

	void clearKilledTokens()
	{
		m_killedTokens.clear();
	}

    void setKeepalive(bool keepAlive)
    {
        allowKeepalive = keepAlive;
    }

    HttpServer()
      : m_serverHost("unnamed"),
        allowKeepalive(true),
        m_reactor(*this),
        m_maxRequestHeadersSize(8192),
        m_maxRequestContentSize(2 * 1024 * 1024)
    {
    }

    ~HttpServer()
    {
        for (auto& sock : m_listeningSockets) {
            sock.close();
        }
    }

    void setRequestLimits(size_t maxRequestHeadersSize, size_t maxRequestContentSize)
    {
        m_maxRequestHeadersSize = maxRequestHeadersSize;
        m_maxRequestContentSize = maxRequestContentSize;
    }

    void setServerName(std::string const& name)
    {
        m_serverHost = name;
    }

    int addListeningPort(int port)
    {
        Socket socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        socket.setNonBlocking();
        socket.setReuseAddr();

        SocketAddr addr(0, port);
        socket.bind(addr);
        socket.getsockname(addr);

        socket.listen(10);
        m_listeningSockets.push_back(socket);
        m_reactor.addSocket(socket, Reactor::Acceptable);
        LOG_INFO("HttpServer: Listening on %s", addr.toString().c_str());

        return addr.port();
    }

    void addHandler(std::string const& root, Callback& handler)
    {
        m_handlers.push_back(std::make_pair(root, &handler));
        LOG_INFO("HttpServer: Added handler for %s", root.c_str());
    }

    void start()
    {
        m_reactor.start();
    }

    void stop()
    {
        m_reactor.stop();
    }

  protected:
    virtual void onSocketAcceptable(Socket socket) override
    {
        LOG_TRACE("HttpServer: accepting socket fd=0x%x", socket.m_sock);
        assert(std::find(m_listeningSockets.begin(), m_listeningSockets.end(), socket) != m_listeningSockets.end());

        Socket csocket;
        SocketAddr caddr;
        if (socket.accept(csocket, caddr)) {
            csocket.setNonBlocking();
            Connection& conn = m_connections[csocket];
            conn.socket = csocket;
            conn.state = Connection::Idle;
            conn.request.client = caddr.toString();
            m_reactor.addSocket(csocket, Reactor::Readable | Reactor::Closed);
            LOG_TRACE("HttpServer: [%s] accepted", conn.request.client.c_str());
        }
    }

    virtual void onSocketReadable(Socket socket) override
    {
        LOG_TRACE("HttpServer: reading socket fd=0x%x", socket.m_sock);
        assert(std::find(m_listeningSockets.begin(), m_listeningSockets.end(), socket) == m_listeningSockets.end());

        auto connIt = m_connections.find(socket);
        if (connIt == m_connections.end()) {
            return;
        }
        Connection& conn = connIt->second;

        char buffer[2048] = { 0 };
        int received = socket.recv(buffer, sizeof(buffer));
        LOG_TRACE("HttpServer: [%s] received %d", conn.request.client.c_str(), received);
        if (received <= 0) {
            handleConnectionClosed(conn);
            return;
        }
        conn.receiveBuffer.append(buffer, buffer + received);

        handleConnection(conn);
    }

    virtual void onSocketWritable(Socket socket) override
    {
        LOG_TRACE("HttpServer: writing socket fd=0x%x", socket.m_sock);
        assert(std::find(m_listeningSockets.begin(), m_listeningSockets.end(), socket) == m_listeningSockets.end());

        auto connIt = m_connections.find(socket);
        if (connIt == m_connections.end()) {
            return;
        }
        Connection& conn = connIt->second;

        if (!sendMore(conn)) {
            handleConnection(conn);
        }
    }

    virtual void onSocketClosed(Socket socket) override
    {
        LOG_TRACE("HttpServer: closing socket fd=0x%x", socket.m_sock);
        assert(std::find(m_listeningSockets.begin(), m_listeningSockets.end(), socket) == m_listeningSockets.end());

        auto connIt = m_connections.find(socket);
        if (connIt == m_connections.end()) {
            return;
        }
        Connection& conn = connIt->second;

        handleConnectionClosed(conn);
    }

    bool sendMore(Connection& conn)
    {
        if (conn.sendBuffer.empty()) {
            return false;
        }

        int sent = conn.socket.send(conn.sendBuffer.data(), static_cast<int>(conn.sendBuffer.size()));
        LOG_TRACE("HttpServer: [%s] sent %d", conn.request.client.c_str(), sent);
        if (sent < 0 && conn.socket.error() != Socket::ErrorWouldBlock) {
            return true;
        }
        conn.sendBuffer.erase(0, sent);

        if (!conn.sendBuffer.empty()) {
            m_reactor.addSocket(conn.socket, Reactor::Writable | Reactor::Closed);
            return true;
        }

        return false;
    }

  protected:
    void handleConnectionClosed(Connection& conn)
    {
        LOG_TRACE("HttpServer: [%s] closed", conn.request.client.c_str());
        if (conn.state != Connection::Idle && conn.state != Connection::Closing) {
            LOG_WARN("HttpServer: [%s] connection closed unexpectedly", conn.request.client.c_str());
        }
        m_reactor.removeSocket(conn.socket);
        auto connIt = m_connections.find(conn.socket);
        conn.socket.close();
        m_connections.erase(connIt);
    }

    void handleConnection(Connection& conn)
    {
        for (;;) {
            if (conn.state == Connection::Idle) {
                conn.response.code = 0;
                conn.state = Connection::ReceivingHeaders;
                LOG_TRACE("HttpServer: [%s] receiving headers", conn.request.client.c_str());
            }

            if (conn.state == Connection::ReceivingHeaders) {
                bool lfOnly = false;
                size_t ofs = conn.receiveBuffer.find("\r\n\r\n");
                if (ofs == std::string::npos) {
                    lfOnly = true;
                    ofs = conn.receiveBuffer.find("\n\n");
                }
                size_t headersLen = (ofs != std::string::npos) ? ofs : conn.receiveBuffer.length();
                if (headersLen > m_maxRequestHeadersSize) {
                    LOG_WARN("HttpServer: [%s] headers too long - %u", conn.request.client.c_str(), static_cast<unsigned>(headersLen));
                    conn.response.code = 431; // Request Header Fields Too Large
                    conn.keepalive = false;
                    conn.state = Connection::Processing;
                    continue;
                }
                if (ofs == std::string::npos) {
                    return;
                }

                if (!parseHeaders(conn)) {
                    LOG_WARN("HttpServer: [%s] invalid headers", conn.request.client.c_str());
                    conn.response.code = 400; // Bad Request
                    conn.keepalive = false;
                    conn.state = Connection::Processing;
                    continue;
                }
                LOG_INFO("HttpServer: [%s] %s %s %s", conn.request.client.c_str(), conn.request.method.c_str(), conn.request.uri.c_str(), conn.request.protocol.c_str());
                conn.receiveBuffer.erase(0, ofs + (lfOnly ? 2 : 4));

                conn.keepalive = (conn.request.protocol == "HTTP/1.1");
                auto const connection = conn.request.headers.find("Connection");
                if (connection != conn.request.headers.end()) {
                    if (equalsLowercased(connection->second, "keep-alive")) {
                        conn.keepalive = true;
                    } else if (equalsLowercased(connection->second, "close")) {
                        conn.keepalive = false;
                    }
                }

                auto const contentLength = conn.request.headers.find("Content-Length");
                if (contentLength != conn.request.headers.end()) {
                    conn.contentLength = atoi(contentLength->second.c_str());
                } else {
                    conn.contentLength = 0;
                }
                if (conn.contentLength > m_maxRequestContentSize) {
                    LOG_WARN("HttpServer: [%s] content too long - %u", conn.request.client.c_str(), static_cast<unsigned>(conn.contentLength));
                    conn.response.code = 413; // Payload Too Large
                    conn.keepalive = false;
                    conn.state = Connection::Processing;
                    continue;
                }

                auto const expect = conn.request.headers.find("Expect");
                if (expect != conn.request.headers.end() && conn.request.protocol == "HTTP/1.1") {
                    if (!equalsLowercased(expect->second, "100-continue")) {
                        LOG_WARN("HttpServer: [%s] unknown expectation - %s", conn.request.client.c_str(), expect->second.c_str());
                        conn.response.code = 417; // Expectation Failed
                        conn.keepalive = false;
                        conn.state = Connection::Processing;
                        continue;
                    }
                    conn.sendBuffer = "HTTP/1.1 100 Continue\r\n\r\n";
                    conn.state = Connection::Sending100Continue;
                    LOG_TRACE("HttpServer: [%s] sending \"100 Continue\"", conn.request.client.c_str());
                    continue;
                }

                conn.state = Connection::ReceivingBody;
                LOG_TRACE("HttpServer: [%s] receiving body", conn.request.client.c_str());
            }

            if (conn.state == Connection::Sending100Continue) {
                if (sendMore(conn)) {
                    return;
                }

                conn.state = Connection::ReceivingBody;
                LOG_TRACE("HttpServer: [%s] receiving body", conn.request.client.c_str());
            }

            if (conn.state == Connection::ReceivingBody) {
                if (conn.receiveBuffer.length() < conn.contentLength) {
                    return;
                }

                if (conn.receiveBuffer.length() == conn.contentLength) {
                    conn.request.content = std::move(conn.receiveBuffer);
                    conn.receiveBuffer.clear();
                } else {
                    conn.request.content.assign(conn.receiveBuffer, 0, conn.contentLength);
                    conn.receiveBuffer.erase(0, conn.contentLength);
                }

                conn.state = Connection::Processing;
                LOG_TRACE("HttpServer: [%s] processing request", conn.request.client.c_str());
            }

            if (conn.state == Connection::Processing) {
                processRequest(conn);

                std::ostringstream os;
                os << conn.request.protocol << ' ' << conn.response.code << ' ' << conn.response.message << "\r\n";
                for (auto const& header : conn.response.headers) {
                    os << header.first << ": " << header.second << "\r\n";
                }
                os << "\r\n";

                conn.sendBuffer = os.str();
                conn.state = Connection::SendingHeaders;
                LOG_TRACE("HttpServer: [%s] sending headers", conn.request.client.c_str());
            }

            if (conn.state == Connection::SendingHeaders) {
                if (sendMore(conn)) {
                    return;
                }

                conn.sendBuffer = std::move(conn.response.content);
                conn.state = Connection::SendingBody;
                LOG_TRACE("HttpServer: [%s] sending body", conn.request.client.c_str());
            }

            if (conn.state == Connection::SendingBody) {
                if (sendMore(conn)) {
                    return;
                }

                conn.keepalive &= allowKeepalive;

                if (conn.keepalive) {
                    m_reactor.addSocket(conn.socket, Reactor::Readable | Reactor::Closed);
                    conn.state = Connection::Idle;
                    LOG_TRACE("HttpServer: [%s] idle (keep-alive)", conn.request.client.c_str());
                    if (conn.receiveBuffer.empty()) {
                        return;
                    }
                } else {
                    conn.socket.shutdown(Socket::ShutdownSend);
                    m_reactor.addSocket(conn.socket, Reactor::Closed);
                    conn.state = Connection::Closing;
                    LOG_TRACE("HttpServer: [%s] closing", conn.request.client.c_str());
                }
            }

            if (conn.state == Connection::Closing) {
                return;
            }
        }
    }

    bool parseHeaders(Connection& conn)
    {
        // Method
        char const* begin = conn.receiveBuffer.c_str();
        char const* ptr = begin;
        while (*ptr && *ptr != ' ' && *ptr != '\r' && *ptr != '\n') {
            ptr++;
        }
        if (*ptr != ' ') {
            return false;
        }
        conn.request.method.assign(begin, ptr);
        while (*ptr == ' ') {
            ptr++;
        }

        // URI
        begin = ptr;
        while (*ptr && *ptr != ' ' && *ptr != '\r' && *ptr != '\n') {
            ptr++;
        }
        if (*ptr != ' ') {
            return false;
        }
        conn.request.uri.assign(begin, ptr);
        while (*ptr == ' ') {
            ptr++;
        }

        // Protocol
        begin = ptr;
        while (*ptr && *ptr != ' ' && *ptr != '\r' && *ptr != '\n') {
            ptr++;
        }
        if (*ptr != '\r' && *ptr != '\n') {
            return false;
        }
        conn.request.protocol.assign(begin, ptr);
        if (*ptr == '\r') {
            ptr++;
        }
        if (*ptr != '\n') {
            return false;
        }
        ptr++;

        // Headers
        conn.request.headers.clear();
        while (*ptr != '\r' && *ptr != '\n') {
            // Name
            begin = ptr;
            while (*ptr && *ptr != ':' && *ptr != ' ' && *ptr != '\r' && *ptr != '\n') {
                ptr++;
            }
            if (*ptr != ':') {
                return false;
            }
            std::string name = normalizeHeaderName(begin, ptr);
            ptr++;
            while (*ptr == ' ') {
                ptr++;
            }

            // Value
            begin = ptr;
            while (*ptr && *ptr != '\r' && *ptr != '\n') {
                ptr++;
            }
            conn.request.headers[name] = std::string(begin, ptr);
            if (*ptr == '\r') {
                ptr++;
            }
            if (*ptr != '\n') {
                return false;
            }
            ptr++;
        }

        if (*ptr == '\r') {
            ptr++;
        }
        if (*ptr != '\n') {
            return false;
        }
        ptr++;

        return true;
    }

    static bool equalsLowercased(std::string const& str, char const* mask)
    {
        char const* ptr = str.c_str();
        while (*ptr && *mask && ::tolower(*ptr) == *mask) {
            ptr++;
            mask++;
        }
        return !*ptr && !*mask;
    }

    static std::string normalizeHeaderName(char const* begin, char const* end)
    {
        std::string result(begin, end);
        bool first = true;
        for (char& ch : result) {
            if (first) {
                ch = static_cast<char>(::toupper(ch));
                first = false;
            } else if (ch == '-') {
                first = true;
            } else {
                ch = static_cast<char>(::tolower(ch));
            }
        }
        return result;
    }

    void processRequest(Connection& conn)
    {
        conn.response.message.clear();
        conn.response.headers.clear();
        conn.response.content.clear();

        if (conn.response.code == 0) {
            conn.response.code = 404; // Not Found
            for (auto& handler : m_handlers) {
                if (conn.request.uri.length() >= handler.first.length() &&
                    strncmp(conn.request.uri.c_str(), handler.first.c_str(), handler.first.length()) == 0)
                {
                    LOG_TRACE("HttpServer: [%s] using handler for %s", conn.request.client.c_str(), handler.first.c_str());
                    int result = handler.second->onHttpRequest(conn.request, conn.response);
                    if (result != 0) {
                        conn.response.code = result;
                        break;
                    }
                }
            }

            if (conn.response.code == -1) {
                LOG_TRACE("HttpServer: [%s] closing by request", conn.request.client.c_str());
                handleConnectionClosed(conn);
            }
        }

        if (conn.response.message.empty()) {
            conn.response.message = getDefaultResponseMessage(conn.response.code);
        }

        conn.response.headers["Host"] = m_serverHost;
        conn.response.headers["Connection"] = (conn.keepalive ? "keep-alive" : "close");
        conn.response.headers["Date"] = formatTimestamp(time(nullptr));
        conn.response.headers["Content-Length"] = std::to_string(conn.response.content.size());
        int kill_duration = -1;
        for (auto &kv : m_killedTokens)
        {
            std::string val = kv.first;
            val += ":all";
            conn.response.headers.insert(std::pair<std::string, std::string>("kill-tokens", val));
            kill_duration = std::max(kill_duration, (int)kv.second);
        }

        if (m_killedTokens.size() > 0) {
            conn.response.headers.insert(std::pair<std::string, std::string>("kill-duration", std::to_string(kill_duration)));
        }
    }

    static std::string formatTimestamp(time_t time)
    {
        tm tm;
#ifdef _WIN32
        gmtime_s(&tm, &time);
#else
        gmtime_r(&time, &tm);
#endif
        char buf[32];
        strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S GMT", &tm);
        return buf;
    }

    static char const* getDefaultResponseMessage(int code)
    {
        switch (code) {
            // *INDENT-OFF*
            case 100: return "Continue";
            case 101: return "Switching Protocols";
            case 200: return "OK";
            case 201: return "Created";
            case 202: return "Accepted";
            case 203: return "Non-Authoritative Information";
            case 204: return "No Content";
            case 205: return "Reset Content";
            case 206: return "Partial Content";
            case 300: return "Multiple Choices";
            case 301: return "Moved Permanently";
            case 302: return "Found";
            case 303: return "See Other";
            case 304: return "Not Modified";
            case 305: return "Use Proxy";
            case 306: return "Switch Proxy";
            case 307: return "Temporary Redirect";
            case 308: return "Permanent Redirect";
            case 400: return "Bad Request";
            case 401: return "Unauthorized";
            case 402: return "Payment Required";
            case 403: return "Forbidden";
            case 404: return "Not Found";
            case 405: return "Method Not Allowed";
            case 406: return "Not Acceptable";
            case 407: return "Proxy Authentication Required";
            case 408: return "Request Timeout";
            case 409: return "Conflict";
            case 410: return "Gone";
            case 411: return "Length Required";
            case 412: return "Precondition Failed";
            case 413: return "Payload Too Large";
            case 414: return "URI Too Long";
            case 415: return "Unsupported Media Type";
            case 416: return "Range Not Satisfiable";
            case 417: return "Expectation Failed";
            case 421: return "Misdirected Request";
            case 426: return "Upgrade Required";
            case 428: return "Precondition Required";
            case 429: return "Too Many Requests";
            case 431: return "Request Header Fields Too Large";
            case 500: return "Internal Server Error";
            case 501: return "Not Implemented";
            case 502: return "Bad Gateway";
            case 503: return "Service Unavailable";
            case 504: return "Gateway Timeout";
            case 505: return "HTTP Version Not Supported";
            case 506: return "Variant Also Negotiates";
            case 510: return "Not Extended";
            case 511: return "Network Authentication Required";
            default:  return "???";
            // *INDENT-ON*
        }
    }
};


} // namespace testing

