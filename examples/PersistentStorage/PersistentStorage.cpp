#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>

#include "json.hpp"

#include <vector>

#include <LogManager.hpp>

using json = nlohmann::json;
using namespace MAT;

/*
    - stats
    - config [maybe not so persistent...]
    - aggregation temporary checkpoints
    - ECS json tree
*/

// Serialize from EventProperties to vector<uint8_t>
std::vector<uint8_t> to_cbor(EventProperties &props)
{
    json j;

    j["data"] = json({});
    j["data"]["baseType"] = "";
    j["data"]["baseData"] = "";
    j["data"]["baseDataType"] = props.GetType();
    j["data"]["eventName"] = props.GetName();

    for (auto &kv : props.GetProperties())
    {
        const std::string &key = kv.first;
        const EventProperty &val = kv.second;
        switch (val.type)
        {
        case EventProperty::TYPE_STRING:
            j["data"][key] = val.as_string;
            break;
        case EventProperty::TYPE_INT64:
            j["data"][key] = val.as_int64;
            break;
        case EventProperty::TYPE_DOUBLE:
            j["data"][key] = val.as_double;
            break;
        case EventProperty::TYPE_TIME:
            // TODO: [MG] - fix time!!!
            j["data"][key] = val.as_time_ticks.ticks;
            break;
        case EventProperty::TYPE_BOOLEAN:
            j["data"][key] = val.to_string().c_str();
            break;
        case EventProperty::TYPE_GUID:
            j["data"][key] = val.to_string();
            break;
        // TODO: [MG] - add proper handling for all other types
        }
    };

    return json::to_cbor(j);
}

// Deserialize from vector<uint8_t> to EventProperties
EventProperties from_cbor(std::vector<uint8_t> blob)
{
    EventProperties result;

    json j = json::from_cbor(blob);
    result.SetName(j["data"]["eventName"]);
    result.SetType(j["data"]["baseDataType"]);

    auto o = j["data"];
    for (json::iterator it = o.begin(); it != o.end(); ++it)
    {
        switch (it.value().type() )
        {
        case json::value_t::array :
            // TODO
            break;
        case json::value_t::boolean :
            result.SetProperty(it.key(), (bool)it.value() ); // (bool)o[it.key()] );
            break;
        case json::value_t::discarded :
            break;
        case json::value_t::null :
            break;
        case json::value_t::number_float :
            result.SetProperty(it.key(), (double)it.value()); // (bool)o[it.key()] );
            break;
        case json::value_t::number_integer :
        case json::value_t::number_unsigned :
            result.SetProperty(it.key(), (int64_t)it.value()); // (bool)o[it.key()] );
            break;
        case json::value_t::object :
            break;
        case json::value_t::string :
            std::string val = it.value();
            result.SetProperty(it.key(), val);
            break;
        }
    }
    return result;
}

void testStorage()
{
    GUID_t guid_0 = { 0x4d36e96e, 0xe325, 0x11c3,{ 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18 } };

    GUID win_guid;
    win_guid.Data1 = 0;
    win_guid.Data2 = 1;
    win_guid.Data3 = 2;

    // GUID constructor from byte[16]
    const uint8_t guid_b[16] = {
        0x03, 0x02, 0x01, 0x00,
        0x05, 0x04,
        0x07, 0x06,
        0x08, 0x09,
        0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };

    GUID_t guid_c(
        0x00010203,
        0x0405,
        0x0607,
        { 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F }
    );

    // Prepare current time in UTC (seconds precision)
    std::time_t t = std::time(nullptr);
    std::gmtime(&t);

    const char *name = "myEvent";
    EventProperties props(name,
        {
            { "_MSC_VER", _MSC_VER },

        { "piiKind.None",               EventProperty("maxgolov",  PiiKind_None) },
        { "piiKind.DistinguishedName",  EventProperty("/CN=Max Golovanov,OU=ARIA,DC=REDMOND,DC=COM",  PiiKind_DistinguishedName) },
        { "piiKind.GenericData",        EventProperty("maxgolov",  PiiKind_GenericData) },
        { "piiKind.IPv4Address",        EventProperty("127.0.0.1", PiiKind_IPv4Address) },
        { "piiKind.IPv6Address",        EventProperty("2001:0db8:85a3:0000:0000:8a2e:0370:7334", PiiKind_IPv6Address) },
        { "piiKind.MailSubject",        EventProperty("RE: test",  PiiKind_MailSubject) },
        { "piiKind.PhoneNumber",        EventProperty("+1-613-866-6960", PiiKind_PhoneNumber) },
        { "piiKind.QueryString",        EventProperty("a=1&b=2&c=3", PiiKind_QueryString) },
        { "piiKind.SipAddress",         EventProperty("sip:maxgolov@microsoft.com", PiiKind_SipAddress) },
        { "piiKind.SmtpAddress",        EventProperty("Max Golovanov <maxgolov@microsoft.com>", PiiKind_SmtpAddress) },
        { "piiKind.Identity",           EventProperty("Max Golovanov", PiiKind_Identity) },
        { "piiKind.Uri",                EventProperty("http://www.microsoft.com", PiiKind_Uri) },
        { "piiKind.Fqdn",               EventProperty("www.microsoft.com", PiiKind_Fqdn) },

        { "strKey",   "hello" },
        { "strKey2",  "hello2" },
        { "int64Key", 1L },
        { "dblKey",   3.14 },
        { "boolKey",  false },
        { "guidKey0", GUID_t("00000000-0000-0000-0000-000000000000") },
        { "guidKey1", GUID_t("00010203-0405-0607-0809-0A0B0C0D0E0F") },
        { "guidKey2", GUID_t(guid_b) },
        { "guidKey3", GUID_t("00010203-0405-0607-0809-0A0B0C0D0E0F") },
        { "guidKey4", GUID_t(guid_c) },
        { "timeKey1",  time_ticks_t((uint64_t)0) },     // ticks   precision
        { "timeKey2",  time_ticks_t(&t) }               // seconds precision
        });

    auto blob = to_cbor(props);
    EventProperties props2 = from_cbor(blob);
}

/// <summary>
/// Mains the specified argc.
/// </summary>
/// <param name="argc">The argc.</param>
/// <param name="argv">The argv.</param>
/// <returns></returns>
int main(int argc, char *argv[])
{
    std::vector<uint8_t> myValues1 = { 1, 2, 3 };
    std::vector<uint8_t> myValues2 = { 1, 2, 3 };

    json j =
    {
        { "ecs",
            { "someTreeElement", 1 }
        },
        { "checkpoints",
            {
                { "val1", myValues1 },
                { "val2", myValues2 }
            }
        },
        { "stats",
            {
                { "statsVal1", 0 },
                { "statsVal2", 1 },
            }
        }
    };

    auto cbor = json::to_cbor(j);
    printf("serialized to cbor, size=%u\n", cbor.size());
    // Once we got a vector<uint8_t> - we can save this as a single record to DB, as SQLite blob


    // ..

    // Then after we read it back from Sqlite, we recover back the vector contents from JSON
    json j2 = json::from_cbor(cbor);
    printf("got back %s\n", j2.dump().c_str());

    std::vector<uint8_t> myVals = j2["checkpoints"]["val1"];
    printf("Vector values: [");
    for (auto &v : myVals)
    {
        printf("%d,", v);
    }
    printf("]\n");

    testStorage();

    return 0;
}
