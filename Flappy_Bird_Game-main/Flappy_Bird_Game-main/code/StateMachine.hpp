#pragma once  // Ensure this header file is included only once

#include <memory>  // For std::unique_ptr
#include <stack>   // For using stack to store states

#include "State.hpp"  // Include the base State class

namespace FlappyBird
{
	// A reference to a unique state object (used for switching between states)
	typedef std::unique_ptr<State> StateRef;

	class StateMachine
	{
	public:
		StateMachine() {}  // Constructor
		~StateMachine() {} // Destructor

		// Add a new state to the stack
		void AddState(StateRef newState, bool isReplacing = true);

		// Remove the top state
		void RemoveState();

		// Handle actual changes to the state stack (called in game loop)
		void ProcessStateChanges();

		// Get the active (top) state
		StateRef& GetActiveState();

	private:
		std::stack<StateRef> _states;  // Stack to hold all states

		StateRef _newState;            // The state to be added

		bool _isRemoving = false;      // Flag: should remove a state?
		bool _isAdding = false;        // Flag: should add a state?
		bool _isReplacing = false;     // Flag: should replace the current state?
	};
}
