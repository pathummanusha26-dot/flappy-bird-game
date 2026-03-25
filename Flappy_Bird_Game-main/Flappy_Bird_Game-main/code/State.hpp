#pragma once  // Make sure this header file is only included once during compilation

namespace FlappyBird
{
	// This is an abstract base class for all game states (like menu, game, game over)
	class State
	{
	public:
		// This function will be called when the state starts (for setup)
		virtual void Init() = 0;

		// Handles user input like keyboard or mouse
		virtual void HandleInput() = 0;

		// Updates the game logic (movement, score, etc.)
		virtual void Update(float dt) = 0;

		// Draws everything on the screen
		virtual void Draw(float dt) = 0;

		// Optional: what happens when the game is paused (default = do nothing)
		virtual void Pause() {};

		// Optional: what happens when the game resumes from pause (default = do nothing)
		virtual void Resume() {};
	};
}
