#pragma once

#include <SFML/Graphics.hpp>

namespace FlappyBird
{
	// Class to manage user input like mouse clicks and mouse position
	class InputManager
	{
	public:
		// Constructor (empty)
		InputManager() {}

		// Destructor (empty)
		~InputManager() {}

		// Check if a given sprite was clicked by the user with a specific mouse button
		bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);

		// Get the current mouse position relative to the window
		sf::Vector2i GetMousePosition(sf::RenderWindow& window);
	};
}
