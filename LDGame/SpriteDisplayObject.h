#ifndef SPRITE_DISPLAY_OBJECT_H
#define SPRITE_DISPLAY_OBJECT_H

#include <string>
#include <SFML\Graphics.hpp>
#include "DisplayObject.h"
#include "SpriteBatch.h"

class SpriteDisplayObject : public DisplayObject
{
	public:
		SpriteDisplayObject(const std::string &fileName, const std::string &textureName, Vector2<float> &position);
		virtual ~SpriteDisplayObject();
		virtual void render(SpriteBatch &spriteBatch, sf::Transform &transform);
		unsigned int getWidth();
		unsigned int getHeight();
		void setWidth(float value);
		void setHeight(float value);
		sf::Texture &getTexture();
		Rect<int> &getTextureRegion();
		Rect<int> &getSpriteRect();
		void setTint(sf::Color tint);
		sf::Color &getTint();
	protected:
		sf::Texture &_texture;
		Rect<int> _textureRegion;
		Rect<int> _spriteRect;
		float _width;
		float _height;
		sf::Color _tint;
	private:
		float *tempTransform;
};

#endif