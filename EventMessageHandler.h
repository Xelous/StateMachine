#pragma once

#include <mutex>
#include <map>
#include "Event.h"
#include "ActionResult.h"
#include "counter.hpp"

namespace xelous
{
#ifndef AddEventHandlerHelper
#define AddEventHandlerHelper(HandlerName_, EventId_, ClassFunctionName_)			\
	ActionFunction HandlerName_ = std::bind(						\
		ClassFunctionName_,											\
		this,														\
		std::placeholders::_1,										\
		std::placeholders::_2);										\
	if (!this->AddEventHandler(										\
			EventId_,												\
			HandlerName_))											\
	{																\
		std::cout << "Failed to Add handler for Event [" << EventId_ << "] against '" << ClassFunctionName_ << "'\r\n";	\
	}
#endif

#ifndef ActionFunctionHelper
#define ActionFunctionHelper(FunctionName_)                         \
    const bool FunctionName_ (Event* const theEventIn, ActionResult& actionResultOut)
#endif

	using ActionFunction = std::function<const bool(
		Event* const,
		ActionResult&)>;

	class EventMessageHandler
	{
	protected:
		std::mutex mLock;
		std::map<EventId, ActionFunction> mRegisteredActions;

		virtual void ProcessEventMessage(Event* const event, ActionResult& result, bool& handled) = 0;

	public:
		const bool AddEventHandler(const EventId& eventId, ActionFunction ActionFunction);
		const bool RemoveEventHandler(const EventId& eventId);
	};
}