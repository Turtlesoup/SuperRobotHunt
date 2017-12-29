#ifndef BORDERED_TEXT_BOX_H
#define BORDERED_TEXT_BOX_H

#include "DisplayObject.h"
#include <SFML\Graphics.hpp>

class TextDisplayObject;

class BorderedTextBox : public DisplayObject
{
	public:
		BorderedTextBox(const std::string &text, const Vector2<float> &position, const sf::Color &mainColour, const sf::Color &borderColour, const float testSize);
		virtual ~BorderedTextBox();
		virtual void setText(const std::string& text);
	protected:
		TextDisplayObject *_text;
		TextDisplayObject *_textBorder1;
		TextDisplayObject *_textBorder2;
		TextDisplayObject *_textBorder3;
		TextDisplayObject *_textBorder4;
		const float TEXT_SIZE;
		const sf::Color MAIN_COLOUR;
		const sf::Color BORDER_COLOUR;
};

#endif