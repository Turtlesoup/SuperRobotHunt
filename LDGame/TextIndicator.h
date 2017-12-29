#ifndef TEXT_INDICATOR_H
#define TEXT_INDICATOR_H

#include "DisplayObject.h"
#include "TextDisplayObject.h"
#include "Vector2.h"

class TextIndicator : public DisplayObject
{
	public:
		TextIndicator(std::string text, sf::Color &mainColour, sf::Color &borderColour, Vector2<float> position, float textSize);
		virtual ~TextIndicator();
		void update(float deltaTime);
	private:
		const float SPEED_Y_DECREASE;
		const float ALPHA_DECREASE;
		const float MAX_VIBRATION_OFFSET;
		float _speed;
		float _alpha;
		float _currentFadeDelay;
		TextDisplayObject *_textObject;
		TextDisplayObject *_textObjectBorder1;
		TextDisplayObject *_textObjectBorder2;
		TextDisplayObject *_textObjectBorder3;
		TextDisplayObject *_textObjectBorder4;
};

#endif