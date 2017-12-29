#include "TileMap.h"
#include "Tile.h"
#include "TextureAtlas.h"
#include "TextureManager.h"
#include "Application.h"
#include "StringHelper.h"

TileMap::TileMap(const Vector2<float>& position) : DisplayObject(position)
{
}

TileMap::~TileMap()
{
}

void TileMap::create(unsigned int width, unsigned int height, unsigned int tileWidth, unsigned int tileHeight, const std::string& tileSheetFileURL, const std::string& textureName, const std::string& delimitedFilename, char delimiter)
{
	std::vector<std::string> tileValueStrings = StringHelper::split(StringHelper::wideStringToString(StringHelper::loadFromFile(delimitedFilename)), delimiter);
	std::vector<unsigned int> tileValues = StringHelper::convertVectorOfStringsToVectorOfUnsignedInts(tileValueStrings);

	create(width, height, tileWidth, tileHeight, tileSheetFileURL, textureName, tileValues);
}

void TileMap::create(unsigned int width, unsigned int height, unsigned int tileWidth, unsigned int tileHeight, const std::string& tileSheetFileURL, const std::string& textureName, const std::vector<unsigned int>& tileValues)
{
	//create the tilemap
	float zoom = Application::zoom();

	_tileValues = tileValues;
	_tileWidth = tileWidth;
	_tileHeight = tileHeight;
	_tileSheetFileURL = tileSheetFileURL;
	_textureName = textureName;
	_numTilesAcross = ceil((double)width/((double)tileWidth*zoom));
	_numTilesDown = ceil((double)height/((double)tileHeight*zoom));
	_numTiles = 0;

	TextureAtlas& textureAtlas = TextureManager::Get()->getTextureAtlas(textureName);
	Rect<int> tileSheetRegion = textureAtlas.getTextureRegion(tileSheetFileURL);

	unsigned int tileSheetRegionWidth = tileSheetRegion.width;
	unsigned int tileSheetRegionHeight = tileSheetRegion.height;

	_numTextureTilesAcross = (double)tileSheetRegionWidth / (double)_tileWidth;
	_numTextureTilesDown = (double)tileSheetRegionHeight / (double)_tileHeight;

	Vector2<float> tilePosition;
	unsigned int tileIndex;

	for(unsigned int tileX = 0; tileX < _numTilesAcross; ++ tileX)
	{
		for(unsigned int tileY = 0; tileY < _numTilesDown; ++ tileY)
		{
			//get the x and y position of the tile
			tilePosition.x = (tileX * _tileWidth);
			tilePosition.y = (tileY * _tileHeight);

			//get the tile index from its tileX and tile Y position
			tileIndex = tileX + (tileY * _numTilesAcross);

			//create the tile
			createTile(tileIndex, tilePosition);
		}
	}
}

void TileMap::createTile(unsigned int tileIndex, Vector2<float> tilePosition)
{
	//if the tile index is greater than the number of tile values, dont add the time
	if(tileIndex < _tileValues.size())
	{
		//get the texture region index for the tile value
		//a texture region index of 0 will mean that a tile is not made and therefore
		//will not be rendered. If the texture region index is greater than 0 then the
		//texture region will be used for that tile
		unsigned int textureRegionIndex = _tileValues[tileIndex];

		if(textureRegionIndex > 0)
		{
			unsigned int textureRegionOffsetX = (double)((textureRegionIndex-1) % _numTextureTilesAcross) * _tileWidth;
			unsigned int textureRegionOffsetY = (floor((double)(textureRegionIndex-1) / (double)_numTextureTilesAcross)) * _tileHeight;

			//create a new tile instance
			Tile *tile = new Tile(_tileSheetFileURL, _textureName, tilePosition, textureRegionOffsetX, textureRegionOffsetY, _tileWidth, _tileHeight);

			//add the new tile
			addChild(tile);

			//add the tile to the list of tiles
			_tiles.push_back(tile);

			//increase tile count
			++ _numTiles;
		}
	}
}

void TileMap::render(SpriteBatch &spriteBatch, sf::Transform &transform)
{
	if(_visible)
	{
		//update the transform
		transform.translate(_position.x - _origin.x, _position.y - _origin.y).rotate(_angle, _origin.x, _origin.y).scale(_scale.x, _scale.y, _origin.x, _origin.y);

		//render the children
		DisplayObject::render(spriteBatch, transform);

		//undo the changes to the tranform
		transform.scale(1/_scale.x, 1/_scale.y, _origin.x, _origin.y).rotate(-_angle, _origin.x, _origin.y).translate(-_position.x + _origin.x, -_position.y + _origin.y);
	}
}

void TileMap::setTint(sf::Color colour)
{
	for(unsigned int tileIndex = 0; tileIndex < _numTiles; ++ tileIndex)
	{
		_tiles[tileIndex]->setTint(colour);
	}
}