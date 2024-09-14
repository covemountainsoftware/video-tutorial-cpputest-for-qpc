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
#include <stddef.h>

typedef struct {
    QActive super; /* inherit QActive, via QP/C Framework C style */
} PwmService;

//internal state handlers.
static QState initial(PwmService * me, void const * par);
static QState state_of_off(PwmService * me, QEvt const * e);

static PwmService m_instance;
QActive * g_thePwmService = NULL;

void PwmService_ctor()
{
    QActive_ctor(&m_instance.super, Q_STATE_CAST(initial));
    g_thePwmService = &m_instance.super;
}

void PwmService_dtor()
{
    g_thePwmService = NULL;
}

static QState initial(PwmService * const me, void const * const par)
{
    Q_UNUSED_PAR(par);
    return Q_TRAN(&state_of_off);
}

QState state_of_off(PwmService * me, const QEvt* e)
{
    QState rtn;
    switch (e->sig) {
        default:
            rtn = Q_SUPER(&QHsm_top);
            break;
    }

    return rtn;
}
