//------------------------------------------------------------------------------
// This code was generated by a tool.
//
//   Tool : bondjson2cpp 2016.12.18.1
//   File : AriaProtocol.json
//
// Changes to this file may cause incorrect behavior and will be lost when
// the code is regenerated.
// <auto-generated />
//------------------------------------------------------------------------------

#pragma once
#include "BondConstTypes.hpp"

namespace bond_lite {

template<typename TReader>
bool Deserialize(TReader& reader, ::AriaProtocol::Ingest& value, bool isBase)
{
    if (!reader.ReadStructBegin(isBase)) {
        return false;
    }

    uint8_t type;
    uint16_t id;
    for (;;) {
        if (!reader.ReadFieldBegin(type, id)) {
            return false;
        }

        if (type == BT_STOP || type == BT_STOP_BASE) {
            if (isBase != (type == BT_STOP_BASE)) {
                return false;
            }
            break;
        }

        switch (id) {
            case 1: {
                if (!reader.ReadInt64(value.time)) {
                    return false;
                }
                break;
            }

            case 2: {
                if (!reader.ReadString(value.clientIp)) {
                    return false;
                }
                break;
            }

            case 3: {
                if (!reader.ReadInt64(value.auth)) {
                    return false;
                }
                break;
            }

            case 4: {
                if (!reader.ReadInt64(value.quality)) {
                    return false;
                }
                break;
            }

            case 5: {
                if (!reader.ReadInt64(value.uploadTime)) {
                    return false;
                }
                break;
            }

            case 6: {
                if (!reader.ReadString(value.userAgent)) {
                    return false;
                }
                break;
            }

            case 7: {
                if (!reader.ReadString(value.client)) {
                    return false;
                }
                break;
            }

            default:
                return false;
        }

        if (!reader.ReadFieldEnd()) {
            return false;
        }
    }

    if (!reader.ReadStructEnd(isBase)) {
        return false;
    }

    return true;
}

template<typename TReader>
bool Deserialize(TReader& reader, ::AriaProtocol::User& value, bool isBase)
{
    if (!reader.ReadStructBegin(isBase)) {
        return false;
    }

    uint8_t type;
    uint16_t id;
    for (;;) {
        if (!reader.ReadFieldBegin(type, id)) {
            return false;
        }

        if (type == BT_STOP || type == BT_STOP_BASE) {
            if (isBase != (type == BT_STOP_BASE)) {
                return false;
            }
            break;
        }

        switch (id) {
            case 1: {
                if (!reader.ReadString(value.id)) {
                    return false;
                }
                break;
            }

            case 2: {
                if (!reader.ReadString(value.localId)) {
                    return false;
                }
                break;
            }

            case 3: {
                if (!reader.ReadString(value.authId)) {
                    return false;
                }
                break;
            }

            default:
                return false;
        }

        if (!reader.ReadFieldEnd()) {
            return false;
        }
    }

    if (!reader.ReadStructEnd(isBase)) {
        return false;
    }

    return true;
}

template<typename TReader>
bool Deserialize(TReader& reader, ::AriaProtocol::Device& value, bool isBase)
{
    if (!reader.ReadStructBegin(isBase)) {
        return false;
    }

    uint8_t type;
    uint16_t id;
    for (;;) {
        if (!reader.ReadFieldBegin(type, id)) {
            return false;
        }

        if (type == BT_STOP || type == BT_STOP_BASE) {
            if (isBase != (type == BT_STOP_BASE)) {
                return false;
            }
            break;
        }

        switch (id) {
            case 1: {
                if (!reader.ReadString(value.id)) {
                    return false;
                }
                break;
            }

            case 2: {
                if (!reader.ReadString(value.localId)) {
                    return false;
                }
                break;
            }

            case 3: {
                if (!reader.ReadString(value.authId)) {
                    return false;
                }
                break;
            }

            case 4: {
                if (!reader.ReadString(value.authSecId)) {
                    return false;
                }
                break;
            }

            case 5: {
                if (!reader.ReadString(value.deviceClass)) {
                    return false;
                }
                break;
            }

            case 6: {
                if (!reader.ReadString(value.orgId)) {
                    return false;
                }
                break;
            }

            case 7: {
                if (!reader.ReadString(value.orgAuthId)) {
                    return false;
                }
                break;
            }

            default:
                return false;
        }

        if (!reader.ReadFieldEnd()) {
            return false;
        }
    }

    if (!reader.ReadStructEnd(isBase)) {
        return false;
    }

    return true;
}

template<typename TReader>
bool Deserialize(TReader& reader, ::AriaProtocol::Os& value, bool isBase)
{
    if (!reader.ReadStructBegin(isBase)) {
        return false;
    }

    uint8_t type;
    uint16_t id;
    for (;;) {
        if (!reader.ReadFieldBegin(type, id)) {
            return false;
        }

        if (type == BT_STOP || type == BT_STOP_BASE) {
            if (isBase != (type == BT_STOP_BASE)) {
                return false;
            }
            break;
        }

        switch (id) {
            case 1: {
                if (!reader.ReadString(value.locale)) {
                    return false;
                }
                break;
            }

            case 2: {
                if (!reader.ReadString(value.expId)) {
                    return false;
                }
                break;
            }

            case 3: {
                if (!reader.ReadInt32(value.bootId)) {
                    return false;
                }
                break;
            }

            default:
                return false;
        }

        if (!reader.ReadFieldEnd()) {
            return false;
        }
    }

    if (!reader.ReadStructEnd(isBase)) {
        return false;
    }

    return true;
}

template<typename TReader>
bool Deserialize(TReader& reader, ::AriaProtocol::App& value, bool isBase)
{
    if (!reader.ReadStructBegin(isBase)) {
        return false;
    }

    uint8_t type;
    uint16_t id;
    for (;;) {
        if (!reader.ReadFieldBegin(type, id)) {
            return false;
        }

        if (type == BT_STOP || type == BT_STOP_BASE) {
            if (isBase != (type == BT_STOP_BASE)) {
                return false;
            }
            break;
        }

        switch (id) {
            case 1: {
                if (!reader.ReadString(value.expId)) {
                    return false;
                }
                break;
            }

            case 2: {
                if (!reader.ReadString(value.userId)) {
                    return false;
                }
                break;
            }

            case 3: {
                if (!reader.ReadString(value.env)) {
                    return false;
                }
                break;
            }

            case 4: {
                if (!reader.ReadInt32(value.asId)) {
                    return false;
                }
                break;
            }

            default:
                return false;
        }

        if (!reader.ReadFieldEnd()) {
            return false;
        }
    }

    if (!reader.ReadStructEnd(isBase)) {
        return false;
    }

    return true;
}

template<typename TReader>
bool Deserialize(TReader& reader, ::AriaProtocol::Utc& value, bool isBase)
{
    if (!reader.ReadStructBegin(isBase)) {
        return false;
    }

    uint8_t type;
    uint16_t id;
    for (;;) {
        if (!reader.ReadFieldBegin(type, id)) {
            return false;
        }

        if (type == BT_STOP || type == BT_STOP_BASE) {
            if (isBase != (type == BT_STOP_BASE)) {
                return false;
            }
            break;
        }

        switch (id) {
            case 1: {
                if (!reader.ReadString(value.stId)) {
                    return false;
                }
                break;
            }

            case 2: {
                if (!reader.ReadString(value.aId)) {
                    return false;
                }
                break;
            }

            case 3: {
                if (!reader.ReadString(value.raId)) {
                    return false;
                }
                break;
            }

            case 4: {
                if (!reader.ReadString(value.op)) {
                    return false;
                }
                break;
            }

            case 5: {
                if (!reader.ReadInt64(value.cat)) {
                    return false;
                }
                break;
            }

            case 6: {
                if (!reader.ReadInt64(value.flags)) {
                    return false;
                }
                break;
            }

            case 7: {
                if (!reader.ReadString(value.sqmId)) {
                    return false;
                }
                break;
            }

            case 8: {
                uint32_t size4;
                uint8_t type4;
                if (!reader.ReadContainerBegin(size4, type4)) {
                    return false;
                }
                if (type4 != BT_STRING) {
                    return false;
                }
                value.tickets.resize(size4);
                for (unsigned i4 = 0; i4 < size4; i4++) {
                    if (!reader.ReadString(value.tickets[i4])) {
                        return false;
                    }
                }
                if (!reader.ReadContainerEnd()) {
                    return false;
                }
                break;
            }

            case 9: {
                if (!reader.ReadString(value.mon)) {
                    return false;
                }
                break;
            }

            case 10: {
                if (!reader.ReadInt32(value.cpId)) {
                    return false;
                }
                break;
            }

            case 11: {
                if (!reader.ReadString(value.bSeq)) {
                    return false;
                }
                break;
            }

            default:
                return false;
        }

        if (!reader.ReadFieldEnd()) {
            return false;
        }
    }

    if (!reader.ReadStructEnd(isBase)) {
        return false;
    }

    return true;
}

template<typename TReader>
bool Deserialize(TReader& reader, ::AriaProtocol::Protocol& value, bool isBase)
{
    if (!reader.ReadStructBegin(isBase)) {
        return false;
    }

    uint8_t type;
    uint16_t id;
    for (;;) {
        if (!reader.ReadFieldBegin(type, id)) {
            return false;
        }

        if (type == BT_STOP || type == BT_STOP_BASE) {
            if (isBase != (type == BT_STOP_BASE)) {
                return false;
            }
            break;
        }

        switch (id) {
            case 1: {
                if (!reader.ReadInt32(value.metadataCrc)) {
                    return false;
                }
                break;
            }

            case 2: {
                if (!reader.ReadString(value.ticketKey)) {
                    return false;
                }
                break;
            }

            default:
                return false;
        }

        if (!reader.ReadFieldEnd()) {
            return false;
        }
    }

    if (!reader.ReadStructEnd(isBase)) {
        return false;
    }

    return true;
}

template<typename TReader>
bool Deserialize(TReader& reader, ::AriaProtocol::PII& value, bool isBase)
{
    if (!reader.ReadStructBegin(isBase)) {
        return false;
    }

    uint8_t type;
    uint16_t id;
    for (;;) {
        if (!reader.ReadFieldBegin(type, id)) {
            return false;
        }

        if (type == BT_STOP || type == BT_STOP_BASE) {
            if (isBase != (type == BT_STOP_BASE)) {
                return false;
            }
            break;
        }

        switch (id) {
            case 1: {
                static_assert(sizeof(value.Kind) == 4, "Invalid size of enum");
                int32_t item4;
                if (!reader.ReadInt32(item4)) {
                    return false;
                }
                value.Kind = static_cast< ::AriaProtocol::PIIKind>(item4);
                break;
            }

            default:
                return false;
        }

        if (!reader.ReadFieldEnd()) {
            return false;
        }
    }

    if (!reader.ReadStructEnd(isBase)) {
        return false;
    }

    return true;
}

template<typename TReader>
bool Deserialize(TReader& reader, ::AriaProtocol::CustomerContent& value, bool isBase)
{
    if (!reader.ReadStructBegin(isBase)) {
        return false;
    }

    uint8_t type;
    uint16_t id;
    for (;;) {
        if (!reader.ReadFieldBegin(type, id)) {
            return false;
        }

        if (type == BT_STOP || type == BT_STOP_BASE) {
            if (isBase != (type == BT_STOP_BASE)) {
                return false;
            }
            break;
        }

        switch (id) {
            case 1: {
                static_assert(sizeof(value.Kind) == 4, "Invalid size of enum");
                int32_t item4;
                if (!reader.ReadInt32(item4)) {
                    return false;
                }
                value.Kind = static_cast< ::AriaProtocol::CustomerContentKind>(item4);
                break;
            }

            default:
                return false;
        }

        if (!reader.ReadFieldEnd()) {
            return false;
        }
    }

    if (!reader.ReadStructEnd(isBase)) {
        return false;
    }

    return true;
}

template<typename TReader>
bool Deserialize(TReader& reader, ::AriaProtocol::Attributes& value, bool isBase)
{
    if (!reader.ReadStructBegin(isBase)) {
        return false;
    }

    uint8_t type;
    uint16_t id;
    for (;;) {
        if (!reader.ReadFieldBegin(type, id)) {
            return false;
        }

        if (type == BT_STOP || type == BT_STOP_BASE) {
            if (isBase != (type == BT_STOP_BASE)) {
                return false;
            }
            break;
        }

        switch (id) {
            case 1: {
                uint32_t size4;
                uint8_t type4;
                if (!reader.ReadContainerBegin(size4, type4)) {
                    return false;
                }
                if (type4 != BT_STRUCT) {
                    return false;
                }
                value.pii.resize(size4);
                for (unsigned i4 = 0; i4 < size4; i4++) {
                    if (!Deserialize(reader, value.pii[i4], false)) {
                        return false;
                    }
                }
                if (!reader.ReadContainerEnd()) {
                    return false;
                }
                break;
            }

            case 2: {
                uint32_t size4;
                uint8_t type4;
                if (!reader.ReadContainerBegin(size4, type4)) {
                    return false;
                }
                if (type4 != BT_STRUCT) {
                    return false;
                }
                value.customerContent.resize(size4);
                for (unsigned i4 = 0; i4 < size4; i4++) {
                    if (!Deserialize(reader, value.customerContent[i4], false)) {
                        return false;
                    }
                }
                if (!reader.ReadContainerEnd()) {
                    return false;
                }
                break;
            }

            default:
                return false;
        }

        if (!reader.ReadFieldEnd()) {
            return false;
        }
    }

    if (!reader.ReadStructEnd(isBase)) {
        return false;
    }

    return true;
}

template<typename TReader>
bool Deserialize(TReader& reader, ::AriaProtocol::Value& value, bool isBase)
{
    if (!reader.ReadStructBegin(isBase)) {
        return false;
    }

    uint8_t type;
    uint16_t id;
    for (;;) {
        if (!reader.ReadFieldBegin(type, id)) {
            return false;
        }

        if (type == BT_STOP || type == BT_STOP_BASE) {
            if (isBase != (type == BT_STOP_BASE)) {
                return false;
            }
            break;
        }

        switch (id) {
            case 1: {
                static_assert(sizeof(value.type) == 4, "Invalid size of enum");
                int32_t item4;
                if (!reader.ReadInt32(item4)) {
                    return false;
                }
                value.type = static_cast< ::AriaProtocol::ValueKind>(item4);
                break;
            }

            case 2: {
                uint32_t size4;
                uint8_t type4;
                if (!reader.ReadContainerBegin(size4, type4)) {
                    return false;
                }
                if (type4 != BT_STRUCT) {
                    return false;
                }
                value.attributes.resize(size4);
                for (unsigned i4 = 0; i4 < size4; i4++) {
                    if (!Deserialize(reader, value.attributes[i4], false)) {
                        return false;
                    }
                }
                if (!reader.ReadContainerEnd()) {
                    return false;
                }
                break;
            }

            case 3: {
                if (!reader.ReadString(value.stringValue)) {
                    return false;
                }
                break;
            }

            case 4: {
                if (!reader.ReadInt64(value.longValue)) {
                    return false;
                }
                break;
            }

            case 5: {
                if (!reader.ReadDouble(value.doubleValue)) {
                    return false;
                }
                break;
            }

            case 6: {
                uint32_t size4;
                uint8_t type4;
                if (!reader.ReadContainerBegin(size4, type4)) {
                    return false;
                }
                if (type4 != BT_LIST) {
                    return false;
                }
                value.guidValue.resize(size4);
                for (unsigned i4 = 0; i4 < size4; i4++) {
                    uint32_t size5;
                    uint8_t type5;
                    if (!reader.ReadContainerBegin(size5, type5)) {
                        return false;
                    }
                    if (type5 != BT_UINT8) {
                        return false;
                    }
                    value.guidValue[i4].resize(size5);
                    for (unsigned i5 = 0; i5 < size5; i5++) {
                        if (!reader.ReadUInt8(value.guidValue[i4][i5])) {
                            return false;
                        }
                    }
                    if (!reader.ReadContainerEnd()) {
                        return false;
                    }
                }
                if (!reader.ReadContainerEnd()) {
                    return false;
                }
                break;
            }

            case 10: {
                uint32_t size4;
                uint8_t type4;
                if (!reader.ReadContainerBegin(size4, type4)) {
                    return false;
                }
                if (type4 != BT_LIST) {
                    return false;
                }
                value.stringArray.resize(size4);
                for (unsigned i4 = 0; i4 < size4; i4++) {
                    uint32_t size5;
                    uint8_t type5;
                    if (!reader.ReadContainerBegin(size5, type5)) {
                        return false;
                    }
                    if (type5 != BT_STRING) {
                        return false;
                    }
                    value.stringArray[i4].resize(size5);
                    for (unsigned i5 = 0; i5 < size5; i5++) {
                        if (!reader.ReadString(value.stringArray[i4][i5])) {
                            return false;
                        }
                    }
                    if (!reader.ReadContainerEnd()) {
                        return false;
                    }
                }
                if (!reader.ReadContainerEnd()) {
                    return false;
                }
                break;
            }

            case 11: {
                uint32_t size4;
                uint8_t type4;
                if (!reader.ReadContainerBegin(size4, type4)) {
                    return false;
                }
                if (type4 != BT_LIST) {
                    return false;
                }
                value.longArray.resize(size4);
                for (unsigned i4 = 0; i4 < size4; i4++) {
                    uint32_t size5;
                    uint8_t type5;
                    if (!reader.ReadContainerBegin(size5, type5)) {
                        return false;
                    }
                    if (type5 != BT_INT64) {
                        return false;
                    }
                    value.longArray[i4].resize(size5);
                    for (unsigned i5 = 0; i5 < size5; i5++) {
                        if (!reader.ReadInt64(value.longArray[i4][i5])) {
                            return false;
                        }
                    }
                    if (!reader.ReadContainerEnd()) {
                        return false;
                    }
                }
                if (!reader.ReadContainerEnd()) {
                    return false;
                }
                break;
            }

            case 12: {
                uint32_t size4;
                uint8_t type4;
                if (!reader.ReadContainerBegin(size4, type4)) {
                    return false;
                }
                if (type4 != BT_LIST) {
                    return false;
                }
                value.doubleArray.resize(size4);
                for (unsigned i4 = 0; i4 < size4; i4++) {
                    uint32_t size5;
                    uint8_t type5;
                    if (!reader.ReadContainerBegin(size5, type5)) {
                        return false;
                    }
                    if (type5 != BT_DOUBLE) {
                        return false;
                    }
                    value.doubleArray[i4].resize(size5);
                    for (unsigned i5 = 0; i5 < size5; i5++) {
                        if (!reader.ReadDouble(value.doubleArray[i4][i5])) {
                            return false;
                        }
                    }
                    if (!reader.ReadContainerEnd()) {
                        return false;
                    }
                }
                if (!reader.ReadContainerEnd()) {
                    return false;
                }
                break;
            }

            case 13: {
                uint32_t size4;
                uint8_t type4;
                if (!reader.ReadContainerBegin(size4, type4)) {
                    return false;
                }
                if (type4 != BT_LIST) {
                    return false;
                }
                value.guidArray.resize(size4);
                for (unsigned i4 = 0; i4 < size4; i4++) {
                    uint32_t size5;
                    uint8_t type5;
                    if (!reader.ReadContainerBegin(size5, type5)) {
                        return false;
                    }
                    if (type5 != BT_LIST) {
                        return false;
                    }
                    value.guidArray[i4].resize(size5);
                    for (unsigned i5 = 0; i5 < size5; i5++) {
                        uint32_t size6;
                        uint8_t type6;
                        if (!reader.ReadContainerBegin(size6, type6)) {
                            return false;
                        }
                        if (type6 != BT_INT64) {
                            return false;
                        }
                        value.guidArray[i4][i5].resize(size6);
                        for (unsigned i6 = 0; i6 < size6; i6++) {
                            if (!reader.ReadInt64(value.guidArray[i4][i5][i6])) {
                                return false;
                            }
                        }
                        if (!reader.ReadContainerEnd()) {
                            return false;
                        }
                    }
                    if (!reader.ReadContainerEnd()) {
                        return false;
                    }
                }
                if (!reader.ReadContainerEnd()) {
                    return false;
                }
                break;
            }

            default:
                return false;
        }

        if (!reader.ReadFieldEnd()) {
            return false;
        }
    }

    if (!reader.ReadStructEnd(isBase)) {
        return false;
    }

    return true;
}

template<typename TReader>
bool Deserialize(TReader& reader, ::AriaProtocol::Data& value, bool isBase)
{
    if (!reader.ReadStructBegin(isBase)) {
        return false;
    }

    uint8_t type;
    uint16_t id;
    for (;;) {
        if (!reader.ReadFieldBegin(type, id)) {
            return false;
        }

        if (type == BT_STOP || type == BT_STOP_BASE) {
            if (isBase != (type == BT_STOP_BASE)) {
                return false;
            }
            break;
        }

        switch (id) {
            case 1: {
                uint32_t size4;
                uint8_t keyType4, valueType4;
                if (!reader.ReadMapContainerBegin(size4, keyType4, valueType4)) {
                    return false;
                }
                if (keyType4 != BT_STRING || valueType4 != BT_STRUCT) {
                    return false;
                }
                for (unsigned i4 = 0; i4 < size4; i4++) {
                    std::string key4;
                    if (!reader.ReadString(key4)) {
                        return false;
                    }
                    if (!Deserialize(reader, value.properties[key4], false)) {
                        return false;
                    }
                }
                if (!reader.ReadContainerEnd()) {
                    return false;
                }
                break;
            }

            default:
                return false;
        }

        if (!reader.ReadFieldEnd()) {
            return false;
        }
    }

    if (!reader.ReadStructEnd(isBase)) {
        return false;
    }

    return true;
}

template<typename TReader>
bool Deserialize(TReader& reader, ::AriaProtocol::CsEvent& value, bool isBase)
{
    if (!reader.ReadStructBegin(isBase)) {
        return false;
    }

    uint8_t type;
    uint16_t id;
    for (;;) {
        if (!reader.ReadFieldBegin(type, id)) {
            return false;
        }

        if (type == BT_STOP || type == BT_STOP_BASE) {
            if (isBase != (type == BT_STOP_BASE)) {
                return false;
            }
            break;
        }

        switch (id) {
            case 1: {
                if (!reader.ReadString(value.ver)) {
                    return false;
                }
                break;
            }

            case 2: {
                if (!reader.ReadString(value.name)) {
                    return false;
                }
                break;
            }

            case 3: {
                if (!reader.ReadInt64(value.time)) {
                    return false;
                }
                break;
            }

            case 4: {
                if (!reader.ReadDouble(value.popSample)) {
                    return false;
                }
                break;
            }

            case 5: {
                if (!reader.ReadString(value.epoch)) {
                    return false;
                }
                break;
            }

            case 6: {
                if (!reader.ReadInt64(value.seqNum)) {
                    return false;
                }
                break;
            }

            case 7: {
                if (!reader.ReadString(value.iKey)) {
                    return false;
                }
                break;
            }

            case 8: {
                if (!reader.ReadInt64(value.flags)) {
                    return false;
                }
                break;
            }

            case 9: {
                if (!reader.ReadString(value.os)) {
                    return false;
                }
                break;
            }

            case 10: {
                if (!reader.ReadString(value.osVer)) {
                    return false;
                }
                break;
            }

            case 11: {
                if (!reader.ReadString(value.appId)) {
                    return false;
                }
                break;
            }

            case 12: {
                if (!reader.ReadString(value.appVer)) {
                    return false;
                }
                break;
            }

            case 13: {
                if (!reader.ReadString(value.cV)) {
                    return false;
                }
                break;
            }

            case 14: {
                uint32_t size4;
                uint8_t type4;
                if (!reader.ReadContainerBegin(size4, type4)) {
                    return false;
                }
                if (type4 != BT_STRUCT) {
                    return false;
                }
                value.extIngest.resize(size4);
                for (unsigned i4 = 0; i4 < size4; i4++) {
                    if (!Deserialize(reader, value.extIngest[i4], false)) {
                        return false;
                    }
                }
                if (!reader.ReadContainerEnd()) {
                    return false;
                }
                break;
            }

            case 15: {
                uint32_t size4;
                uint8_t type4;
                if (!reader.ReadContainerBegin(size4, type4)) {
                    return false;
                }
                if (type4 != BT_STRUCT) {
                    return false;
                }
                value.extUser.resize(size4);
                for (unsigned i4 = 0; i4 < size4; i4++) {
                    if (!Deserialize(reader, value.extUser[i4], false)) {
                        return false;
                    }
                }
                if (!reader.ReadContainerEnd()) {
                    return false;
                }
                break;
            }

            case 16: {
                uint32_t size4;
                uint8_t type4;
                if (!reader.ReadContainerBegin(size4, type4)) {
                    return false;
                }
                if (type4 != BT_STRUCT) {
                    return false;
                }
                value.extDevice.resize(size4);
                for (unsigned i4 = 0; i4 < size4; i4++) {
                    if (!Deserialize(reader, value.extDevice[i4], false)) {
                        return false;
                    }
                }
                if (!reader.ReadContainerEnd()) {
                    return false;
                }
                break;
            }

            case 17: {
                uint32_t size4;
                uint8_t type4;
                if (!reader.ReadContainerBegin(size4, type4)) {
                    return false;
                }
                if (type4 != BT_STRUCT) {
                    return false;
                }
                value.extOs.resize(size4);
                for (unsigned i4 = 0; i4 < size4; i4++) {
                    if (!Deserialize(reader, value.extOs[i4], false)) {
                        return false;
                    }
                }
                if (!reader.ReadContainerEnd()) {
                    return false;
                }
                break;
            }

            case 18: {
                uint32_t size4;
                uint8_t type4;
                if (!reader.ReadContainerBegin(size4, type4)) {
                    return false;
                }
                if (type4 != BT_STRUCT) {
                    return false;
                }
                value.expApp.resize(size4);
                for (unsigned i4 = 0; i4 < size4; i4++) {
                    if (!Deserialize(reader, value.expApp[i4], false)) {
                        return false;
                    }
                }
                if (!reader.ReadContainerEnd()) {
                    return false;
                }
                break;
            }

            case 19: {
                uint32_t size4;
                uint8_t type4;
                if (!reader.ReadContainerBegin(size4, type4)) {
                    return false;
                }
                if (type4 != BT_STRUCT) {
                    return false;
                }
                value.extUtc.resize(size4);
                for (unsigned i4 = 0; i4 < size4; i4++) {
                    if (!Deserialize(reader, value.extUtc[i4], false)) {
                        return false;
                    }
                }
                if (!reader.ReadContainerEnd()) {
                    return false;
                }
                break;
            }

            case 20: {
                uint32_t size4;
                uint8_t type4;
                if (!reader.ReadContainerBegin(size4, type4)) {
                    return false;
                }
                if (type4 != BT_STRUCT) {
                    return false;
                }
                value.extProtocol.resize(size4);
                for (unsigned i4 = 0; i4 < size4; i4++) {
                    if (!Deserialize(reader, value.extProtocol[i4], false)) {
                        return false;
                    }
                }
                if (!reader.ReadContainerEnd()) {
                    return false;
                }
                break;
            }

            case 21: {
                uint32_t size4;
                uint8_t type4;
                if (!reader.ReadContainerBegin(size4, type4)) {
                    return false;
                }
                if (type4 != BT_STRUCT) {
                    return false;
                }
                value.ext.resize(size4);
                for (unsigned i4 = 0; i4 < size4; i4++) {
                    if (!Deserialize(reader, value.ext[i4], false)) {
                        return false;
                    }
                }
                if (!reader.ReadContainerEnd()) {
                    return false;
                }
                break;
            }

            case 22: {
                uint32_t size4;
                uint8_t keyType4, valueType4;
                if (!reader.ReadMapContainerBegin(size4, keyType4, valueType4)) {
                    return false;
                }
                if (keyType4 != BT_STRING || valueType4 != BT_STRING) {
                    return false;
                }
                for (unsigned i4 = 0; i4 < size4; i4++) {
                    std::string key4;
                    if (!reader.ReadString(key4)) {
                        return false;
                    }
                    if (!reader.ReadString(value.tags[key4])) {
                        return false;
                    }
                }
                if (!reader.ReadContainerEnd()) {
                    return false;
                }
                break;
            }

            case 50: {
                if (!reader.ReadString(value.baseType)) {
                    return false;
                }
                break;
            }

            case 51: {
                uint32_t size4;
                uint8_t type4;
                if (!reader.ReadContainerBegin(size4, type4)) {
                    return false;
                }
                if (type4 != BT_STRUCT) {
                    return false;
                }
                value.baseData.resize(size4);
                for (unsigned i4 = 0; i4 < size4; i4++) {
                    if (!Deserialize(reader, value.baseData[i4], false)) {
                        return false;
                    }
                }
                if (!reader.ReadContainerEnd()) {
                    return false;
                }
                break;
            }

            case 60: {
                uint32_t size4;
                uint8_t type4;
                if (!reader.ReadContainerBegin(size4, type4)) {
                    return false;
                }
                if (type4 != BT_STRUCT) {
                    return false;
                }
                value.data.resize(size4);
                for (unsigned i4 = 0; i4 < size4; i4++) {
                    if (!Deserialize(reader, value.data[i4], false)) {
                        return false;
                    }
                }
                if (!reader.ReadContainerEnd()) {
                    return false;
                }
                break;
            }

            default:
                return false;
        }

        if (!reader.ReadFieldEnd()) {
            return false;
        }
    }

    if (!reader.ReadStructEnd(isBase)) {
        return false;
    }

    return true;
}

} // namespace bond_lite
