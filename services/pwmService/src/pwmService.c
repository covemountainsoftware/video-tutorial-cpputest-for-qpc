/// @brief A sample/demonstration QP/C QActive based service used
///        to demonstrate host based unit testing of a QP/C active object
///        using cpputest and the cpputest-for-qpc support code.
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

#include "pwmService.h"
#include "pwm.h"
#include "qsafe.h"
#include "pub_sub_signals.h"
#include "bspTicks.h"
#include <stddef.h>

Q_DEFINE_THIS_MODULE("PwmService")

typedef struct {
    QActive super; /* inherit QActive, via QP/C Framework C style */

    //member variables of PwmService
    float current_percent;
    QTimeEvt refresh_timer;
} PwmService;

enum InternalSignals {
    PWM_REFRESH_SIG = MAX_PUB_SUB_SIG + 1
};

static const uint32_t TICKS_PER_REFRESH = BSP_TICKS_PER_SECOND / 4;

//internal state handlers.
static QState initial(PwmService * me, void const * par);
static QState state_of_off(PwmService * me, QEvt const * e);
static QState state_of_on(PwmService * me, QEvt const * e);

static PwmService m_instance;
QActive * g_thePwmService = NULL;

void PwmService_ctor()
{
    QActive_ctor(&m_instance.super, Q_STATE_CAST(initial));
    g_thePwmService = &m_instance.super;
}

void PwmService_dtor()
{
    QTimeEvt_disarm(&m_instance.refresh_timer);
    g_thePwmService = NULL;
}

static QState initial(PwmService * const me, void const * const par)
{
    Q_UNUSED_PAR(par);
    QActive_subscribe(&me->super, PWM_REQUEST_ON_SIG);
    QActive_subscribe(&me->super, PWM_REQUEST_OFF_SIG);
    QTimeEvt_ctorX(&me->refresh_timer, &me->super, PWM_REFRESH_SIG, 0U);
    bool ok = PwmInit();
    Q_ASSERT(true == ok);
    return Q_TRAN(&state_of_off);
}

QState state_of_off(PwmService * me, const QEvt* e)
{
    static const QEvt OffStatusEvent = QEVT_INITIALIZER(PWM_IS_OFF_SIG);
    QState rtn;

    switch (e->sig) {
        case Q_ENTRY_SIG: {
            bool ok = PwmOff();
            Q_ASSERT(true == ok);
            QF_PUBLISH(&OffStatusEvent, &me->super);
            rtn = Q_HANDLED();
            break;
        }
        case PWM_REQUEST_ON_SIG: {
            const PwmServiceOnRequestEvent* event = (const PwmServiceOnRequestEvent*)e;
            me->current_percent = event->percent;
            rtn = Q_TRAN(&state_of_on);
            break;
        }

        default:
            rtn = Q_SUPER(&QHsm_top);
            break;
    }

    return rtn;
}

QState state_of_on(PwmService * me, const QEvt* e)
{
    static const QEvt OnStatusEvent = QEVT_INITIALIZER(PWM_IS_ON_SIG);
    QState rtn;

    switch (e->sig) {
        case Q_ENTRY_SIG: {
            QTimeEvt_armX(&me->refresh_timer, TICKS_PER_REFRESH, TICKS_PER_REFRESH);
            bool ok = PwmOn(me->current_percent);
            Q_ASSERT(true == ok);
            QF_PUBLISH(&OnStatusEvent, &me->super);
            rtn = Q_HANDLED();
            break;
        }
        case Q_EXIT_SIG: {
            QTimeEvt_disarm(&me->refresh_timer);
            rtn = Q_HANDLED();
            break;
        }

        case PWM_REQUEST_OFF_SIG:
            rtn = Q_TRAN(&state_of_off);
            break;

        case PWM_REFRESH_SIG: {
            bool ok = PwmOn(me->current_percent);
            Q_ASSERT(true == ok);
            rtn = Q_HANDLED();
            break;
        }

        default:
            rtn = Q_SUPER(&QHsm_top);
            break;
    }

    return rtn;
}
