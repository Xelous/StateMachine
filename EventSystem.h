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
    class Event;

    class EventSystem;
    using EventSystemSharedPtr = std::shared_ptr<EventSystem>;
    using EventSystemWeakPtr = std::weak_ptr<EventSystem>;

    class EventSystem : public std::enable_shared_from_this<EventSystem>
    {
    private:
        static EventSystemSharedPtr sInstance;

        EventSystem();

        friend class std::_Ref_count_obj<EventSystem>;

        std::atomic<bool> mExitFlag{ false };
        std::thread mDeliveryThread;

        std::atomic<bool> mIsRunning{ false };

        std::mutex mEventQueueLock;
        std::queue<Event*> mEventQueue;

        void DequeueEvent(Event* event);

        void Start();
        void Stop();
        void DeliveryFunction();

        std::mutex mClientStateMachinesLock;
        std::vector<StateMachineWeakPtr> mClientStateMachines;        
        
    public:
        static EventSystemSharedPtr Create();        
        static EventSystemSharedPtr Get();

        ~EventSystem();

        inline EventSystemWeakPtr GetReference() { return weak_from_this(); }

        void RegisterStateMachine(StateMachineWeakPtr& pStateMachine);        

        void RaiseEvent(Event *const pEvent);

    };

}