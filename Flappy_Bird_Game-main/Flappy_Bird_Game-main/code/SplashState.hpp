#pragma once  // Ensures this header file is only included once

#include <SFML/Graphics.hpp>  // For SFML graphics (sprites, textures)
#include "State.hpp"          // Base class for all game states
#include "Game.hpp"           // Shared game data (window, assets, etc.)

namespace FlappyBird
{
	// SplashState shows the splash screen (the screen shown at the start)
	class SplashState : public State  // Inherits from the base State class
	{
	public:
		// Constructor receives shared game data
		SplashState(GameDataRef data);

		// Runs once when the splash screen starts (load images, setup)
		void Init();

		// Handles user input (usually none for splash)
		void HandleInput();

		// Updates logic like splash screen duration
		void Update(float dt);

		// Draws the splash screen on the window
		void Draw(float dt);

	private:
		GameDataRef _data;  // Shared pointer to game data (assets, window, etc.)

		sf::Clock _clock;   // Used to wait a few seconds before switching state

		sf::Texture _backgroundTexture;  // Image file for splash background
		sf::Sprite _background;          // Sprite that shows the background
	};
}
