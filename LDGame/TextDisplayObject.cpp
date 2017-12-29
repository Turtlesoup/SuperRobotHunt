#include "TextDisplayObject.h"
#include "Game.h"

TextDisplayObject::TextDisplayObject(std::string text, BitmapFont& font, unsigned int size, sf::Color tint, ALIGNMENT alignment, Vector2<float> position) : DisplayObject(position),
																																						    _text(text),
																																						    _font(font),
																																						    _size(size),
																																						    _tint(tint),
																																						    _alignment(alignment),
																																							_requiresRecompute(true)
{
}

TextDisplayObject::~TextDisplayObject()
{
}

void TextDisplayObject::render(SpriteBatch &spriteBatch, sf::Transform &transform)
{
	if(_visible)
	{
		//update the transform
		transform.translate(_position.x - _origin.x + _offset.x, _position.y - _origin.y + _offset.y).rotate(_angle, _origin.x, _origin.y).scale(_scale.x, _scale.y, _origin.x, _origin.y);

		//draw the text
		drawText(spriteBatch, transform);

		//undo the changes to the tranform
		transform.scale(1/_scale.x, 1/_scale.y, _origin.x, _origin.y).rotate(-_angle, _origin.x, _origin.y).translate(-_position.x + _origin.x - _offset.x, -_position.y + _origin.y - _offset.y);

		//render the children
		DisplayObject::render(spriteBatch, transform);
	}
}

void TextDisplayObject::setText(std::string value)
{
	if(value != _text)
	{
		_text = value;
		//set the required recompute flag
		_requiresRecompute = true;
	}
}

std::string TextDisplayObject::getText()
{
	return _text;
}

void TextDisplayObject::setAlignment(ALIGNMENT value)
{
	_alignment = value;
}

ALIGNMENT TextDisplayObject::getAlignment()
{
	return _alignment;
}

void TextDisplayObject::setTint(sf::Color tint)
{
	_tint = tint;
}

sf::Color &TextDisplayObject::getTint()
{
	return _tint;
}

void TextDisplayObject::drawText(SpriteBatch &spriteBatch, sf::Transform &transform)
{
	const char *chars = _text.c_str();
	unsigned int charsLength = _text.length();

	//if the text has not changed then we dont need to recompute the position of the characters
	//and can simply redraw the same characters in the same positions as the last render cycle
	if(_requiresRecompute && charsLength > 0)
	{
		recomputeCharacterPositions(chars, charsLength);
	}

	//based on the alignment, set the text alignment offsets
	float textAlignmentOffsetX = 0;
	switch(_alignment)
	{
		case LEFT_ALIGN:
			textAlignmentOffsetX = 0;
			break;
		case RIGHT_ALIGN:
			textAlignmentOffsetX = -_textWidth;
			break;
		case CENTER_ALIGN:
			textAlignmentOffsetX = -_textWidth*0.5;
			break;
	}

	float scale = _size/_font.size;
	
	//apply scale transform
	transform.scale(scale, scale);

	//render the text
	unsigned int currentChar;
	BitmapFontChar *bitmapChar;
	float charXPosition;
	for(unsigned int charsIndex = 0; charsIndex < charsLength; ++ charsIndex)
	{
		//get the current char and corresponding bitmap char
		currentChar = chars[charsIndex];
		bitmapChar = &_font.bitmapChars[currentChar];
		charXPosition = _characterXPositions[charsIndex];

		//translate the tranform by the current xAdvance value
		transform.translate(charXPosition + bitmapChar->xOffset + textAlignmentOffsetX, bitmapChar->yOffset);
		
		//draw the character
		spriteBatch.draw(_font.fontTexture, bitmapChar->charTextureRegion, _tint, transform);

		//undo the baseline offset from the transform
		transform.translate(-(charXPosition + bitmapChar->xOffset + textAlignmentOffsetX), -bitmapChar->yOffset);
	}

	//undo scale transform
	transform.scale(1/scale, 1/scale);
}

void TextDisplayObject::recomputeCharacterPositions(const char *chars, unsigned int charsLength)
{
	//compute the x positions for all the characters. this is only performed when the text changes
	//and allows for the width of the font to be determined before rendering allowing for the
	//alignment of the text to be modified
	unsigned int currentChar;
	BitmapFontChar bitmapChar;
	float xAdvance = 0;

	//clear the current character x positions vector
	_characterXPositions.clear();

	//set the first x position to 0
	_characterXPositions.push_back(0);

	for(unsigned int charsIndex = 0; charsIndex < charsLength - 1; ++ charsIndex)
	{
		//get the current char and corresponding bitmap char
		currentChar = chars[charsIndex];
		bitmapChar = _font.bitmapChars[currentChar];

		//set the kerning value for following letter to transform by
		xAdvance += _font.getKerning(currentChar, chars[charsIndex + 1]);

		//increase the xAdvance value for the following character
		xAdvance += bitmapChar.xAdvance;

		//add the xAdvance value to the vectors of character positions
		_characterXPositions.push_back(xAdvance);
	}

	//compute width of the text by adding the xAdvance and xoffset of the last character to the last character x position
	currentChar = chars[charsLength-1];
	bitmapChar = _font.bitmapChars[currentChar];
	_textWidth = _characterXPositions[charsLength-1] + bitmapChar.xAdvance + bitmapChar.xOffset;
}

float TextDisplayObject::getTextWidth()
{
	return _textWidth;
}