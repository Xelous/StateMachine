#pragma once

#include <memory>
#include <cstdint>
#include <atomic>
#include "ActionResult.h"

namespace xelous
{
    using EventId = uint64_t;

    class BaseEvent
    {
    private:
        EventId mInternalEventId;

    public:

        BaseEvent() = delete;
        BaseEvent(const EventId& eventIdCode)
            : mInternalEventId(eventIdCode)
        {
        }

        inline const EventId& EventIdCode() const noexcept
        {
            return mInternalEventId;
        }

        const bool operator==(const EventId& id) const noexcept
        {
            return id == mInternalEventId;
        }

        const bool operator==(const BaseEvent& other) const noexcept
        {
            return other.mInternalEventId == mInternalEventId;
        }
    };

    template<typename T, int Code, class = typename std::enable_if<std::is_integral<T>::value>::type>
    class Event : public BaseEvent
    {
    public:
        static const EventId Id {Code};

        Event& operator=(const Event&) = delete;
        Event& operator=(const Event&&) = delete;

        inline const bool& GetHandled() const
        {
            return mHandled.load(std::memory_order::memory_order_consume);
        }

        inline void Reset() noexcept
        {
            mHandled = false;
        }

    protected:
        Event()
            : BaseEvent(Code)
        {
        }
        Event(const Event& other) = default;
        Event(const Event&&) = delete;

        std::atomic<bool> mHandled {false};
    };
}