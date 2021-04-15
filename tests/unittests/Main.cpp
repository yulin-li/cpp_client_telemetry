//
// Copyright (c) 2015-2020 Microsoft Corporation and Contributors.
// SPDX-License-Identifier: Apache-2.0
//

#include "common/Common.hpp"
#include "config/RuntimeConfig_Default.hpp"
#include "utils/Utils.hpp"

#if defined(_DEBUG) && defined(_WIN32) && !defined(_INC_WINDOWS)
extern "C" unsigned long __stdcall IsDebuggerPresent();
#endif

class TestStatusLogger : public testing::EmptyTestEventListener {
  public:
    virtual void OnTestStart(testing::TestInfo const& test) override
    {
        std::ignore = test;
        LOG_INFO("--- %s.%s", test.test_case_name(), test.name());
    }

    virtual void OnTestEnd(testing::TestInfo const& test) override
    {
        std::ignore = test;
        LOG_INFO("=== %s.%s [%s]", test.test_case_name(), test.name(), test.result()->Passed() ? "OK" : "FAILED");
    }
};
#ifdef _MSC_VER
#define MAIN_CDECL __cdecl
#else
#define MAIN_CDECL
#endif

int MAIN_CDECL main(int argc, char** argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    ::testing::UnitTest::GetInstance()->listeners().Append(new TestStatusLogger());

    ILogConfiguration logConfig;
    RuntimeConfig_Default runtimeConfig(logConfig);
    PAL::initialize(runtimeConfig);
    int result = RUN_ALL_TESTS();
    PAL::shutdown();

#if defined(_DEBUG) && defined(_WIN32)
    if (IsDebuggerPresent()) {
        printf("Press Enter to close...");
        getchar();
    }
#endif

    return result;
}

