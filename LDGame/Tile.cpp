#include "Tile.h"

Tile::Tile(const std::string& fileName, const std::string& textureName, Vector2<float> position, unsigned int textureRegionOffsetX, unsigned int textureRegionOffsetY, unsigned int tileWidth, unsigned int tileHeight) : SpriteDisplayObject(fileName, textureName, position)
{
	_spriteRect.left += textureRegionOffsetX;
	_spriteRect.top += textureRegionOffsetY;
	_spriteRect.width = tileWidth;
	_spriteRect.height = tileHeight;

	//update the width, height and origin
	_width = tileWidth;
	_height = tileHeight;
	//set tile origin to top left
	_origin.x = 0;
	_origin.y = 0;
}

Tile::~Tile()
{
}