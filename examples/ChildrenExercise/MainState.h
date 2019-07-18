#ifndef MAIN_STATE_HEADER
#define MAIN_STATE_HEADER

#include "../../StateMachine/State.h"

namespace xelous
{
    StateDefinitionHelper(MainState)   

        MainState();

    private:
        ActionFunctionHelper(OnEnterChild);
        ActionFunctionHelper(OnExitChild);        
    };
}

#endif