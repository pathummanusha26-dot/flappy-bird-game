#pragma once  // Make sure this file is only included once during compile time

#include <SFML/Graphics.hpp>  // For drawing graphics
#include <SFML/Audio.hpp>     // For playing sound
#include "State.hpp"          // Base class for game states
#include "Game.hpp"           // Shared game data
#include "Pipe.hpp"           // Pipe object
#include "Land.hpp"           // Land object
#include "Bird.hpp"           // Bird (player character)
#include "Collision.hpp"      // For detecting collisions
#include "Flash.hpp"          // Flash screen effect
#include "Hud.hpp"            // Score display

namespace FlappyBird
{
	// This class is the main game state (the actual play screen)
	class GameState : public State
	{
	public:
		GameState(GameDataRef data); // Constructor

		void Init();             // Set up game state (load images, sounds)
		void HandleInput();      // Handle mouse clicks and window close
		void Update(float dt);   // Game logic (movement, collision, scoring)
		void Draw(float dt);     // Draw everything on screen

	private:
		GameDataRef _data;       // Shared data (window, assets, etc.)

		sf::Texture _backgroundTexture; // Background image
		sf::Sprite _background;         // Background sprite

		sf::SoundBuffer _hitSoundBuffer;   // Buffer to hold hit sound
		sf::SoundBuffer _pointSoundBuffer; // Buffer to hold point sound
		sf::SoundBuffer _wingSoundBuffer;  // Buffer to hold wing sound

		sf::Sound _hitSound;    // Sound played when bird hits
		sf::Sound _pointSound;  // Sound played when scoring
		sf::Sound _wingSound;   // Sound played when bird flaps

		Pipe* pipe;             // Pipe object
		Land* land;             // Land object
		Bird* bird;             // Bird object
		Collision collision;    // Collision checker
		Flash* flash;           // White flash effect when bird hits
		Hud* hud;               // Heads-up display (score)

		sf::Clock clock;        // Tracks time for spawning and transitions

		int _gameState;         // Current state: Ready, Playing, or Game Over
		int _score;             // Current score
	};
}
