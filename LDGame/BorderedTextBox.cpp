#include "BorderedTextBox.h"
#include "Resources.h"
#include "BitmapFont.h"
#include "TextDisplayObject.h"
#include "GuiManager.h"
#include "StringHelper.h"

BorderedTextBox::BorderedTextBox(const std::string &text, const Vector2<float> &position, const sf::Color &mainColour, const sf::Color &borderColour, const float testSize) : DisplayObject(position),
																																											  TEXT_SIZE(testSize),
																																											  MAIN_COLOUR(mainColour),
																																											  BORDER_COLOUR(borderColour)
{
	BitmapFont &bitmapFont = GuiManager::Get()->getBitmapFont(FONT_FNT);

	_textBorder1 = new TextDisplayObject(text, bitmapFont, TEXT_SIZE, BORDER_COLOUR, ALIGNMENT::CENTER_ALIGN, Vector2<float>(-1,0));
	addChild(_textBorder1);

	_textBorder2 = new TextDisplayObject(text, bitmapFont, TEXT_SIZE, BORDER_COLOUR, ALIGNMENT::CENTER_ALIGN, Vector2<float>(1,0));
	addChild(_textBorder2);

	_textBorder3 = new TextDisplayObject(text, bitmapFont, TEXT_SIZE, BORDER_COLOUR, ALIGNMENT::CENTER_ALIGN, Vector2<float>(0,-1));
	addChild(_textBorder3);

	_textBorder4 = new TextDisplayObject(text, bitmapFont, TEXT_SIZE, BORDER_COLOUR, ALIGNMENT::CENTER_ALIGN, Vector2<float>(0,1));
	addChild(_textBorder4);

	_text = new TextDisplayObject(text, bitmapFont, TEXT_SIZE, MAIN_COLOUR, ALIGNMENT::CENTER_ALIGN, Vector2<float>());
	addChild(_text);

	setText(text);
}

BorderedTextBox::~BorderedTextBox()
{
}

void BorderedTextBox::setText(const std::string& text)
{
	_textBorder1->setText(text);
	_textBorder2->setText(text);
	_textBorder3->setText(text);
	_textBorder4->setText(text);
	_text->setText(text);
}