#pragma once

#include <utility>

namespace xelous
{
    enum class ActionResultCode
    {
        Nothing,
        NoStateChange = Nothing,
        NewState,
        NewChildState,
        ExitChildState,
        ExitStateMachine,
        ExitState,
        Error
    };

    class State;
    using ActionResult = std::pair<ActionResultCode, State*>;
}