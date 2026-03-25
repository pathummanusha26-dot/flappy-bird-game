#pragma once

#include <map>                // For using map (key-value pairs)
#include <SFML/Graphics.hpp> // For SFML texture and font

namespace FlappyBird
{
	class AssetManager
	{
	public:
		AssetManager() {}  // Constructor
		~AssetManager() {} // Destructor

		// Loads a texture and stores it with a name
		void LoadTexture(std::string name, std::string fileName);

		// Returns a reference to a loaded texture
		sf::Texture& GetTexture(std::string name);

		// Loads a font and stores it with a name
		void LoadFont(std::string name, std::string fileName);

		// Returns a reference to a loaded font
		sf::Font& GetFont(std::string name);

	private:
		// Stores all loaded textures
		std::map<std::string, sf::Texture> _textures;

		// Stores all loaded fonts
		std::map<std::string, sf::Font> _fonts;
	};
}
