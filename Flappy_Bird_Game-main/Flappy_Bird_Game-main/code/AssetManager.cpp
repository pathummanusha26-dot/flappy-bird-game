#include "AssetManager.hpp"

namespace FlappyBird
{
	// Load a texture from a file and store it in a map using the given name
	void AssetManager::LoadTexture(std::string name, std::string fileName)
	{
		sf::Texture tex;

		// If the file loads successfully
		if (tex.loadFromFile(fileName)) {
			// Save the texture in the map with the given name
			this->_textures[name] = tex;
		}
	}

	// Return a reference to a texture by name
	sf::Texture& AssetManager::GetTexture(std::string name)
	{
		return this->_textures.at(name);
	}

	// Load a font from a file and store it in a map using the given name
	void AssetManager::LoadFont(std::string name, std::string fileName)
	{
		sf::Font font;

		// If the file loads successfully
		if (font.loadFromFile(fileName)) {
			// Save the font in the map with the given name
			this->_fonts[name] = font;
		}
	}

	// Return a reference to a font by name
	sf::Font& AssetManager::GetFont(std::string name)
	{
		return this->_fonts.at(name);
	}
}
