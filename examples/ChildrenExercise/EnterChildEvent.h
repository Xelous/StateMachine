#ifndef ENTER_CHILD_EVENT_HEADER
#define ENTER_CHILD_EVENT_HEADER

#include "../../StateMachine/Event.h"

namespace xelous
{
    class EnterChildEvent : public Event<EventId, 777>
    {
    };
}

#endif