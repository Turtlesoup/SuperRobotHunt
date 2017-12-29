#ifndef SCORE_TEXT_H
#define SCORE_TEXT_H

#include "BorderedTextBox.h"
#include <SFML\Graphics.hpp>

class TextDisplayObject;

class ScoreText : public BorderedTextBox
{
	public:
		ScoreText(const Vector2<float> &position, const sf::Color &mainColour, const sf::Color &borderColour, float size);
		virtual ~ScoreText();
		void setScore(unsigned int score);
	private:
		const unsigned int SCORE_LENGTH;
};

#endif