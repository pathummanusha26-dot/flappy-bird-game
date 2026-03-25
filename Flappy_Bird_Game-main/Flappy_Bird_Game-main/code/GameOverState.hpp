#pragma once  // Make sure this header file is only included once

#include <SFML/Graphics.hpp>  // SFML graphics library (sprites, textures, text)
#include "State.hpp"          // Base class for game states
#include "Game.hpp"           // Shared game data: window, assets, input, etc.

namespace FlappyBird
{
	// This class is the Game Over screen (shown after the player loses)
	class GameOverState : public State
	{
	public:
		// Constructor: receives shared game data and player's final score
		GameOverState(GameDataRef data, int score);

		// Called when Game Over screen starts: loads images and sets up positions
		void Init();

		// Handles user input (e.g., retry button click)
		void HandleInput();

		// Update game logic (optional for this screen)
		void Update(float dt);

		// Draw everything (background, retry button, score text, etc.)
		void Draw(float dt);

	private:
		GameDataRef _data;  // Shared game data reference

		// Background image and UI elements
		sf::Texture _backgroundTexture;  // Texture for background
		sf::Sprite _background;          // Sprite to show background
		sf::Sprite _gameOverTitle;       // "Game Over" title image
		sf::Sprite _gameOverBody;        // UI box (scoreboard)
		sf::Sprite _retryButton;         // Retry button image
		sf::Sprite _medal;               // Medal image (bronze, silver, etc.)

		sf::Text _scoreText;       // Text showing current score
		sf::Text _highScoreText;   // Text showing high score

		int _score;       // Final score of current game
		int _highScore;   // Highest score saved from previous games
	};
}
