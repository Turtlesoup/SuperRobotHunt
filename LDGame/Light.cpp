#include "Light.h"
#include "Application.h"
#include "Resources.h"

Light::Light(Vector2<float> position, sf::Color colour, float size) : SpriteDisplayObject(SPRITE_GAUSSIAN, TEXTURE_ATLAS_SPRITES, position),
																	  _scaleFactor(size/(_textureRegion.width * Application::zoom()))
{
	//reset effects of application zoom on lights
	_scale.x = _scaleFactor;
	_scale.y = _scaleFactor;
	_width = _textureRegion.width;
	_height = _textureRegion.height;

	//set the light colour
	setTint(colour);
}

Light::~Light()
{
}