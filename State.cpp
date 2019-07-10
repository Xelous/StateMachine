#include "State.h"

#include <iostream>
#include "EventSystem.h"

namespace xelous
{
    void Message(const std::string& message)
    {
        std::cout << message << std::endl;
    }

    StateBase::StateBase(const char* const name)
        : Name(name)
    {
    }

    const std::string StateBase::GetName() const noexcept
    {
        return std::string(Name);
    }

    void StateBase::RaiseEvent(Event<EventId, 1>* const event)
    {
        auto es = EventSystem::Get();
        if (es)
        {
            es->RaiseEvent<Event<EventId, 1>>(event);
        }
    }

    State::State(const char* const name)
        : StateBase(name)
    {
    }

    void State::Initialise()
    {
        Message("Initialising [" + GetName() + "]");
    }

    void State::OnEnter()
    {
        Message("OnEnter [" + GetName() + "]");
    }

    void State::OnExit()
    {
        Message("OnExit [" + GetName() + "]");
    }

    void State::SetChild(const State* newChild)
    {
        if (mChild)
        {
            mChild->SetChild(newChild);
        }
        auto nonConst = const_cast<State*>(newChild);
        mChild = nonConst;
        mChild->Enter();
    }

    void State::ProcessEventMessage(BaseEvent* const event,
                                    ActionResult& result,
                                    bool& handled)
    {
        result.first = ActionResultCode::NoStateChange;

        if (event)
        {
            auto find = mRegisteredActions.find(event->EventIdCode());
            if (find != mRegisteredActions.end())
            {
                if (find->second != nullptr)
                {
                    handled = find->second(event, result);
                }
            }
        }
    }
}