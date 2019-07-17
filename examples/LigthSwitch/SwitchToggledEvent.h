#ifndef SWITCH_TOGGLED_EVENT_HEADER
#define SWITCH_TOGGLED_EVENT_HEADER

#include "../../StateMachine/Event.h"

namespace xelous
{
    class SwitchToggledEvent : public Event<EventId, 123456>
    {
    };
}


#endif