#include "StateMachine.h"

#ifdef _DEBUG
    #include <iostream>
#endif

namespace xelous
{
    StateMachineSharedPtr StateMachine::Create(const std::string& name,
                                               State* initialState)
    {
        return std::shared_ptr<StateMachine>(new StateMachine(name, initialState));
    }

    StateMachine::StateMachine(const std::string& name,
                               State* initialState)
        : Name(name)
        , mCurrentState(initialState)
    {
        Start();        
    }

    StateMachine::~StateMachine()
    {
        Stop();
    }

    const bool StateMachine::HandleEvent(BaseEvent* const e,
                                         const bool immediate)
    {
        bool result {true};

        if (HasRun() && !HasExited())
        {
            if (e != nullptr)
            {
                if (immediate)
                {
                    result = ImmediateProcessEventMessage(e);
                }
                else
                {
                    EnqueueEvent(e);
                }
            }
        }

        return result;
    }

    void StateMachine::Start()
    {
        mMasterExitFlag = false;
        mStateMachineThread = std::thread(std::bind(&StateMachine::ProcessFunction, this));
    }

    void StateMachine::Stop()
    {
        mMasterExitFlag = true;
        if (mStateMachineThread.joinable())
        {
            mStateMachineThread.join();
        }
    }

    void StateMachine::ProcessFunction()
    {
        bool handled {false};
        BaseEvent* theEvent {nullptr};
        ActionResult theResult {ActionResultCode::Nothing, nullptr};

        if (!mMasterExitFlag)
        {
            mHasRun = true;
        }

        while (!mMasterExitFlag)
        {
            handled = false;

            SleepProcess();

            DequeueEvent(&theEvent);
            if (theEvent != nullptr)
            {
                ProcessEventMessage(theEvent, theResult, handled);
                if (handled)
                {
                    HandleResultAtStateMachine(theResult);
                }
            }
        }

        mHasExited = true;
    }

    void StateMachine::SleepProcess()
    {
        std::this_thread::sleep_for(
            std::chrono::milliseconds(
                static_cast<uint32_t>(
                    mProcessingPriority)));
    }

    void StateMachine::EnqueueEvent(BaseEvent* const e)
    {
        std::scoped_lock lock(mEventQueueLock);
        mEventQueue.push(e);
    }

    void StateMachine::DequeueEvent(BaseEvent** e)
    {
        std::scoped_lock lock(mEventQueueLock);
        if (!mEventQueue.empty())
        {
            *e = mEventQueue.front();
            mEventQueue.pop();
        }
        else
        {
            *e = nullptr;
        }
    }

    const bool StateMachine::ImmediateProcessEventMessage(BaseEvent* const event)
    {
        bool result {false};
        ActionResult actionResult;
        if (event != nullptr)
        {
            ProcessEventMessage(event, actionResult, result);
            if (result)
            {
                HandleResultAtStateMachine(actionResult);
            }
        }
        return result;
    }

    void StateMachine::ProcessEventMessage(BaseEvent* const event,
                                           ActionResult& result,
                                           bool& handled)
    {
        if (event != nullptr)
        {
            if (mCurrentState)
            {
                mCurrentState->ProcessEventMessage(event, result, handled);
            }

            if (!handled &&
                !mRegisteredActions.empty())
            {
                auto found = mRegisteredActions.find(event->EventIdCode());
                if (found != mRegisteredActions.end())
                {
                    auto function = found->second;

                    handled = function(event, result);
                }
            }
        }
    }

    void StateMachine::HandleResultAtStateMachine(const ActionResult& result)
    {
        switch (result.first)
        {
        case ActionResultCode::Nothing:
            break;

        case ActionResultCode::NewState:
            EnterState(result.second);
            break;

        case ActionResultCode::NewChildState:
            EnterChildState(result.second);
            break;

        case ActionResultCode::ExitChildState:
            ExitChildState();
            break;        

        case ActionResultCode::ExitStateMachine:
            ExitStateMachine();
            break;

        case ActionResultCode::ExitState:
            ExitState();
            break;

        case ActionResultCode::Error:
            ReportError();
            break;
        }
    }

    void StateMachine::EnterState(const State* newState)
    {
        ExitState();
        mCurrentState = const_cast<State*>(newState);
        mCurrentState->Enter();
    }

    void StateMachine::ExitState()
    {
        if (mCurrentState != nullptr)
        {
            mCurrentState->Exit();
            delete mCurrentState;
            mCurrentState = nullptr;
        }
    }

    void StateMachine::EnterChildState(const State* newState)
    {
        if (mCurrentState == nullptr)
        {
            EnterState(newState);
        }
        else
        {
            mCurrentState->SetChild(newState);
        }
    }

    void StateMachine::ExitChildState()
    {
        if (mCurrentState)
        {
            mCurrentState->ExitChild();
        }
    }

    void StateMachine::ExitStateMachine()
    {
        mMasterExitFlag = true;
    }

    void StateMachine::ReportError()
    {
#if _DEBUG
        std::cout << "Error in State Machine [" << Name << "]" << std::endl;
#endif
    }
}