#ifndef BITMAP_FONT_H
#define BITMAP_FONT_H

#include <string>
#include <map>
#include <SFML\Graphics.hpp>
#include "Vector2.h"
#include "Rect.h"
#include "SpriteBatch.h"

struct KerningPair
{
	unsigned int first;
	unsigned int second;
	int amount;
};

struct BitmapFontChar
{
	public:
		Rect<int> charTextureRegion;
		int xOffset;
		int yOffset;
		int xAdvance;
		int page;
};

class BitmapFont
{
	public:
		BitmapFont();
		virtual ~BitmapFont();
		void create(const std::string& fontFile, const std::string& bitmapFontImageFile, const std::string& textureName);
		int getKerning(unsigned int first, unsigned int second);
		sf::Texture *fontTexture;
		std::string face;
		float size;
		int lineHeight;
		int base;
		int width;
		int height;
		int pages;
		int outline;
		std::map<unsigned int, BitmapFontChar> bitmapChars;
		unsigned int charsLength;
	private:
		std::vector<KerningPair> _kerningPairs;
		unsigned int _kerningLength;
};

#endif