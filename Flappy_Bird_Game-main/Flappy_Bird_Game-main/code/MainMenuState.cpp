#include <SFML/Graphics.hpp>
#include <sstream>
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace FlappyBird
{
	// Constructor: saves the shared game data reference
	MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{

	}

	// This function is called when the main menu state starts
	void MainMenuState::Init()
	{
		// Load background, title, and play button textures into memory
		_data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
		_data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
		_data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);

		// Set the textures to the matching sprites
		_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
		_title.setTexture(this->_data->assets.GetTexture("Game Title"));
		_playButton.setTexture(this->_data->assets.GetTexture("Play Button"));

		// Position background at top-left corner
		_background.setPosition(0, 0);

		// Position the title image at the top center
		_title.setPosition(
			(SCREEN_WIDTH / 2.0f) - (_title.getGlobalBounds().width / 2.0f),
			_title.getGlobalBounds().height / 4.0f
		);

		// Position the play button at the center of the screen
		_playButton.setPosition(
			(SCREEN_WIDTH / 2.0f) - (_playButton.getGlobalBounds().width / 2.0f),
			(SCREEN_HEIGHT / 2.0f) - (_playButton.getGlobalBounds().height / 2.0f)
		);
	}

	// Handles user input (mouse click or window close)
	void MainMenuState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			// Close the game window if the user clicks the close button
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			// If the play button is clicked with left mouse button
			if (_data->input.IsSpriteClicked(_playButton, sf::Mouse::Left, this->_data->window))
			{
				// Change the game state to GameState (start the game)
				_data->machine.AddState(StateRef(new GameState(_data)), true);
			}
		}
	}

	// No game logic to update in the main menu, so this is empty
	void MainMenuState::Update(float dt)
	{

	}

	// Draw everything on the screen
	void MainMenuState::Draw(float dt)
	{
		_data->window.clear();               // Clear the screen

		_data->window.draw(_background);     // Draw background image
		_data->window.draw(_title);          // Draw the game title
		_data->window.draw(_playButton);     // Draw the play button

		_data->window.display();             // Show everything on the screen
	}
}
