#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Game.hpp"


namespace FlappyBird
{
	class Hud
	{
	public:
		Hud(GameDataRef data);
		void Draw();
		void UpdateScore(int score);
		
	private:
		GameDataRef _data;

		sf::Text _scoreText;

	};
}