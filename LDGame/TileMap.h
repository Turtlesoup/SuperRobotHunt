#ifndef TILE_MAP_H
#define TIME_MAP_H

#include <SFML\Graphics.hpp>
#include <vector>
#include <string>
#include <map>
#include "DisplayObject.h"

class Tile;

class TileMap : public DisplayObject
{
	public:
		TileMap(const Vector2<float>& position);
		virtual ~TileMap();
		void create(unsigned int width, unsigned int height, unsigned int tileWidth, unsigned int tileHeight, const std::string& tileSheetFileURL, const std::string& textureName, const std::string& delimitedFilename, char delimiter = ',');
		void create(unsigned int width, unsigned int height, unsigned int tileWidth, unsigned int tileHeight, const std::string& tileSheetFileURL, const std::string& textureName, const std::vector<unsigned int>& tileValues);
		void render(SpriteBatch &spriteBatch, sf::Transform &transform);
		void setTint(sf::Color colour);
	protected:
		virtual void createTile(unsigned int tileIndex, Vector2<float> tilePosition);
		std::vector<unsigned int> _tileValues;
		std::vector<Tile*> _tiles;
		unsigned int _numTiles;
		unsigned int _numTilesAcross;
		unsigned int _numTilesDown;
		unsigned int _numTextureTilesAcross;
		unsigned int _numTextureTilesDown;
		float _tileWidth;
		float _tileHeight;
		std::string _tileSheetFileURL;
		std::string _textureName;
};

#endif