#pragma once
#include "StateMachine.h"

void StateMachine::AddState(StateRef newState, bool isReplacing)
{
    _isAdding = true;
    _isReplacing = isReplacing;
    _newState = move(newState);
}

void StateMachine::ProcessStateChanges()
{
    if (_isRemoving && !_states.empty())
    {
        _states.pop();
        if (!_states.empty())
            _states.top()->Resume();
    }
    _isRemoving = false;

    if (_isAdding)
    {
        if (!_states.empty())
        {
            if (_isReplacing)
                _states.pop();
            else
                _states.top()->Pause();
        }

        _states.push(move(_newState));
        _states.top()->Init();
        _isAdding = false;
    }
}

void StateMachine::RemoveState()
{
    _isRemoving = true;
}

StateRef& StateMachine::GetActiveState()
{
    return _states.top();
}
