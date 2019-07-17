#ifndef LIGHT_ON_STATE_HEADER
#define LIGHT_ON_STATE_HEADER

#include "../../StateMachine/State.h"

namespace xelous
{

    class LightOnState : public State
    {
    public:
        static constexpr const char* const sStateName = "LightOnState";

        LightOnState();

    private:
        ActionFunctionHelper(OnSwitch);
    };

}

#endif