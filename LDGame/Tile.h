#ifndef TILE_H
#define TILE_H

#include "SpriteDisplayObject.h"

class Tile : public SpriteDisplayObject
{
	public:
		Tile(const std::string& fileName, const std::string& textureName, Vector2<float> position, unsigned int textureRegionOffsetX, unsigned int textureRegionOffsetY, unsigned int tileWidth, unsigned int tileHeight);
		virtual ~Tile();
};

#endif