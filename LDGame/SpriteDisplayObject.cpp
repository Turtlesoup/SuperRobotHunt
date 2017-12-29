#include "SpriteDisplayObject.h"
#include "TextureManager.h"
#include "Application.h"
#include "SpriteBatch.h"

SpriteDisplayObject::SpriteDisplayObject(const std::string &fileName, const std::string &textureName, Vector2<float> &position) : DisplayObject(position),
																																  _texture(TextureManager::Get()->getTextureAtlas(textureName).texture()),
																																  _textureRegion(TextureManager::Get()->getTextureAtlas(textureName).getTextureRegion(fileName)),
																																  _spriteRect(_textureRegion),
																																  _width((float)_textureRegion.width),
																																  _height((float)_textureRegion.height),
																																  _tint(sf::Color(255, 255, 255))
{
	tempTransform = new float[16];

	_origin.x = _width*0.5;
	_origin.y = _height*0.5;
}

SpriteDisplayObject::~SpriteDisplayObject()
{
	delete[] tempTransform;
}

void SpriteDisplayObject::render(SpriteBatch &spriteBatch, sf::Transform &transform)
{
	if(_visible)
	{
		//create a copy of the transform before applying translation, rotation and scale.
		memcpy((void*)tempTransform, transform.getMatrix(), 16*sizeof(float));

		//update the transform
		transform.translate(_position.x - _origin.x + _offset.x, _position.y - _origin.y + _offset.y).rotate(_angle, _origin.x, _origin.y).scale(_scale.x, _scale.y, _origin.x, _origin.y);

		//draw the sprite
		spriteBatch.draw(&_texture, _spriteRect, _tint, transform);

		//render the children
		DisplayObject::render(spriteBatch, transform);

		//undo the changes to the tranform
		memcpy((void*)transform.getMatrix(), tempTransform, 16*sizeof(float));
	}
}

unsigned int SpriteDisplayObject::getWidth()
{
	return _width * _scale.x;
}

unsigned int SpriteDisplayObject::getHeight()
{
	return _height * _scale.y;
}

void SpriteDisplayObject::setWidth(float value)
{
	setScale(value/_width, _scale.y);
}

void SpriteDisplayObject::setHeight(float value)
{
	setScale(_scale.x, value/_height);
}

sf::Texture &SpriteDisplayObject::getTexture()
{
	return _texture;
}

Rect<int> &SpriteDisplayObject::getTextureRegion()
{
	return _textureRegion;
}

Rect<int> &SpriteDisplayObject::getSpriteRect()
{
	return _spriteRect;
}

void SpriteDisplayObject::setTint(sf::Color tint)
{
	_tint = tint;
}

sf::Color &SpriteDisplayObject::getTint()
{
	return _tint;
}