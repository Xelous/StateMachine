#include "LightOffState.h"

#include "SwitchToggledEvent.h"
#include "LightOnState.h"

namespace xelous
{
    LightOffState::LightOffState()
        : State(LightOffState::sStateName)
    {        
        AddEventHandlerHelper(OnLightToggled, SwitchToggledEvent::Id, &LightOffState::OnSwitch);
    }

    ActionFunctionHelper(LightOffState::OnSwitch)
    {
        actionResultOut = std::make_pair(ActionResultCode::NewState, new LightOnState());
        return true;
    }
}