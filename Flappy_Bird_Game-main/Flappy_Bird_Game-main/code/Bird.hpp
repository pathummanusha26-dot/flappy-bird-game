#pragma once  // This ensures the file is only included once when compiling

#include <SFML/Graphics.hpp>  // Include SFML graphics (sprites, textures)
#include "Game.hpp"           // Include shared game data
#include "DEFINITIONS.hpp"    // Include game constants like gravity or speed
#include <vector>             // For using std::vector

namespace FlappyBird
{
	// This class controls the Bird (player's character)
	class Bird
	{
	public:
		// Constructor: creates the bird using shared game data
		Bird(GameDataRef data);

		// Draws the bird on the game window
		void Draw();

		// Animates the bird's flapping
		void Animate(float dt);

		// Updates bird position and rotation (flying or falling)
		void Update(float dt);

		// Makes the bird fly up when tapped
		void Tap();

		// Gives read-only access to the bird's sprite (for collisions)
		const sf::Sprite& GetSprite() const;

	private:
		GameDataRef _data;                    // Pointer to shared game data (window, assets, etc.)
		sf::Sprite _birdSprite;              // Bird sprite (image object)
		std::vector<sf::Texture> _animationFrames;  // All frames for animation

		unsigned int _animationIterator;     // Which frame the animation is showing

		sf::Clock _clock;                    // Clock for controlling animation timing

		sf::Clock _movementClock;            // Clock for controlling how long the bird flies

		int _birdState;                      // State of the bird: still, flying, or falling

		float _rotate;                       // Current rotation angle of the bird
	};
}
