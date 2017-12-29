#include "TextIndicator.h"
#include "GuiManager.h"
#include "BitmapFont.h"
#include "MathHelper.h"
#include "Resources.h"

TextIndicator::TextIndicator(std::string text, sf::Color &mainColour, sf::Color &borderColour, Vector2<float> position, float textSize) : DisplayObject(position),
																																		  _speed(0.01),
																																		  SPEED_Y_DECREASE(0.0001),
																																		  ALPHA_DECREASE(0.2),
																																		  MAX_VIBRATION_OFFSET(1),
																																		  _currentFadeDelay(200)
{
	_alpha = mainColour.a;

	BitmapFont &bitmapFont = GuiManager::Get()->getBitmapFont(FONT_FNT);

	_textObjectBorder1 = new TextDisplayObject(text, bitmapFont, textSize, borderColour, ALIGNMENT::CENTER_ALIGN, Vector2<float>(-1,0));
	addChild(_textObjectBorder1);

	_textObjectBorder2 = new TextDisplayObject(text, bitmapFont, textSize, borderColour, ALIGNMENT::CENTER_ALIGN, Vector2<float>(1,0));
	addChild(_textObjectBorder2);

	_textObjectBorder3 = new TextDisplayObject(text, bitmapFont, textSize, borderColour, ALIGNMENT::CENTER_ALIGN, Vector2<float>(0,-1));
	addChild(_textObjectBorder3);

	_textObjectBorder4 = new TextDisplayObject(text, bitmapFont, textSize, borderColour, ALIGNMENT::CENTER_ALIGN, Vector2<float>(0,1));
	addChild(_textObjectBorder4);

	_textObject = new TextDisplayObject(text, bitmapFont, textSize, mainColour, ALIGNMENT::CENTER_ALIGN, Vector2<float>());
	addChild(_textObject);
}

TextIndicator::~TextIndicator()
{
}

void TextIndicator::update(float deltaTime)
{
	DisplayObject::update(deltaTime);

	_offset.x = (MathHelper::randomFloat()*2*MAX_VIBRATION_OFFSET)-MAX_VIBRATION_OFFSET;
	_offset.y = (MathHelper::randomFloat()*2*MAX_VIBRATION_OFFSET)-MAX_VIBRATION_OFFSET;

	if(_speed > 0)
	{
		_position.y -= (_speed * deltaTime);
		_speed -= SPEED_Y_DECREASE;
	}

	if(_currentFadeDelay > 0)
	{
		_currentFadeDelay -= deltaTime;
	}
	else
	{
		_alpha -= ALPHA_DECREASE * deltaTime;

		if(_alpha <= 0)
		{
			getParent()->removeChild(this, true);
		}
		else
		{
			_textObject->getTint().a = _alpha;
			_textObjectBorder1->getTint().a = _alpha;
			_textObjectBorder2->getTint().a = _alpha;
			_textObjectBorder3->getTint().a = _alpha;
			_textObjectBorder4->getTint().a = _alpha;
		}
	}
}