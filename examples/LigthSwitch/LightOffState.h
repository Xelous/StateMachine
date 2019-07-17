#ifndef LIGHT_OFF_STATE_HEADER
#define LIGHT_OFF_STATE_HEADER

#include "../../StateMachine/State.h"

namespace xelous
{
    class LightOffState : public State
    {
    public:
        static constexpr const char* const sStateName = "LightOffState";

        LightOffState();

    private:
        ActionFunctionHelper(OnSwitch);
    };
}

#endif