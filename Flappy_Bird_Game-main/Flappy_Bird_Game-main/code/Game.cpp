#include "Game.hpp"
#include "SplashState.hpp"  // Start game with splash screen

#include <stdlib.h>  // For srand and rand
#include <time.h>    // For time()

namespace FlappyBird
{
	// Constructor: sets up game window and first screen (Splash)
	Game::Game(int width, int height, std::string title)
	{
		srand(time(NULL));  // Initialize random number generator with current time

		// Create a new SFML window with given size and title
		_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);

		// Push the SplashState (first screen) onto the state machine
		_data->machine.AddState(StateRef(new SplashState(this->_data)));

		this->Run();  // Start the game loop
	}

	// Main game loop
	void Game::Run()
	{
		float newTime, frameTime, interpolation;

		float currentTime = this->_clock.getElapsedTime().asSeconds();  // Get current time in seconds
		float accumulator = 0.0f;  // Time buffer between frames

		// Loop while the game window is open
		while (this->_data->window.isOpen())
		{
			this->_data->machine.ProcessStateChanges();  // Handle any pending state changes

			newTime = this->_clock.getElapsedTime().asSeconds();  // Time now
			frameTime = newTime - currentTime;  // How much time has passed since last frame

			if (frameTime > 0.25f)
			{
				frameTime = 0.25f;  // Limit maximum frame time to avoid big jumps
			}

			currentTime = newTime;
			accumulator += frameTime;  // Add time to the buffer

			// Update logic while buffer has enough time for 1 frame
			while (accumulator >= dt)
			{
				this->_data->machine.GetActiveState()->HandleInput();  // Check player input
				this->_data->machine.GetActiveState()->Update(dt);     // Update game logic

				accumulator -= dt;  // Remove one frame's worth of time from the buffer
			}

			interpolation = accumulator / dt;  // Used for smooth drawing
			this->_data->machine.GetActiveState()->Draw(interpolation);  // Draw game objects
		}
	}
}
