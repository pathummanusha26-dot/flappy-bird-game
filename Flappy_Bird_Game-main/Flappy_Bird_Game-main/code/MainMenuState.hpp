#pragma once  // Make sure this header file is only included once

#include <SFML/Graphics.hpp>  // For graphics (sprites, textures)
#include "State.hpp"          // Base class for all game states
#include "Game.hpp"           // Shared game data (assets, window, input)

namespace FlappyBird
{
	// This class is the Main Menu screen of the game
	class MainMenuState : public State  // Inherits from base State class
	{
	public:
		// Constructor that receives shared game data
		MainMenuState(GameDataRef data);

		// Called once when the state starts (load images, setup screen)
		void Init();

		// Handles user input like mouse click or closing window
		void HandleInput();

		// Updates game logic (empty for menu)
		void Update(float dt);

		// Draws everything on the screen (background, title, button)
		void Draw(float dt);

	private:
		GameDataRef _data;  // Shared game data: window, assets, state machine

		sf::Sprite _title;       // Game title image
		sf::Sprite _background;  // Background image
		sf::Sprite _playButton;  // Play button image
	};
}
