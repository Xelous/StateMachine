#pragma once

#include <iostream>
#include <mutex>
#include <map>
#include <vector>
#include <queue>
#include <functional>
#include "Event.h"
#include "ActionResult.h"

namespace xelous
{
#ifndef AddEventHandlerHelper
#define AddEventHandlerHelper(HandlerName_, EventId_, ClassFunctionName_)                       \
    ActionFunction HandlerName_ = std::bind(                                                    \
        ClassFunctionName_,                                                                     \
        this,                                                                                   \
        std::placeholders::_1,                                                                  \
        std::placeholders::_2);                                                                 \
    if (!this->AddEventHandler(                                                                 \
            EventId_,                                                                           \
            HandlerName_))                                                                      \
    {                                                                                           \
        std::cout << "Failed to Add handler for Event [" << EventId_ << "] against '" << ClassFunctionName_ << "'\r\n"; \
    }
#endif

#ifndef ActionFunctionHelper
#define ActionFunctionHelper(FunctionName_)                         \
    const bool FunctionName_([[maybe_unused]] BaseEvent* const theEventIn, [[maybe_unused]] ActionResult& actionResultOut)
#endif

    using ActionFunction = std::function<const bool (
                                             BaseEvent* const,
                                             ActionResult&)>;

    using ActionFunctionList = std::vector<ActionFunction>;

    class EventMessageHandler
    {
    protected:
        std::mutex mLock;
        std::map<EventId, ActionFunctionList> mRegisteredActions;

        std::mutex mEventQueueLock;
        std::queue<BaseEvent*> mEventQueue;

        virtual void ProcessEventMessage(BaseEvent* const event,
                                         ActionResult& result,
                                         bool& handled) = 0;

    public:
        const bool AddEventHandler(const EventId& eventId,
                                   ActionFunction ActionFunction);
        const bool RemoveEventHandlers(const EventId& eventId);
    };
}