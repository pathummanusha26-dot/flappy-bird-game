#include "Bird.hpp"

namespace FlappyBird
{
	// Constructor: called when the bird object is created
	Bird::Bird(GameDataRef data) : _data(data)
	{
		_animationIterator = 0; // Start animation at frame 0

		// Load all bird animation textures into a list
		_animationFrames.push_back(_data->assets.GetTexture("Bird Frame 1"));
		_animationFrames.push_back(_data->assets.GetTexture("Bird Frame 2"));
		_animationFrames.push_back(_data->assets.GetTexture("Bird Frame 3"));
		_animationFrames.push_back(_data->assets.GetTexture("Bird Frame 4"));

		// Set the bird's texture to the first animation frame
		_birdSprite.setTexture(_animationFrames.at(_animationIterator));

		// Position the bird in the center-left of the screen
		_birdSprite.setPosition(
			(_data->window.getSize().x / 4) - (_birdSprite.getGlobalBounds().width / 2),
			(_data->window.getSize().y / 2) - (_birdSprite.getGlobalBounds().height / 2)
		);

		_birdState = BIRD_STILL; // Bird starts still (not flying or falling)

		// Set the rotation center of the bird sprite to its center
		sf::Vector2f origin = sf::Vector2f(
			_birdSprite.getGlobalBounds().width / 2,
			_birdSprite.getGlobalBounds().height / 2
		);
		_birdSprite.setOrigin(origin);

		_rotate = 0; // No rotation at start
	}

	// Draw the bird on the screen
	void Bird::Draw()
	{
		_data->window.draw(_birdSprite);
	}

	// Animate the bird by changing the texture frame
	void Bird::Animate(float dt)
	{
		// If enough time has passed, move to the next frame
		if (_clock.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / _animationFrames.size())
		{
			if (_animationIterator < _animationFrames.size() - 1)
			{
				_animationIterator++; // Go to next frame
			}
			else
			{
				_animationIterator = 0; // Restart from frame 0
			}

			// Set the bird's texture to the new frame
			_birdSprite.setTexture(_animationFrames.at(_animationIterator));

			_clock.restart(); // Restart the animation clock
		}
	}

	// Update the bird's movement and rotation
	void Bird::Update(float dt)
	{
		// If bird is falling (going down)
		if (_birdState == BIRD_FALLING)
		{
			_birdSprite.move(0, GRAVITY * dt); // Move down by gravity

			_rotate += ROTATION_SPEED * dt; // Rotate clockwise

			if (_rotate > 25.0f)
			{
				_rotate = 25.f; // Limit maximum rotation
			}

			_birdSprite.setRotation(_rotate); // Apply rotation
		}
		// If bird is flying (going up)
		else if (_birdState == BIRD_FLYING)
		{
			_birdSprite.move(0, -FLYING_SPEED * dt); // Move up

			_rotate -= ROTATION_SPEED * dt; // Rotate counter-clockwise

			if (_rotate < -25.0f)
			{
				_rotate = -25.f; // Limit max upward rotation
			}

			_birdSprite.setRotation(_rotate); // Apply rotation
		}

		// After flying for some time, bird starts falling
		if (_movementClock.getElapsedTime().asSeconds() > FLYING_DURATION)
		{
			_movementClock.restart();   // Restart movement timer
			_birdState = BIRD_FALLING;  // Change to falling state
		}
	}

	// When the player taps, make the bird fly up
	void Bird::Tap()
	{
		_movementClock.restart(); // Restart flying time
		_birdState = BIRD_FLYING; // Set bird to flying
	}

	// Return a reference to the bird's sprite (used for collision)
	const sf::Sprite& Bird::GetSprite() const
	{
		return _birdSprite;
	}
}
