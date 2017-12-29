#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <map>
#include <SFML\Graphics.hpp>
#include "TextureAtlas.h"

class TextureManager
{
	public:
		TextureManager();
		~TextureManager();
		static TextureManager *Get();
		void loadTexture(const std::string &textureURL);
		void deleteTexture(const std::string &textureURL);
		sf::Texture &getTexture(std::string textureURL);
		void addTextureAtlas(std::string textureAtlasID, const TextureAtlas &textureAtlas);
		void deleteTextureAtlas(std::string textureAtlasID);
		TextureAtlas &getTextureAtlas(std::string textureAtlasID);
	private:
		static TextureManager *_instance;
		std::map<std::string, sf::Texture> _textureURLToTexture;
		std::map<std::string, TextureAtlas> _textureAtlasIDToTextureAtlas;
};

#endif