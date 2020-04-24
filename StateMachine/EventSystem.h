#pragma once

#include <map>
#include <queue>
#include <mutex>
#include <thread>
#include <memory>
#include <atomic>
#include <vector>

#include "StateMachine.h"

namespace xelous
{
    class EventSystem;
    using EventSystemSharedPtr = std::shared_ptr<EventSystem>;
    using EventSystemWeakPtr = std::weak_ptr<EventSystem>;

    class EventSystem : public std::enable_shared_from_this<EventSystem>
    {
    private:
        static EventSystemSharedPtr sInstance;

        EventSystem();
        
        friend void* ::operator new(size_t);

        std::atomic<bool> mExitFlag {false};
        std::thread mDeliveryThread;

        std::atomic<bool> mIsRunning {false};

        std::mutex mEventQueueLock;
        std::queue<BaseEvent*> mEventQueue;

        void DequeueEvent(BaseEvent* event);

        void Start();
        void Stop();
        void DeliveryFunction();

        std::mutex mClientStateMachinesLock;
        std::vector<StateMachineWeakPtr> mClientStateMachines;

        void RaiseEvent(BaseEvent* const pEvent);

    public:
        static EventSystemSharedPtr Create();
        static EventSystemSharedPtr Get();

        ~EventSystem();

        inline EventSystemWeakPtr GetReference()
        {
            return weak_from_this();
        }

        void RegisterStateMachine(StateMachineWeakPtr& pStateMachine);
        void UnregisterStateMachine(StateMachineWeakPtr& pStateMachine);

        template<typename T>
        void RaiseEvent(T* const pEvent)
        {
            if (pEvent != nullptr)
            {
                RaiseEvent(reinterpret_cast<BaseEvent*>(pEvent));
            }
        }
    };
}