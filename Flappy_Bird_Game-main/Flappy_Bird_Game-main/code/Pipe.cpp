#include "Pipe.hpp"
#include <iostream>

namespace FlappyBird
{
	Pipe::Pipe(GameDataRef data) : _data(data)
	{
		_landHeight = _data->assets.GetTexture("Land").getSize().y;

	}

	void Pipe::SpawnPipes()
	{

	}
	void Pipe::SpawnTopPipe()
	{
		sf::Sprite pipeSprite(_data->assets.GetTexture("Pipe Down"));

		pipeSprite.setPosition(_data->window.getSize().x, -_pipeSpawnYOffset);

		pipeSprites.push_back(pipeSprite);

	}
	void Pipe::SpawnBottomPipe()
	{
		sf::Sprite pipeSprite(_data->assets.GetTexture("Pipe Up"));

		pipeSprite.setPosition(_data->window.getSize().x, 
			_data->window.getSize( ).y - pipeSprite.
			getGlobalBounds().height - _pipeSpawnYOffset);

		pipeSprites.push_back(pipeSprite);

	}
	void Pipe::SpawnInvisiblePipe()
	{
		sf::Sprite pipeSprite(_data->assets.GetTexture("Pipe Up"));

		pipeSprite.setPosition(_data->window.getSize().x,
			_data->window.getSize().y - pipeSprite.getGlobalBounds().height);

		pipeSprite.setColor(sf::Color(0, 0, 0, 0)); // Make it invisible

		pipeSprites.push_back(pipeSprite);

	}

	void Pipe::SpawnScoringPipe()
	{
		sf::Sprite sprite(_data->assets.GetTexture("Scoring Pipe"));

		sprite.setPosition(_data->window.getSize().x, 0);

		scoringPipes.push_back(sprite);

	}

	void Pipe::MovePipes(float dt)
	{
		for (unsigned short int i = 0; i < pipeSprites.size(); i++) {

			if (pipeSprites.at(i).getPosition().x < 0 )
			{
				pipeSprites.erase(pipeSprites.begin() + i);
				i--; // Adjust index after removal
				
			} 
			else {

				float movement = PIPE_MOVEMENT_SPEED * dt;

				pipeSprites.at(i).move(-movement, 0);

			}

		}
		std::cout << pipeSprites.size() << std::endl;

		for (unsigned short int i = 0; i < scoringPipes.size(); i++) {

			if (scoringPipes.at(i).getPosition().x < 0)
			{
				scoringPipes.erase(scoringPipes.begin() + i);
				i--; // Adjust index after removal

			}
			else {

				float movement = PIPE_MOVEMENT_SPEED * dt;

				scoringPipes.at(i).move(-movement, 0);

			}

		}



	}

	void Pipe::DrawPipes()
	{
		for (unsigned short int i = 0; i < pipeSprites.size( ); i++){

			_data->window.draw(pipeSprites.at(i));

		}
		
	}

	void Pipe::RamdomizePipeOffset()
	{
		_pipeSpawnYOffset = rand() % (_landHeight + 1); // Random offset within land height
	}


	const std::vector<sf::Sprite>&Pipe:: GetSprites() const {
		return pipeSprites;
	}


	std::vector<sf::Sprite>& Pipe::GetScoringSprites() {
		return scoringPipes;
	}
}