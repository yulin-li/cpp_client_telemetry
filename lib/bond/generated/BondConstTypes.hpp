//
// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: Apache-2.0
//
//------------------------------------------------------------------------------
// This code was generated by a tool.
//
//   Tool : bondjson2cpp 2017.09.19.1
//   File : bond_const.json
//
// Changes to this file may cause incorrect behavior and will be lost when
// the code is regenerated.
// <auto-generated />
//------------------------------------------------------------------------------

#pragma once

namespace bond_lite {

enum BondDataType {
    BT_STOP        = 0,
    BT_STOP_BASE   = 1,
    BT_BOOL        = 2,
    BT_UINT8       = 3,
    BT_UINT16      = 4,
    BT_UINT32      = 5,
    BT_UINT64      = 6,
    BT_FLOAT       = 7,
    BT_DOUBLE      = 8,
    BT_STRING      = 9,
    BT_STRUCT      = 10,
    BT_LIST        = 11,
    BT_SET         = 12,
    BT_MAP         = 13,
    BT_INT8        = 14,
    BT_INT16       = 15,
    BT_INT32       = 16,
    BT_INT64       = 17,
    BT_WSTRING     = 18,
    BT_UNAVAILABLE = 127
};

enum ProtocolType {
    MARSHALED_PROTOCOL   = 0,
    FAST_PROTOCOL        = 17997,
    COMPACT_PROTOCOL     = 16963,
    SIMPLE_JSON_PROTOCOL = 19027,
    SIMPLE_PROTOCOL      = 20563
};

} // namespace bond_lite

