#include "BitmapFont.h"
#include "TextureManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 

BitmapFont::BitmapFont()
{
}

BitmapFont::~BitmapFont()
{
}

void BitmapFont::create(const std::string& fontFile, const std::string& bitmapFontImageFile, const std::string& textureName)
{
	fontTexture = &TextureManager::Get()->getTextureAtlas(textureName).texture();
	Rect<int> fontTextureRegion = TextureManager::Get()->getTextureAtlas(textureName).getTextureRegion(bitmapFontImageFile);
	unsigned int fontTextureRegionX = fontTextureRegion.left;
	unsigned int fontTextureRegionY = fontTextureRegion.top;

	//parse the .fnt file and populate the character and kerning datas
	std::ifstream stream(fontFile); 
	std::string line;
	std::string read, key, value;
	std::size_t i;

	KerningPair kerningPair;
	BitmapFontChar character;

	while(!stream.eof())
	{
		std::stringstream linestream;
		std::getline(stream, line);
		linestream << line;

		//read the line's type
		linestream >> read;

		if(read == "info")
		{
			//font info
			while(!linestream.eof())
			{
				std::stringstream converter;
				linestream >> read;
				i = read.find('=');
				key = read.substr(0, i);
				value = read.substr(i + 1);

				converter << value;
				if(key == "face")
				{
					converter >> face;
				}
				else if(key == "size")
				{
					converter >> size;
				}
			}
		}
		else if(read == "common")
		{
			//common data
			while(!linestream.eof())
			{
				std::stringstream converter;
				linestream >> read;
				i = read.find('=');
				key = read.substr(0, i);
				value = read.substr(i + 1);

				converter << value;
				if(key == "lineHeight")
				{
					converter >> lineHeight;
				}
				else if(key == "base")
				{
					converter >> base;
				}
				else if(key == "scaleW")
				{
					converter >> width;
				}
				else if(key == "scaleH")
				{
					converter >> height;
				}
				else if(key == "pages")
				{
					converter >> pages;
				}
				else if(key == "outline")
				{
					converter >> outline;
				}
			}
		}
		else if(read == "chars")
		{
			//kerning length data
			while(!linestream.eof())
			{
				std::stringstream converter;
				linestream >> read;
				i = read.find('=');
				key = read.substr(0, i);
				value = read.substr(i + 1);

				converter << value;
				if(key == "count")
				{
					converter >> charsLength;
				}
			}
		}
		else if(read == "char")
		{
			//char data
			unsigned int charID = 0;
			while(!linestream.eof())
			{
				std::stringstream converter;
				linestream >> read;
				i = read.find('=');
				key = read.substr(0, i);
				value = read.substr(i + 1);

				converter << value;
				if(key == "id")
				{
					converter >> charID;
				}
				else if(key == "x")
				{
					converter >> character.charTextureRegion.left;
					character.charTextureRegion.left += fontTextureRegionX;
				}      
				else if(key == "y")
				{
					converter >> character.charTextureRegion.top;
					character.charTextureRegion.top += fontTextureRegionY;
				}      
				else if(key == "width")
				{
					converter >> character.charTextureRegion.width;
				}        
				else if(key == "height")
				{
					converter >> character.charTextureRegion.height;
				}         
				else if(key == "xoffset")
				{
					converter >> character.xOffset;
				}         
				else if(key == "yoffset")
				{
					converter >> character.yOffset;
				}        
				else if(key == "xadvance")
				{
					converter >> character.xAdvance;
				}         
				else if(key == "page")
				{
					converter >> character.page;
				}           
			}
			
			bitmapChars[charID] = character;
		}
		else if(read == "kernings")
		{
			//kerning length data
			while(!linestream.eof())
			{
				std::stringstream converter;
				linestream >> read;
				i = read.find('=');
				key = read.substr(0, i);
				value = read.substr(i + 1);

				converter << value;
				if(key == "count")
				{
					converter >> _kerningLength;
				}
			}
		}
		else if(read == "kerning")
		{
			//kerning data
			while(!linestream.eof())
			{
				std::stringstream converter;
				linestream >> read;
				i = read.find('=');
				key = read.substr(0, i);
				value = read.substr(i + 1);

				//assign the correct value
				converter << value;
				if(key == "first")
				{
					converter >> kerningPair.first;
				}
				else if(key == "second")
				{
					converter >> kerningPair.second;
				}
				else if(key == "amount")
				{
					converter >> kerningPair.amount;
				}
 			}
			_kerningPairs.push_back(kerningPair);
		}
	}

	stream.close();
}

int BitmapFont::getKerning(unsigned int first, unsigned int second)
{
	std::vector<KerningPair>::iterator kerningPairBegin, kerningPairEnd, kerningPairIterator;
	kerningPairBegin = _kerningPairs.begin();
	kerningPairEnd = _kerningPairs.end();
	KerningPair kerningPair;
	for(kerningPairIterator = kerningPairBegin; kerningPairIterator != kerningPairEnd; ++ kerningPairIterator)
	{
		kerningPair = (*kerningPairIterator);
		if(kerningPair.first == first && kerningPair.second == second)
		{
			return kerningPair.amount;
		}
	}

	return 0;
}