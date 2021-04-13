#include "State.h"

#include <string_view>
#include <iostream>
#include "EventSystem.h"

namespace
{
    void Message(const std::string_view message)
    {
#ifdef _DEBUG
        std::cout << message << std::endl;
#endif
        // if not debug, intentionally empty
    }
}

namespace xelous
{    
    StateBase::StateBase(const char* const name)
        : Name(name)
    {
        Message("State Constructor [" + std::string(name) + "]");
    }

    StateBase::~StateBase()
    {
        Message("State Destructor [" + GetName() + "]");
    }

    void StateBase::Enter()
    {
        OnEnter();
    }

    void StateBase::Exit()
    {
        OnExit();
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

    State::~State()
    {
        ExitChild();
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

    void State::ExitChild()
    {
        if (HasChild())
        {            
            State* temp {nullptr};
            std::swap(mChild, temp);
            if (temp)
            {
                delete temp;
                temp = nullptr;
            }
        }
    }

    void State::ProcessEventMessage(BaseEvent* const event,
                                    ActionResult& result,
                                    bool& handled)
    {
        handled = false;
        result.first = ActionResultCode::NoStateChange;

        if (event)
        {            
            auto found = mRegisteredActions.find(event->EventIdCode());
            if (found != mRegisteredActions.end())
            {
                bool didHandle{ false };
                const auto& functionList = found->second;
                for (const auto& registeredFunction : functionList)
                {
                    didHandle = registeredFunction(event, result);
                }
                if (!handled && didHandle)
                {
                    handled = true;
                }
            }            
        }
    }
}