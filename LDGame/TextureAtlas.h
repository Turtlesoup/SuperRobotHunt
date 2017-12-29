#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include "Rect.h"

#include <vector>
#include <map>
#include <string>
#include <SFML\Graphics.hpp>

class TextureAtlas
{
	public:
		TextureAtlas();
		~TextureAtlas();
		void create(unsigned int width, unsigned int height, const std::vector<std::string> &resourceURLs);
		Rect<int>& getTextureRegion(std::string resourceURL);
		sf::Texture& texture();
		void saveToFile(const std::string& filename);
	private:
		sf::Texture _texture;
		sf::Image _textureImage;
		std::map<std::string, Rect<int>> _textureRegions;
};

#endif