#include <iostream>
#include <string>
#include <memory>
#include <cassert>

#include "counter.hpp"


DefineCompileTimeCounter(GlobalCounter1);

enum class ValuesAA
{
    A = GlobalCounter1Next(),
    B,
    C,
    D,
    Max
};

enum class ValuesBB
{
    A = GlobalCounter1Next(),
    B,
    C,
    D,
    Max
};

template<typename EnumType>
uint64_t EnumToUint64(const EnumType& value)
{
    static_assert(std::is_enum<EnumType>::value);
    return static_cast<uint64_t>(value);
}

template<typename EnumType, class = typename std::enable_if<std::is_enum<EnumType>::value>::type>
std::ostream& operator<<(std::ostream& stream,
                         EnumType value)
{
    stream << static_cast<uint64_t>(value);
    return stream;
}

//std::ostream& operator<<(std::ostream& stream,
//                         ValuesAA value)
//{
//    stream << static_cast<uint64_t>(value);
//    return stream;
//}

DefineCompileTimeCounter(Jon);
DefineCompileTimeCounter(Another);

void Roller()
{
    std::cout << ValuesAA::A << std::endl;
    std::cout << EnumToUint64(ValuesAA::A) << std::endl;
    std::cout << EnumToUint64(ValuesAA::B) << std::endl;
    std::cout << EnumToUint64(ValuesAA::C) << std::endl;
    std::cout << EnumToUint64(ValuesAA::D) << std::endl;
    std::cout << "----" << std::endl;

    std::cout << EnumToUint64(ValuesBB::A) << std::endl;
    std::cout << EnumToUint64(ValuesBB::B) << std::endl;
    std::cout << EnumToUint64(ValuesBB::C) << std::endl;
    std::cout << EnumToUint64(ValuesBB::D) << std::endl;
    std::cout << "----" << std::endl;

    constexpr auto one = JonNext();
    constexpr auto two = JonNext();
    constexpr auto three = JonNext();

    constexpr auto anotherOne = AnotherNext();
    constexpr auto anotherTwo = AnotherNext();
    constexpr auto anotherThree = AnotherNext();

    std::cout << one << " " << two << " " << three << std::endl;
    std::cout << anotherOne << " " << anotherTwo << " " << anotherThree << std::endl;

    constexpr int a = GlobalCounter1Next();
    constexpr int b = GlobalCounter1Next();
    constexpr int c = GlobalCounter1Next();

    std::cout << a << " " << b << " " << c << std::endl;
}


class Bar : public std::enable_shared_from_this<Bar>
{
public:
    const int index {JonNext()};

    void Print()
    {
        std::cout << "Bar [" << index << "]" << std::endl;
    }

    std::shared_ptr<Bar> GetShared()
    {
        return shared_from_this();
    }

    std::weak_ptr<Bar> GetWeak()
    {
        return weak_from_this();
    }
};

#include <vector>


#include <string>

#include <map>
#include <thread>
#include <functional>

#include "State.h"
#include "Event.h"
#include "ActionResult.h"
#include "StateMachine.h"
#include "EventSystem.h"


using namespace xelous;

class StartEvent : public Event<EventId, 1>
{
};

class StopEvent : public Event<EventId, 2>
{
};

class PayLoadEvent : public Event<EventId, 3>
{
public:
    inline const std::string& GetMessage() const
    {
        return mMessage;
    }

    void SetMessage(const std::string& pMessage)
    {
        mMessage = pMessage;
    }

    void operator++()
    {
        ++counter;
    }

    inline const int& GetCounter() const
    {
        return counter;
    }

private:
    std::string mMessage {""};
    int counter {0};
};


class AState : public State
{
public:
    AState()
        : State("AState")
    {
        AddEventHandlerHelper(af1, StartEvent::Id, &AState::OnAnother);
        AddEventHandlerHelper(af2, StopEvent::Id, &AState::OnStop);
        AddEventHandlerHelper(af3, PayLoadEvent::Id, &AState::OnPayload);
    }

    ActionFunctionHelper(OnAnother)
    {
        actionResultOut.first = ActionResultCode::ExitState;
        std::cout << "AState::OnAnother" << std::endl;
        return true;
    }

    ActionFunctionHelper(OnStop)
    {
        actionResultOut.first = ActionResultCode::ExitStateMachine;
        return true;
    }

    ActionFunctionHelper(OnPayload)
    {
        if (theEventIn != nullptr)
        {
            MakeEventLocalAs(theEventIn, PayLoadEvent, pe);

            if (pe->GetCounter() == 0)
            {
                pe->SetMessage("We just set the message");
            }
            else if (pe->GetCounter() == 1)
            {
                pe->SetMessage("We just changed that message");
            }
            else
            {
                std::cout << std::to_string(pe->GetCounter()) << std::endl;
            }
            ++(*pe);
        }
        return true;
    }
};

const bool HelloWorld(BaseEvent* const e,
                      [[maybe_unused]] ActionResult& ar)
{
    std::cout << "Event Came in: " << e->EventIdCode() << std::endl;

    ar.first = ActionResultCode::NewState;
    ar.second = new AState();


    return true;
}


class SomethingElse
{
public:
    std::unique_ptr<int> block {nullptr};
    int shared {0};

    SomethingElse()
        : block(std::make_unique<int>(8192000))
    {
    }

    ~SomethingElse()
    {
    }
};

int main()
{
    Roller();

    EventSystem::Create();

    std::cout << StartEvent::Id << " " << PayLoadEvent::Id << " " << StopEvent::Id << std::endl;


    StartEvent* se = new StartEvent();

    StopEvent ste;

    PayLoadEvent* pe = new PayLoadEvent();

    auto sm = StateMachine::Create("Main");
    sm->AddEventHandler(StartEvent::Id, HelloWorld);

    auto ap = sm->GetReference();
    EventSystem::Get()->RegisterStateMachine(ap);

    EventSystem::Get()->RaiseEvent<StartEvent>(se);

    EventSystem::Get()->RaiseEvent<PayLoadEvent>(pe);

    std::cout << pe->GetMessage() << std::endl;

    EventSystem::Get()->RaiseEvent<PayLoadEvent>(pe);
    std::cout << pe->GetMessage() << std::endl;

    volatile int countThisPass = pe->GetCounter();
    int waits = 0;
    while (pe->GetCounter() < 99)
    {
        countThisPass = pe->GetCounter();
        pe->Reset();
        EventSystem::Get()->RaiseEvent<PayLoadEvent>(pe);
        EventSystem::Get()->RaiseEvent<StartEvent>(nullptr);
        waits = 0;
        while (countThisPass >= pe->GetCounter())
        {
            std::this_thread::sleep_for(std::chrono::microseconds(100));
            ++waits;
        }

        std::cout << "Total waits on SM to process: " << waits << std::endl;
    }

    EventSystem::Get()->RaiseEvent(&ste);

    while (!sm->HasExited())
    {
        std::cout << "Waiting for Sm to Exit" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    delete pe;
    delete se;

    sm.reset();




    auto thing = std::make_shared<SomethingElse>();
    ++thing->shared;

    std::weak_ptr<SomethingElse> weak = thing;
    ++thing->shared;

    thing.reset();

    if (!weak.expired())
    {
        auto actual = weak.lock();
        ++actual->shared;
        std::cout << actual->shared << std::endl;
    }



    /*A aa = A::One;
       int av = static_cast<int>(aa);

       av++;
       A bb = static_cast<A>(av);

       av++;
       A cc = static_cast<A>(av);*/




    std::vector<std::string> items
    {
        "Hello"
        //ReturnString("Hello World")
        //ReturnString("Yes"),
        //ReturnString("Missing has a space"),
        //ReturnString("No")
    };

    for (auto s : items)
    {
        std::cout << s << std::endl;
    }


    std::cout << "-----------------" << std::endl;



    auto b = std::make_shared<Bar>();
    std::cout << "Uses: " << b.use_count() << std::endl;

    auto bp = b->GetShared();
    std::cout << "Uses: " << b.use_count() << std::endl;

    bp->Print();
    std::cout << "Uses: " << b.use_count() << std::endl;

    auto bw = b->GetWeak();
    std::cout << "Uses: " << b.use_count() << std::endl;
    if (!bw.expired())
    {
        auto sp = bw.lock();
        std::cout << "Uses: " << b.use_count() << std::endl;
        sp->Print();
    }
    std::cout << "Uses: " << b.use_count() << std::endl;

    //Error e;
    //std::cout << static_cast<int>(Error::Code::None) << std::endl;
    //std::cout << e.Message() << std::endl;
}