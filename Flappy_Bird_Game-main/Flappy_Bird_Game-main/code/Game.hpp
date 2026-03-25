#pragma once  // Makes sure this file is only included once during compilation

#include <memory>              // For using shared_ptr
#include <string>              // To use std::string
#include <SFML/Graphics.hpp>   // SFML window and graphics
#include "StateMachine.hpp"    // To manage game states
#include "AssetManager.hpp"    // For loading textures and fonts
#include "InputManager.hpp"    // For keyboard/mouse input

namespace FlappyBird
{
	// This struct holds all the shared game data (state, window, assets, input)
	struct GameData
	{
		StateMachine machine;       // Controls the game states (menu, play, game over)
		sf::RenderWindow window;    // SFML window to display the game
		AssetManager assets;        // Loads and stores textures and fonts
		InputManager input;         // Manages user input (keyboard, mouse)
	};

	// Create a shared pointer to GameData (easier to pass around)
	typedef std::shared_ptr<GameData> GameDataRef;

	// The main Game class that starts and runs the game
	class Game
	{
	public:
		// Constructor: initializes the game window and first state
		Game(int width, int height, std::string title);

	private:
		const float dt = 1.0f / 60.0f;  // Fixed time per frame (60 FPS)
		sf::Clock _clock;              // SFML clock to track time

		GameDataRef _data = std::make_shared<GameData>();  // Shared game data

		void Run();  // The main game loop (update/draw repeatedly)
	};
}
