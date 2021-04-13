#pragma once

#include <string>
#include <memory>
#include "Event.h"
#include "EventMessageHandler.h"

namespace xelous
{
#ifndef MakeEventLocalAs
        #define MakeEventLocalAs(EventIn_, UsableTypeOut_, VariableName_)                       \
    UsableTypeOut_* VariableName_ {nullptr};                              \
    if (EventIn_ != nullptr)                                               \
    {                                                                       \
        VariableName_ = reinterpret_cast<UsableTypeOut_*>(EventIn_);         \
    }
#endif

    class StateMachine;

    class StateBase;
    class StateBase
    {
    private:
        friend class StateMachine;

        const char* Name;

    public:
        StateBase(const char* const name);

        virtual void Initialise() = 0;
        virtual void OnEnter() = 0;
        virtual void OnExit() = 0;

        const std::string GetName() const noexcept;

        void RaiseEvent(Event<EventId, 1>* const event);        

    protected:
        
        ~StateBase();        

        void Enter();

        void Exit();
    };

#ifndef StateDefinitionHelper
#define StateDefinitionHelper(StateName_)       \
class StateName_ : public State  \
    {\
    public: \
        static constexpr const char* const sStateName = #StateName_ ;
#endif

    class State : public StateBase, public EventMessageHandler
    {
    private:
        // TODO - make smart pointer
        State* mChild {nullptr};

        friend class StateMachine;

        void SetChild(const State* newChild);

        void Initialise() override;
        void OnEnter() override;
        void OnExit() override;

        void ExitChild();

    public:
        State(const char* const name);
        ~State();

        void ProcessEventMessage(BaseEvent* const event,
                                 ActionResult& result,
                                 bool& handled) override;

        inline const bool HasChild() const noexcept
        {
            return mChild != nullptr;
        }
    };
}