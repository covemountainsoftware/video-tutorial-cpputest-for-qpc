/// @brief  Tests for the Hw Lock Ctrl Service, demonstrating various unit
///         testing capabilities of the 'fake' cms::test::qf_ctrl environment,
///         using cpputest and QP/C (qpc) framework.
/// @ingroup
/// @cond
///***************************************************************************
///
/// Copyright (C) 2022 Matthew Eshleman. All rights reserved.
///
/// This program is open source software: you can redistribute it and/or
/// modify it under the terms of the GNU General Public License as published
/// by the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// Alternatively, upon written permission from Matthew Eshleman, this program
/// may be distributed and modified under the terms of a Commercial
/// License. For further details, see the Contact Information below.
///
/// Contact Information:
///   Matthew Eshleman
///   https://covemountainsoftware.com
///   info@covemountainsoftware.com
///***************************************************************************
/// @endcond

#include "qpc.h"
#include "pwmService.h"
#include "cms_cpputest_qf_ctrl.hpp"
#include "bspTicks.h"
#include "pub_sub_signals.h"

// the cpputest headers must always be last
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

Q_DEFINE_THIS_MODULE("pwmServiceTests")

TEST_GROUP(PwmServiceTests)
{
    QActive* mUnderTest         = nullptr;

    void setup() final
    {
        // Setup and create the cpputest-for-qpc environment
        cms::test::qf_ctrl::Setup(MAX_PUB_SUB_SIG, BSP_TICKS_PER_SECOND);

        // Confirm that the PwmService instance is currently null,
        // enforcing a clean setup()
        CHECK_TRUE(g_thePwmService == nullptr);

        // Create our unit under test. Since it is a C style unit,
        // we must call its init method (ctor, following QP/C style)
        PwmService_ctor();

        // Assign the global singleton to our 'under test' member
        // this could be skipped, I just prefer to refer to the object
        // under test in this manner.
        mUnderTest = g_thePwmService;
        CHECK_TRUE(mUnderTest != nullptr);
    }

    void teardown() final
    {
        // Destroy the unit under test
        PwmService_dtor();
        mUnderTest = nullptr;

        // Clear out the cpputest mock subsystem
        mock().clear();

        // Tear down (destroy) the cpputest-for-qpc environment
        cms::test::qf_ctrl::Teardown();
    }
};

TEST(PwmServiceTests, given_init_when_created_then_does_not_crash)
{
    // setup() is automatically called by cpputest, which creates our
    // unit under test fully representing this trivial starting test.
}
