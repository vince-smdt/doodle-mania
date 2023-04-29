#pragma once
#include <memory>
#include <stack>
#include <iostream>

#include "State.hpp"

typedef std::unique_ptr<State> StateRef;

class StateMachine
{
private:
    std::stack<StateRef> _states;
    StateRef _newState;

    bool _isRemoving;
    bool _isAdding;
    bool _isReplacing;
public:
    void AddState(StateRef newState, bool isReplacing = false);
    void RemoveState();
    void ProcessStateChanges();
    StateRef& GetActiveState();
};
