#include "LightOnState.h"

#include <iostream>
#include "SwitchToggledEvent.h"
#include "LightOffState.h"

namespace xelous
{
    LightOnState::LightOnState()
        : State(LightOnState::sStateName)
    {        
        AddEventHandlerHelper(OnLightToggled, SwitchToggledEvent::Id, &LightOnState::OnSwitch);
    }

    ActionFunctionHelper(LightOnState::OnSwitch)
    {        
        actionResultOut = std::make_pair(ActionResultCode::NewState, new LightOffState());
        return true;
    }
}