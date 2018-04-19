// Copyright (c) Microsoft. All rights reserved.

#pragma once
#include "Common.hpp"
#include "api/LogManagerImpl.hpp"
#include "api/ContextFieldsProvider.hpp"
#include "Enums.hpp"
#include "ILogger.hpp"


namespace testing {


    class MockILogManagerInternal : public ARIASDK_NS::ILogManagerInternal
    {
    public:
        MockILogManagerInternal();
        ~MockILogManagerInternal();

        MOCK_METHOD0(FlushAndTeardown, void());
        MOCK_METHOD0(Flush, void());
        MOCK_METHOD0(UploadNow, void());
        MOCK_METHOD0(PauseTransmission, void());
        MOCK_METHOD0(ResumeTransmission, void());
        MOCK_METHOD1(SetTransmitProfile, void(ARIASDK_NS::TransmitProfile profile));
        MOCK_METHOD1(SetTransmitProfile, bool(const std::string& profile));
        MOCK_METHOD1(LoadTransmitProfiles, bool(const std::string& profiles_json));
        MOCK_METHOD0(ResetTransmitProfiles, void());
        MOCK_METHOD0(GetTransmitProfileName, std::string&());
        MOCK_METHOD0(GetSemanticContext, ARIASDK_NS::ISemanticContext & ());
        MOCK_METHOD3(SetContext, MAT::status_t(std::string const &, std::string const &, ARIASDK_NS::PiiKind));
        MOCK_METHOD3(SetContext, MAT::status_t(const std::string&, const char*, ARIASDK_NS::PiiKind));
        MOCK_METHOD3(SetContext, MAT::status_t(const std::string&, double, ARIASDK_NS::PiiKind));
        MOCK_METHOD3(SetContext, MAT::status_t(const std::string&, int64_t, ARIASDK_NS::PiiKind));
        MOCK_METHOD3(SetContext, MAT::status_t(const std::string&, int8_t, ARIASDK_NS::PiiKind));
        MOCK_METHOD3(SetContext, MAT::status_t(const std::string&, int16_t, ARIASDK_NS::PiiKind));
        MOCK_METHOD3(SetContext, MAT::status_t(const std::string&, int32_t, ARIASDK_NS::PiiKind));
        MOCK_METHOD3(SetContext, MAT::status_t(const std::string&, uint8_t, ARIASDK_NS::PiiKind));
        MOCK_METHOD3(SetContext, MAT::status_t(const std::string&, uint16_t, ARIASDK_NS::PiiKind));
        MOCK_METHOD3(SetContext, MAT::status_t(const std::string&, uint32_t, ARIASDK_NS::PiiKind));
        MOCK_METHOD3(SetContext, MAT::status_t(const std::string&, uint64_t, ARIASDK_NS::PiiKind));
        MOCK_METHOD3(SetContext, MAT::status_t(const std::string&, bool, ARIASDK_NS::PiiKind));
        MOCK_METHOD3(SetContext, MAT::status_t(const std::string&, ARIASDK_NS::time_ticks_t, ARIASDK_NS::PiiKind));
        MOCK_METHOD3(SetContext, MAT::status_t(const std::string&, ARIASDK_NS::GUID_t, ARIASDK_NS::PiiKind));
        MOCK_METHOD4(GetLogger, ARIASDK_NS::ILogger * (std::string const &, ARIASDK_NS::ContextFieldsProvider*, std::string const &, std::string const &));
        MOCK_METHOD1(sendEvent, void(ARIASDK_NS::IncomingEventContextPtr const &));
    };


} // namespace testing
