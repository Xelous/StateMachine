#pragma once

#include <queue>
#include <mutex>
#include <memory>
#include <string>
#include <thread>
#include <chrono>
#include <atomic>
#include <cstdint>
#include <functional>

#include "ActionResult.h"
#include "Event.h"
#include "State.h"


namespace xelous
{
    class StateMachine;
    using StateMachineSharedPtr = std::shared_ptr<StateMachine>;
    using StateMachineWeakPtr = std::weak_ptr<StateMachine>;

    using SleepPeriod = std::chrono::milliseconds;

    class StateMachine : public std::enable_shared_from_this<StateMachine>, public EventMessageHandler
    {
    public:
        enum class ProcessingPriority
        {
            Ultra = 0,
            High = 1,
            Normal = 100,
            Low = 1000,
            UltraLow = 10000
        };

        const std::string Name;

        StateMachine() = delete;

        ~StateMachine();

        const bool HandleEvent(BaseEvent* const e,
                               const bool immediate = false);

        inline const bool HasRun() const
        {
            return mHasRun;
        }
        inline const bool HasExited() const
        {
            return mHasExited;
        }

        inline StateMachineWeakPtr GetReference()
        {
            return weak_from_this();
        }

        static StateMachineSharedPtr Create(const std::string& name,
                                            State* initialState = nullptr);    

    protected:
        StateMachine(const std::string& name,
                     State* initialState);

    private:
        friend class std::_Ref_count_obj<StateMachine>;

        ProcessingPriority mProcessingPriority {ProcessingPriority::Normal};
        State* mCurrentState {nullptr};
        std::atomic<bool> mMasterExitFlag {false};
        std::atomic<bool> mHasRun {false};
        std::atomic<bool> mHasExited {false};
        std::thread mStateMachineThread;

        // TODO - Swap to boost lock free queue later
        std::mutex mEventQueueLock {};
        std::queue<BaseEvent*> mEventQueue {};

        void Start();
        void Stop();
        void ProcessFunction();
        void SleepProcess();

        void HandleResultAtStateMachine(const ActionResult& result);

        void EnqueueEvent(BaseEvent* const e);
        void DequeueEvent(BaseEvent** e);
        const bool ImmediateProcessEventMessage(BaseEvent* const event);
        void ProcessEventMessage(BaseEvent* const event,
                                 ActionResult& result,
                                 bool& handled) override;

        void EnterState(const State* newState);
        void ExitState();
        void EnterChildState(const State* newState);
        void ExitChildState();
        void ExitStateMachine();
        void ReportError();
    };
}