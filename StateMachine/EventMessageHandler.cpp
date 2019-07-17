#include "EventMessageHandler.h"

namespace xelous
{
	const bool EventMessageHandler::AddEventHandler(const EventId& eventId, ActionFunction ActionFunction)
	{
		bool result{ false };
		std::scoped_lock lock(mLock);
		auto found = mRegisteredActions.find(eventId);
		if (found == mRegisteredActions.end())
		{
			mRegisteredActions.emplace(
				std::make_pair(
					eventId,
					ActionFunction));
			result = true;
		}
		return result;
	}

	const bool EventMessageHandler::RemoveEventHandler(const EventId& eventId)
	{
		bool result{ false };
		std::scoped_lock lock(mLock);

		mRegisteredActions.erase(eventId);
		
		return result;
	}

}