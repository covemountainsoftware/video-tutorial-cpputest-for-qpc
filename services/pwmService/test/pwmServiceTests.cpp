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
#include <array>

// the cpputest headers must always be last
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

Q_DEFINE_THIS_MODULE("pwmServiceTests")

TEST_GROUP(PwmServiceTests)
{
    QActive* mUnderTest         = nullptr;
    std::array<const QEvt*, 10> underTestEventQueueStorage;

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

        underTestEventQueueStorage.fill(nullptr);
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

    void startServiceUnderTest()
    {
        using namespace cms::test;
        // Initialize the PWM to off

        //mock: expect PWM Init
        mock().expectOneCall("PwmInit").andReturnValue(true);
        //mock: expect PWM off
        mock().expectOneCall("PwmOff").andReturnValue(true);
        //Start the AO under test

        QACTIVE_START(mUnderTest, qf_ctrl::UNIT_UNDER_TEST_PRIORITY,
                      underTestEventQueueStorage.data(), underTestEventQueueStorage.size(),
                      nullptr, 0, nullptr);

        //after doing anything with QF/QP, recommend giving it some processing time
        qf_ctrl::ProcessEvents();

        //mock: check expectations
        mock().checkExpectations();

        //ignore published event requirement at this time.
    }
};

TEST(PwmServiceTests, given_init_when_created_then_does_not_crash)
{
    // setup() is automatically called by cpputest, which creates our
    // unit under test fully representing this trivial starting test.
}

TEST(PwmServiceTests, given_initialized_when_started_then_init_the_pwm_to_off)
{
    //helper method fully tests this requirement
    startServiceUnderTest();
}

TEST(PwmServiceTests, given_started_when_pwm_on_event_then_sets_the_pwm_to_expected_value)
{
    //  Subscribe to PWM On event (with percentage [ 0.0f … 1.0f ])
    using namespace cms::test;
    constexpr float TEST_PERCENT = 0.4f;

    startServiceUnderTest();
    //service is now started.

    //allocate event to publish, same as firmware would
    auto e = Q_NEW(PwmServiceOnRequestEvent, PWM_REQUEST_ON_SIG);
    e->percent = TEST_PERCENT;

    //mock: expect pwm on call with expected percent value
    mock().expectOneCall("PwmOn").withParameter("percent", TEST_PERCENT).andReturnValue(true);
    //use helper method to publish and give processing time
    qf_ctrl::PublishAndProcess(&e->super);

    mock().checkExpectations();

    //again, ignore the requirement to publish a status event for now
}

//  Publish PWM Status when On is complete
//  When On, the AO must refresh the PWM every 250 milliseconds.
//Subscribe to PWM Off event
//  Publish PWM Status when Off is complete
//Receive via Post: Factory Test Request Event, process when Off, otherwise assert.
//  Post back to requestor pass/fail and the uint16 device ID of the PWM