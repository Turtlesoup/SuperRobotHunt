#ifndef TEXT_DISPLAY_OBJECT_H
#define TEXT_DISPLAY_OBJECT_H

#include <SFML\Graphics.hpp>
#include <string>
#include "DisplayObject.h"
#include "SpriteBatch.h"
#include "BitmapFont.h"
#include "Rect.h"

enum ALIGNMENT
{
	LEFT_ALIGN,
	RIGHT_ALIGN,
	CENTER_ALIGN
};

class TextDisplayObject : public DisplayObject
{
	public:
		TextDisplayObject(std::string text, BitmapFont& font, unsigned int size, sf::Color tint, ALIGNMENT alignment, Vector2<float> position);
		virtual ~TextDisplayObject();
		virtual void render(SpriteBatch &spriteBatch, sf::Transform &transform);
		void setText(std::string value);
		std::string getText();
		void setAlignment(ALIGNMENT value);
		ALIGNMENT getAlignment();
		void setTint(sf::Color tint);
		sf::Color &getTint();
	protected:
		std::string _text;
		BitmapFont& _font;
		unsigned int _size;
		sf::Color _tint;
		ALIGNMENT _alignment;
	private:
		void drawText(SpriteBatch &spriteBatch, sf::Transform &transform);
		float getTextWidth();
		void recomputeCharacterPositions(const char *chars, unsigned int charsLength);
		std::vector<float> _characterXPositions;
		float _textWidth;
		bool _requiresRecompute;
};

#endif