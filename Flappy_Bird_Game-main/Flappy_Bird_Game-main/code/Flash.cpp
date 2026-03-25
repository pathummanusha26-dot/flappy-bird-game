#include "Flash.hpp"

namespace FlappyBird
{
	Flash::Flash(GameDataRef data) : _data(data)
	{
		_shape = sf::RectangleShape(sf::Vector2f(data->window.getSize()));
		_shape.setFillColor(sf::Color(255, 255, 255, 0)); // Start fully transparent

		_flashOn = true; // Start with flash on
	}

	void Flash::Show(float dt)
	{
		if (_flashOn)
		{
			int alpha = (int)_shape.getFillColor().a + (FLASH_SPEED * dt);
			if (alpha >= 255)
			{
				alpha = 255.0f;
				_flashOn = false; // Stop flashing 
			}
			_shape.setFillColor(sf::Color(255, 255, 255, alpha)); 

		}
		else
		{

			int alpha = (int)_shape.getFillColor().a - (FLASH_SPEED * dt);

			if (alpha <= 0.0f)
			{
				alpha = 0.0f;
				_flashOn = false; // Stop flashing 
			}
			_shape.setFillColor(sf::Color(255, 255, 255, alpha));

			}

		}

	void Flash::Draw()
	{
		_data->window.draw(_shape);
	}
	}
	
