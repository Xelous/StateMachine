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

int main()
{
    xelous::EventSystem::Create();
    auto theLightSwitch = xelous::StateMachine::Create("LightSwitch", new xelous::LightOffState());
    auto theLightSwitchRef = theLightSwitch->GetReference();
    xelous::EventSystem::Get()->RegisterStateMachine(theLightSwitchRef);

    bool exit{ false };
    bool returnDown{ false };
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
    }
    xelous::EventSystem::Get()->UnregisterStateMachine(theLightSwitchRef);

}

//void oldcode()
//{
//
//    //Roller();
//
//
//
//    std::cout << StartEvent::Id << " " << PayLoadEvent::Id << " " << StopEvent::Id << std::endl;
//
//
//    StartEvent* se = new StartEvent();
//
//    StopEvent ste;
//
//    PayLoadEvent* pe = new PayLoadEvent();
//
//    auto sm = StateMachine::Create("Main");
//    sm->AddEventHandler(StartEvent::Id, HelloWorld);
//
//    auto ap = sm->GetReference();
//    EventSystem::Get()->RegisterStateMachine(ap);
//
//    EventSystem::Get()->RaiseEvent<StartEvent>(se);
//
//    EventSystem::Get()->RaiseEvent<PayLoadEvent>(pe);
//
//    std::cout << pe->GetMessage() << std::endl;
//
//    EventSystem::Get()->RaiseEvent<PayLoadEvent>(pe);
//    std::cout << pe->GetMessage() << std::endl;
//
//    volatile int countThisPass = pe->GetCounter();
//    int waits = 0;
//    while (pe->GetCounter() < 99)
//    {
//        countThisPass = pe->GetCounter();
//        pe->Reset();
//        EventSystem::Get()->RaiseEvent<PayLoadEvent>(pe);
//        EventSystem::Get()->RaiseEvent<StartEvent>(nullptr);
//        waits = 0;
//        while (countThisPass >= pe->GetCounter())
//        {
//            std::this_thread::sleep_for(std::chrono::microseconds(100));
//            ++waits;
//        }
//
//        std::cout << "Total waits on SM to process: " << waits << std::endl;
//    }
//
//    EventSystem::Get()->RaiseEvent(&ste);
//
//    while (!sm->HasExited())
//    {
//        std::cout << "Waiting for Sm to Exit" << std::endl;
//        std::this_thread::sleep_for(std::chrono::seconds(1));
//    }
//
//    delete pe;
//    delete se;
//
//    sm.reset();
//}

//namespace GlobalCounterTests
//{
//#include "counter.hpp"
//
//
//    DefineCompileTimeCounter(GlobalCounter1);
//
//    enum class ValuesAA
//    {
//        A = GlobalCounter1Next(),
//        B,
//        C,
//        D,
//        Max
//    };
//
//    enum class ValuesBB
//    {
//        A = GlobalCounter1Next(),
//        B,
//        C,
//        D,
//        Max
//    };
//
//    template<typename EnumType>
//    uint64_t EnumToUint64(const EnumType& value)
//    {
//        static_assert(std::is_enum<EnumType>::value);
//        return static_cast<uint64_t>(value);
//    }
//
//    template<typename EnumType, class = typename std::enable_if<std::is_enum<EnumType>::value>::type>
//    std::ostream& operator<<(std::ostream& stream,
//                             EnumType value)
//    {
//        stream << static_cast<uint64_t>(value);
//        return stream;
//    }
//
//    DefineCompileTimeCounter(Jon);
//    DefineCompileTimeCounter(Another);
//
//    void Roller()
//    {
//        std::cout << ValuesAA::A << std::endl;
//        std::cout << EnumToUint64(ValuesAA::A) << std::endl;
//        std::cout << EnumToUint64(ValuesAA::B) << std::endl;
//        std::cout << EnumToUint64(ValuesAA::C) << std::endl;
//        std::cout << EnumToUint64(ValuesAA::D) << std::endl;
//        std::cout << "----" << std::endl;
//
//        std::cout << EnumToUint64(ValuesBB::A) << std::endl;
//        std::cout << EnumToUint64(ValuesBB::B) << std::endl;
//        std::cout << EnumToUint64(ValuesBB::C) << std::endl;
//        std::cout << EnumToUint64(ValuesBB::D) << std::endl;
//        std::cout << "----" << std::endl;
//
//        constexpr auto one = JonNext();
//        constexpr auto two = JonNext();
//        constexpr auto three = JonNext();
//
//        constexpr auto anotherOne = AnotherNext();
//        constexpr auto anotherTwo = AnotherNext();
//        constexpr auto anotherThree = AnotherNext();
//
//        std::cout << one << " " << two << " " << three << std::endl;
//        std::cout << anotherOne << " " << anotherTwo << " " << anotherThree << std::endl;
//
//        constexpr int a = GlobalCounter1Next();
//        constexpr int b = GlobalCounter1Next();
//        constexpr int c = GlobalCounter1Next();
//
//        std::cout << a << " " << b << " " << c << std::endl;
//    }
//}