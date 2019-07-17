#include "EventSystem.h"

namespace xelous
{
    EventSystemSharedPtr EventSystem::sInstance {nullptr};

    EventSystem::EventSystem()
    {
        Start();
    }

    EventSystem::~EventSystem()
    {
        Stop();
    }

    void EventSystem::DequeueEvent(BaseEvent* event)
    {
        std::scoped_lock lock(mEventQueueLock);
        if (!mEventQueue.empty())
        {
            // TODO - swap to lockless
            event = mEventQueue.front();
            mEventQueue.pop();
        }
    }

    void EventSystem::Start()
    {
        mDeliveryThread = std::thread(std::bind(&EventSystem::DeliveryFunction, this));
    }

    void EventSystem::Stop()
    {
        mExitFlag = true;
        if (mDeliveryThread.joinable())
        {
            mDeliveryThread.join();
        }
    }

    void EventSystem::DeliveryFunction()
    {
        mExitFlag = false;
        mIsRunning = true;
        BaseEvent* currentEvent {};
        std::queue<BaseEvent*> localEventVersion;
        while (!mExitFlag)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(100));

            {
                // Drain the event queue in one move
                std::scoped_lock lock(mEventQueueLock);
                if (!mEventQueue.empty())
                {
                    std::swap(mEventQueue, localEventVersion);
                }
            }

            while (!localEventVersion.empty())
            {
                currentEvent = localEventVersion.front();
                localEventVersion.pop();

                std::scoped_lock lock(mClientStateMachinesLock);
                for (auto& stateMachine : mClientStateMachines)
                {
                    if (!stateMachine.expired())
                    {
                        auto local = stateMachine.lock();
                        if (local->HandleEvent(currentEvent))
                        {
                            // COUNT metrics?
                        }
                    }
                    // TODO - remove dead clients
                }
            }
        }
        mIsRunning = false;
    }

    EventSystemSharedPtr EventSystem::Create()
    {
        if (!sInstance)
        {
            sInstance = std::make_shared<EventSystem>();
        }
        return sInstance;
    }

    EventSystemSharedPtr EventSystem::Get()
    {
        return sInstance;
    }

    void EventSystem::RegisterStateMachine(StateMachineWeakPtr& pStateMachine)
    {
        std::scoped_lock lock(mClientStateMachinesLock);
        mClientStateMachines.push_back(pStateMachine);
    }

    void EventSystem::UnregisterStateMachine([[maybe_unused]] StateMachineWeakPtr& pStateMachine)
    {
        /*std::scoped_lock lock(mClientStateMachinesLock);
           for (auto& stateMachine : mClientStateMachines)
           {
            if (stateMachine.expired())
            {
                mClientStateMachines.erase(stateMachine);
            }
           }*/
    }

    void EventSystem::RaiseEvent(BaseEvent* const pEvent)
    {
        if (pEvent != nullptr)
        {
            std::scoped_lock lock(mEventQueueLock);
            mEventQueue.push(pEvent);
        }
    }
}