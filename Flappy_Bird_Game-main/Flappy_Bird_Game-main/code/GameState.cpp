#include <SFML/Graphics.hpp>
#include <sstream>
#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"
#include "GameOverState.hpp"
#include <iostream>

namespace FlappyBird
{
	GameState::GameState(GameDataRef data) : _data(data) {}

	void GameState::Init()
	{
		// Load sound files
		if (!_hitSoundBuffer.loadFromFile(HIT_SOUND_FILEPATH)) std::cout << "Error loading hit sound!\n";
		if (!_pointSoundBuffer.loadFromFile(POINT_SOUND_FILEPATH)) std::cout << "Error loading point sound!\n";
		if (!_wingSoundBuffer.loadFromFile(WING_SOUND_FILEPATH)) std::cout << "Error loading wing sound!\n";

		_hitSound.setBuffer(_hitSoundBuffer);
		_pointSound.setBuffer(_pointSoundBuffer);
		_wingSound.setBuffer(_wingSoundBuffer);

		// Load all textures for background, pipes, bird, land
		_data->assets.LoadTexture("Game State Background", GAME_BACKGROUND_FILEPATH);
		_data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
		_data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
		_data->assets.LoadTexture("Land", LAND_FILEPATH);
		_data->assets.LoadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
		_data->assets.LoadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
		_data->assets.LoadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
		_data->assets.LoadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);
		_data->assets.LoadTexture("Scoring Pipe", SCORING_PIPE_FILEPATH);
		_data->assets.LoadFont("Flappy Font", FONT_FILEPATH);

		// Create objects for each game part
		pipe = new Pipe(_data);
		land = new Land(_data);
		bird = new Bird(_data);
		flash = new Flash(_data);
		hud = new Hud(_data);

		_background.setTexture(this->_data->assets.GetTexture("Game State Background"));

		_score = 0;
		hud->UpdateScore(_score);  // Show score as 0 at start
		_gameState = GameStates::Bird_Ready;  // Bird is waiting
	}

	void GameState::HandleInput()
	{
		sf::Event event;
		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
				this->_data->window.close();

			// If background is clicked and bird is not dead
			if (_data->input.IsSpriteClicked(_background, sf::Mouse::Left, this->_data->window))
			{
				if (_gameState != GameStates::Bird_Over)
				{
					_gameState = GameStates::Bird_Playing;
					bird->Tap();         // Bird goes up
					_wingSound.play();   // Play wing sound
				}
			}
		}
	}

	void GameState::Update(float dt)
	{
		if (_gameState != GameStates::Bird_Over)
		{
			bird->Animate(dt);  // Bird flapping
			land->MoveLand(dt); // Land moves left
		}

		// If bird is flying
		if (_gameState == GameStates::Bird_Playing)
		{
			pipe->MovePipes(dt);  // Pipes move left

			// Time to spawn a new pipe
			if (clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
			{
				pipe->RamdomizePipeOffset();
				pipe->SpawnInvisiblePipe();
				pipe->SpawnBottomPipe();
				pipe->SpawnTopPipe();
				pipe->SpawnScoringPipe();
				clock.restart();
			}

			bird->Update(dt);  // Apply gravity and rotation

			// Check collision with land
			for (auto landSprite : land->GetLandSprites())
			{
				if (collision.CheckSpriteCollision(bird->GetSprite(), 0.7f, landSprite, 1.0f))
				{
					_gameState = GameStates::Bird_Over;
					std::cout << "Game Over! You hit the land!" << std::endl;
					clock.restart();
					_hitSound.play();
				}
			}

			// Check collision with pipes
			for (auto pipeSprite : pipe->GetSprites())
			{
				if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, pipeSprite, 1.0f))
				{
					_gameState = GameStates::Bird_Over;
					std::cout << "Game Over! You hit the pipe!" << std::endl;
					clock.restart();
					_hitSound.play();
				}
			}

			// Check if bird scores
			auto& scoringSprites = pipe->GetScoringSprites();
			for (int i = 0; i < scoringSprites.size(); i++)
			{
				if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, scoringSprites[i], 1.0f))
				{
					_score++;
					hud->UpdateScore(_score);
					std::cout << "Score: " << _score << std::endl;
					scoringSprites.erase(scoringSprites.begin() + i);
					_pointSound.play();
				}
			}
		}

		// If game over, show flash and move to GameOver screen
		if (_gameState == GameStates::Bird_Over)
		{
			flash->Show(dt);

			if (clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS)
			{
				_data->machine.AddState(StateRef(new GameOverState(_data, _score)), true);
			}
		}
	}

	void GameState::Draw(float dt)
	{
		_data->window.clear();               // Clear screen
		_data->window.draw(_background);     // Draw background
		pipe->DrawPipes();                   // Draw pipes
		land->DrawLand();                    // Draw ground
		bird->Draw();                        // Draw the bird
		flash->Draw();                       // Draw white flash if any
		hud->Draw();                         // Draw the score

		_data->window.display();             // Show everything on screen
	}
}
