#include <iostream>
#include <string>
#include <memory>
#include <cassert>

#include <windows.h>

//=============================================
// Start State Machine Test
//=============================================
#include "../StateMachine/State.h"
#include "../StateMachine/Event.h"
#include "../StateMachine/ActionResult.h"
#include "../StateMachine/StateMachine.h"
#include "../StateMachine/EventSystem.h"

#include "../examples/LigthSwitch/LightOnState.h"
#include "../examples/LigthSwitch/LightOffState.h"
#include "../examples/LigthSwitch/SwitchToggledEvent.h"

#include "../examples/ChildrenExercise/MainState.h"
#include "../examples/ChildrenExercise/ChildState.h"
#include "../examples/ChildrenExercise/EnterChildEvent.h"
#include "../examples/ChildrenExercise/ExitChildEvent.h"


int main()
{
    xelous::EventSystem::Create();

    auto theLightSwitch = xelous::StateMachine::Create("LightSwitch", new xelous::LightOffState());
    auto theLightSwitchRef = theLightSwitch->GetReference();
    xelous::EventSystem::Get()->RegisterStateMachine(theLightSwitchRef);

    auto theChildTest = xelous::StateMachine::Create("ChildTest", new xelous::MainState());
    auto theChildTestRef = theChildTest->GetReference();
    xelous::EventSystem::Get()->RegisterStateMachine(theChildTestRef);

    bool exit{ false };
    bool returnDown{ false };
    bool downDown{ false };
    bool upDown{ false };
    bool oneDown{ false };
    bool twoDown{ false };
    bool threeDown{ false };
    while (!exit)
    {
        auto key = GetAsyncKeyState(VK_RETURN);
        if (key != 0)
        {
            if (!returnDown)
            {
                std::cout << "------ Switched --------" << std::endl;
                xelous::EventSystem::Get()->RaiseEvent(new xelous::SwitchToggledEvent());
                returnDown = true;
            }
        }
        else
        {
            if (returnDown)
            {
                returnDown = false;
            }
        }

        key = GetAsyncKeyState(VK_ESCAPE);
        if (key != 0)
        {
            exit = true;
        }

        key = GetAsyncKeyState(VK_DOWN);
        if (key != 0)
        {
            if (!downDown)
            {
                std::cout << "------ Down ---- " << std::endl;
                xelous::EventSystem::Get()->RaiseEvent(new xelous::EnterChildEvent());
                downDown = true;
            }
        }
        else
        {
            if (downDown)
            {
                downDown = false;
            }
        }

        key = GetAsyncKeyState(VK_UP);
        if (key != 0)
        {
            if (!upDown)
            {
                std::cout << "------ Up ------" << std::endl;
                xelous::EventSystem::Get()->RaiseEvent(new xelous::ExitChildEvent());
                upDown = true;
            }
        }
        else
        {
            if (upDown)
            {
                upDown = false;
            }
        }

        key = GetAsyncKeyState(VK_NUMPAD1);
        if (key != 0)
        {
            if (!oneDown)
            {
                std::cout << "----- One ------" << std::endl;                
                oneDown = true;
            }
        }
        else
        {
            if (oneDown)
            {
                oneDown = false;
            }
        }

        key = GetAsyncKeyState(VK_NUMPAD2);
        if (key != 0)
        {
            if (!twoDown)
            {
                std::cout << "----- Two ------" << std::endl;                
                twoDown = true;
            }
        }
        else
        {
            if (twoDown)
            {
                twoDown = false;
            }
        }

        key = GetAsyncKeyState(VK_NUMPAD3);
        if (key != 0)
        {
            if (!threeDown)
            {
                std::cout << "----- Three ------" << std::endl;                
                threeDown = true;
            }
        }
        else
        {
            if (threeDown)
            {
                threeDown = false;
            }
        }

    }
    xelous::EventSystem::Get()->UnregisterStateMachine(theChildTestRef);
    xelous::EventSystem::Get()->UnregisterStateMachine(theLightSwitchRef);
}