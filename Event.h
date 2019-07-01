#pragma once

#include <memory>
#include <cstdint>
#include "ActionResult.h"

namespace xelous
{
	using EventId = uint64_t;

	class Event;    
	class Event : public std::enable_shared_from_this<Event>
	{
	public:
		const EventId Id;

		Event& operator=(const Event&) = delete;
		Event& operator=(const Event&&) = delete;

		const bool operator==(const EventId& id) const;
		const bool operator==(const Event& other) const;		

		inline const bool& GetHandled() const { return mHandled; }

		inline void Reset() { mHandled = false; }

	protected:
		Event() = delete;
		Event(const Event& other);
		Event(const Event&&) = delete;
		Event(const EventId& id);			

		bool mHandled{ false };
	};

}