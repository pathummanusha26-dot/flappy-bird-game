#include "StateMachine.hpp"
#include <stdexcept>

namespace FlappyBird
{
	// Add a new state to the state machine
	void StateMachine::AddState(StateRef newState, bool isReplacing)
	{
		this->_isAdding = true;             // Mark that we want to add a new state
		this->_isReplacing = isReplacing;   // Save whether we want to replace the current state

		this->_newState = std::move(newState);  // Save the new state (move to avoid copying)

	}

	// Mark the current state to be removed
	void StateMachine::RemoveState()
	{
		this->_isRemoving = true;// Mark that we want to remove a state
	}

	// This function processes the adding/removing of states
	void StateMachine::ProcessStateChanges()
	{
		
		// If removing a state and stack is not empty
		if (this->_isRemoving && !_states.empty())
		{
			_states.pop(); // Remove the current (top) state
		}
		this->_isRemoving = false;// Reset the remove flag


		// ✅ Safely add new state if requested
		if (this->_isAdding)
		{
			if (!_states.empty())
			{
				if (_isReplacing)
				{
					_states.pop(); // Replace: remove current
				}
				else
				{
					_states.top()->Pause(); // Stack: pause current
				}
			}

			_states.push(std::move(_newState));
			_states.top()->Init();
			_isAdding = false;
		}
	}

	// Return the active (top) state
	StateRef& StateMachine::GetActiveState()
	{
		if (_states.empty())
		{
			throw std::runtime_error("StateMachine Error: No active state!");
		}

		return _states.top(); // Return the current top state from the stack
	}
}
