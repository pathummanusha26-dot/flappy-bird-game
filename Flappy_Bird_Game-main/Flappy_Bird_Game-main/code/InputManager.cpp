#include "InputManager.hpp"

namespace FlappyBird
{
	// Check if the given sprite was clicked with the specified mouse button inside the window
	bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window)
	{
		// Check if the specified mouse button is currently pressed
		if (sf::Mouse::isButtonPressed(button))
		{
			// Create a rectangle representing the sprite's area on screen
			sf::IntRect tempRect(
				object.getPosition().x,               // top-left x position of sprite
				object.getPosition().y,               // top-left y position of sprite
				object.getGlobalBounds().width,      // width of sprite
				object.getGlobalBounds().height      // height of sprite
			);

			// Check if the mouse position (relative to the window) is inside the sprite's rectangle
			if (tempRect.contains(sf::Mouse::getPosition(window)))
			{
				// Mouse is clicked on the sprite
				return true;
			}
		}
		// Mouse button not pressed or click outside sprite
		return false;
	}

	// Get the current mouse position relative to the given window
	sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window)
	{
		return sf::Mouse::getPosition(window);
	}
}
