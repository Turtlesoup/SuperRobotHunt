#ifndef LIGHT_H
#define LIGHT_H

#include "SpriteDisplayObject.h"
#include <SFML\Graphics.hpp>

struct LightProperties
{
	Vector2<float> offset;
	sf::Color colour;
	float size;
};

class Light : public SpriteDisplayObject
{
	public:
		Light(Vector2<float> position, sf::Color colour, float size);
		~Light();
	protected:
		float _scaleFactor;
};

#endif