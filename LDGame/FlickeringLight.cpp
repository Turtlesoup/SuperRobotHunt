#include "FlickeringLight.h"
#include "MathHelper.h"

FlickeringLight::FlickeringLight(Vector2<float> position, sf::Color colour, float size, float flickerDelay) : Light(position, colour, size),
																											FLICKER_DELAY(flickerDelay),
																											_currentFlickerDelay(0)
{
}

FlickeringLight::~FlickeringLight()
{
}

void FlickeringLight::update(float deltaTime)
{
	_currentFlickerDelay += deltaTime;
	if(_currentFlickerDelay >= FLICKER_DELAY)
	{
		float val = (_scaleFactor * 0.9) + (MathHelper::randomFloat() * (_scaleFactor * 0.1));
		_scale.x = val;
		_scale.y = val;

		_currentFlickerDelay = 0.0;
	}
}