#include "Event.h"

namespace xelous
{
	const bool Event::operator==(const EventId& id) const
	{
		return Id == id;
	}

	const bool Event::operator==(const Event& other) const
	{
		return other.Id == Id;
	}

	Event::Event(const Event& other)
		:
		Id(other.Id)
	{

	}
	
	Event::Event(const EventId& id)
		:
		Id(id)
	{
	}
}