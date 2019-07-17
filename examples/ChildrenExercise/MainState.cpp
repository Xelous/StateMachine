#include "MainState.h"

#include "ChildState.h"
#include "EnterChildEvent.h"
#include "ExitChildEvent.h"

namespace xelous
{
    MainState::MainState()
        :
        State(MainState::sStateName)
    {
        AddEventHandlerHelper(OnEnterChild, EnterChildEvent::Id, &MainState::OnEnterChild);
        AddEventHandlerHelper(OnExitChild, ExitChildEvent::Id, &MainState::OnExitChild);
    }

    ActionFunctionHelper(MainState::OnEnterChild)
    {
        if (!this->HasChild())
        {
            actionResultOut = std::make_pair(ActionResultCode::NewChildState, new ChildState());
        }
        return true;
    }

    ActionFunctionHelper(MainState::OnExitChild)
    {
        if (this->HasChild())
        {
            actionResultOut = std::make_pair(ActionResultCode::ExitChildState, nullptr);
        }
        return true;
    }
}