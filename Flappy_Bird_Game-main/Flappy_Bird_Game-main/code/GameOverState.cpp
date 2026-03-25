#include <SFML/Graphics.hpp>
#include <sstream>
#include "GameOverState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"
#include "GameState.hpp"

#include <iostream>
#include <fstream>

namespace FlappyBird
{
	// Constructor: saves game data and the score from the last game
	GameOverState::GameOverState(GameDataRef data, int score) : _data(data), _score(score)
	{

	}

	// This function runs once when Game Over screen appears
	void GameOverState::Init()
	{
		// --- Load High Score from file ---
		std::ifstream readFile("Resources/Highscore.txt");
		if (readFile.is_open())
		{
			while (!readFile.eof())  // Keep reading until the end of file
			{
				readFile >> _highScore;  // Read high score value
			}
		}
		readFile.close();

		// --- Update High Score if new score is higher ---
		std::ofstream writeFile("Resources/Highscore.txt");
		if (writeFile.is_open())
		{
			if (_score > _highScore)
			{
				_highScore = _score;  // Save new high score
			}
			writeFile << _highScore;  // Write to file
		}
		writeFile.close();

		// --- Load all required textures ---
		_data->assets.LoadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);
		_data->assets.LoadTexture("Game Over Title", GAME_OVER_TITLE_FILEPATH);
		_data->assets.LoadTexture("Game Over Body", GAME_OVER_BODY_FILEPATH);
		_data->assets.LoadTexture("Bronze Medal", BRONZE_MEDAL_FILEPATH);
		_data->assets.LoadTexture("Silver Medal", SILVER_MEDAL_FILEPATH);
		_data->assets.LoadTexture("Gold Medal", GOLD_MEDAL_FILEPATH);
		_data->assets.LoadTexture("Platinum Medal", PLATINUM_MEDAL_FILEPATH);

		// --- Set textures to sprites ---
		_background.setTexture(this->_data->assets.GetTexture("Game Over Background"));
		_gameOverTitle.setTexture(this->_data->assets.GetTexture("Game Over Title"));
		_gameOverBody.setTexture(this->_data->assets.GetTexture("Game Over Body"));
		_retryButton.setTexture(this->_data->assets.GetTexture("Play Button")); // Reuse play button as retry

		// --- Position Game Over UI on screen ---
		_gameOverBody.setPosition(
			(_data->window.getSize().x / 2.0f) - (_gameOverBody.getGlobalBounds().width / 2.0f),
			(_data->window.getSize().y / 2.0f) - (_gameOverBody.getGlobalBounds().height / 2.0f)
		);

		_gameOverTitle.setPosition(
			_data->window.getSize().x / 2.0f - _gameOverTitle.getGlobalBounds().width / 2.0f,
			_gameOverBody.getPosition().y - (_gameOverTitle.getGlobalBounds().height * 1.2)
		);

		_retryButton.setPosition(
			_data->window.getSize().x / 2.0f - _retryButton.getGlobalBounds().width / 2.0f,
			_gameOverBody.getPosition().y + _gameOverBody.getGlobalBounds().height +
			(_retryButton.getGlobalBounds().height * 0.2)
		);

		// --- Set and position score text ---
		_scoreText.setFont(_data->assets.GetFont("Flappy Font"));
		_scoreText.setString(std::to_string(_score));  // Convert number to string
		_scoreText.setCharacterSize(56);
		_scoreText.setFillColor(sf::Color::White);
		_scoreText.setOrigin(
			_scoreText.getGlobalBounds().width / 2.0f,
			_scoreText.getGlobalBounds().height / 2.0f
		);
		_scoreText.setPosition(
			_data->window.getSize().x / 10 * 7.25,
			_data->window.getSize().y / 2.15
		);

		// --- Set and position high score text ---
		_highScoreText.setFont(_data->assets.GetFont("Flappy Font"));
		_highScoreText.setString(std::to_string(_highScore));
		_highScoreText.setCharacterSize(56);
		_highScoreText.setFillColor(sf::Color::White);
		_highScoreText.setOrigin(
			_highScoreText.getGlobalBounds().width / 2.0f,
			_highScoreText.getGlobalBounds().height / 2.0f
		);
		_highScoreText.setPosition(
			_data->window.getSize().x / 10 * 7.25,
			_data->window.getSize().y / 1.78
		);

		// --- Select medal image based on score ---
		if (_score >= PLATINUM_MEDAL_SCORE)
		{
			_medal.setTexture(_data->assets.GetTexture("Platinum Medal"));
		}
		else if (_score >= GOLD_MEDAL_SCORE)
		{
			_medal.setTexture(_data->assets.GetTexture("Gold Medal"));
		}
		else if (_score >= SILVER_MEDAL_SCORE)
		{
			_medal.setTexture(_data->assets.GetTexture("Silver Medal"));
		}
		else
		{
			_medal.setTexture(_data->assets.GetTexture("Bronze Medal"));
		}

		_medal.setPosition(175, 465);  // Fixed position for medal
	}

	// Check for retry button click or window close
	void GameOverState::HandleInput()
	{
		sf::Event event;
		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();  // Close game
			}

			// If retry button clicked, restart the game
			if (_data->input.IsSpriteClicked(_retryButton, sf::Mouse::Left, _data->window))
			{
				_data->machine.AddState(StateRef(new GameState(_data)), true);
			}
		}
	}

	// No update logic needed for static Game Over screen
	void GameOverState::Update(float dt)
	{

	}

	// Draw Game Over screen with all UI elements
	void GameOverState::Draw(float dt)
	{
		_data->window.clear(sf::Color::Red);  // Clear screen with red

		_data->window.draw(this->_background);
		_data->window.draw(this->_gameOverTitle);
		_data->window.draw(this->_gameOverBody);
		_data->window.draw(this->_retryButton);
		_data->window.draw(_scoreText);
		_data->window.draw(_highScoreText);
		_data->window.draw(_medal);

		_data->window.display();  // Show everything on screen
	}
}
