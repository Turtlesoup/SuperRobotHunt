#ifndef WAVE_TEXT_H
#define WAVE_TEXT_H

#include "BorderedTextBox.h"

class TextDisplayObject;

class WaveText : public BorderedTextBox
{
	public:
		WaveText(const Vector2<float> &position);
		virtual ~WaveText();
		void setWave(unsigned int wave);
};

#endif