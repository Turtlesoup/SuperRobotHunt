#include "WaveText.h"
#include "Resources.h"
#include "BitmapFont.h"
#include "TextDisplayObject.h"
#include "GuiManager.h"
#include "StringHelper.h"

WaveText::WaveText(const Vector2<float> &position) : BorderedTextBox("", position, sf::Color(200, 0, 200, 255), sf::Color(255, 255, 255, 255), 30)
{
	//initialise with 0 for the score
	setWave(0);
}

WaveText::~WaveText()
{
}

void WaveText::setWave(unsigned int wave)
{
	setText("Wave: "+ std::to_string(wave));
}