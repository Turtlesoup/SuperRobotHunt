#include "TextureManager.h"

TextureManager *TextureManager::_instance = 0;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

TextureManager *TextureManager::Get()
{
	if(_instance == 0)
	{
		_instance = new TextureManager();
	}

	return _instance;
}

void TextureManager::loadTexture(const std::string &textureURL)
{
	sf::Texture texture;
	texture.loadFromFile(textureURL);
	_textureURLToTexture[textureURL] = texture;
}

void TextureManager::deleteTexture(const std::string &textureURL)
{
	_textureURLToTexture.erase(textureURL);
}

sf::Texture &TextureManager::getTexture(std::string textureURL)
{
	return _textureURLToTexture[textureURL];
}


void TextureManager::addTextureAtlas(std::string textureAtlasID, const TextureAtlas &textureAtlas)
{
	_textureAtlasIDToTextureAtlas[textureAtlasID] = textureAtlas;
}

void TextureManager::deleteTextureAtlas(std::string textureAtlasID)
{
	_textureAtlasIDToTextureAtlas.erase(textureAtlasID);
}

TextureAtlas &TextureManager::getTextureAtlas(std::string textureAtlasID)
{
	return _textureAtlasIDToTextureAtlas[textureAtlasID];
}