#ifndef FLICKER_LIGHT_H
#define FLICKER_LIGHT_H

#include "Light.h"

class FlickeringLight : public Light
{
	public:
		FlickeringLight(Vector2<float> position, sf::Color colour, float size, float flickerDelay);
		virtual ~FlickeringLight();
		virtual void update(float deltaTime);
	private:
		const float FLICKER_DELAY;
		float _currentFlickerDelay;
};

#endif