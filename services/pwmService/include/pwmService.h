/// @file pwmService.h
/// @brief A service (active object) for demonstrating cpputest host
///        based unit testing within the QP/C (qpc) Framework.
/// @ingroup
/// @cond
///***************************************************************************
///
///  MIT License
///
/// Contact Information:
///   Matthew Eshleman
///   https://covemountainsoftware.com
///   info@covemountainsoftware.com
///***************************************************************************
/// @endcond

#ifndef PWM_SERVICE_H
#define PWM_SERVICE_H

#include "qpc.h"
#include "pub_sub_signals.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    QEvt super; //inherit QEvt, QP/C Framework OOP C style

    float percent;
} PwmServiceOnRequestEvent;


typedef struct {
    QEvt super; //inherit QEvt, QP/C Framework OOP C style

    QActive* requester;
    QSignal  response_sig;
} PwmServiceFactoryTestRequestEvent;

typedef struct {
    QEvt super; //inherit QEvt, QP/C Framework OOP C style

    bool test_passed;
    uint16_t device_id;
} PwmServiceFactoryTestResponseEvent;


enum PostedSignals {
    PWM_REQUEST_FACTORY_TEST_SIG = MAX_PUB_SUB_SIG + 1,
    MAX_PWM_POSTED_SIGNALS
};

/**
 * opaque pointer to the active object, this pointer is
 * only valid after calling PwmService_ctor().
 * After calling PwmService_dtor(), the pointer
 * will be null.
 */
extern QActive * g_thePwmService;

/**
 * Construct the PWM Service.
 */
void PwmService_ctor();

/**
 * Destroy the PWM Service.
 * Typically only needed from a unit
 * testing environment.
 */
void PwmService_dtor();

#ifdef __cplusplus
}
#endif

#endif   // PWM_SERVICE_H
