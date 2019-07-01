#pragma once

#include <string>
#include <memory>
#include "Event.h"
#include "EventMessageHandler.h"

namespace xelous
{
#ifndef MakeEventLocalAs
	#define MakeEventLocalAs(EventIn_, UsableTypeOut_, VariableName_)			\
        UsableTypeOut_* VariableName_ { nullptr };                              \
        if (EventIn_ != nullptr )                                               \
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

        void RaiseEvent(Event* const event);

	protected:

		void Enter()
		{
			OnEnter();
		}

		void Exit()
		{
			OnExit();
		}
	};

	class State : public StateBase, public EventMessageHandler
	{	
	private:
		State* mChild{ nullptr };		

	public:
		State(const char* const name);

		void SetChild(const State* newChild);

		void Initialise() override;
		void OnEnter() override;
		void OnExit() override;

		void ProcessEventMessage(Event* const event, ActionResult& result, bool& handled) override;
	};


}