#include <SFML/Graphics.hpp>
#include <sstream>
#include "SplashState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace FlappyBird
{
    // Constructor: store the reference to shared game data
    SplashState::SplashState(GameDataRef data) : _data(data)
    {
        // Nothing to do here yet
    }

    // Initialize function: load splash screen background texture
    void SplashState::Init()
    {
        // Load the splash screen image texture into asset manager
        this->_data->assets.LoadTexture("Splash State Background", SPLASH_STATE_FILEPATH);

        // Set the sprite's texture to the loaded splash screen background
        _background.setTexture(this->_data->assets.GetTexture("Splash State Background"));
    }

    // Handle input events like window close
    void SplashState::HandleInput()
    {
        sf::Event event;

        // Process all pending window events
        while (this->_data->window.pollEvent(event))
        {
            // If the user clicks the close button on the window
            if (sf::Event::Closed == event.type)
            {
                // Close the window and end the game
                this->_data->window.close();
            }
        }
    }

    // Update function called every frame with delta time dt (time since last frame)
    void SplashState::Update(float dt)
    {
        // Check if splash screen display time has passed
        if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
        {
            // Move to Main Menu State, replacing SplashState
            _data->machine.AddState(StateRef(new MainMenuState(_data)), true);
        }
    }

    // Draw function renders splash screen every frame
    void SplashState::Draw(float dt)
    {
        // Clear the window with red color (background)
        this->_data->window.clear(sf::Color::Red);

        // Draw the splash screen background sprite
        this->_data->window.draw(this->_background);

        // Display everything drawn on the window
        this->_data->window.display();
    }
}
