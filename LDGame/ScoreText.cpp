#include "ScoreText.h"
#include "Resources.h"
#include "BitmapFont.h"
#include "TextDisplayObject.h"
#include "GuiManager.h"
#include "StringHelper.h"

ScoreText::ScoreText(const Vector2<float> &position, const sf::Color &mainColour, const sf::Color &borderColour, float size) : BorderedTextBox("", position, mainColour, borderColour, size),
																															   SCORE_LENGTH(10)
{
	//initialise with 0 for the score
	setScore(0);
}

ScoreText::~ScoreText()
{
}

void ScoreText::setScore(unsigned int score)
{
	setText(StringHelper::frontPadString(SCORE_LENGTH, '0', std::to_string(score)));
}