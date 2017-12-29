#ifndef GUI_CONSTS_H
#define GUI_CONSTS_H

#include <string>

namespace GUIConsts
{
	//JSON keys
	extern const std::wstring ID;
	extern const std::wstring NAME;
	extern const std::wstring TYPE;
	extern const std::wstring X;
	extern const std::wstring Y;
	extern const std::wstring PROPERTIES;
	extern const std::wstring KEY;
	extern const std::wstring VALUE;
	extern const std::wstring CHILDREN;

	//widget types
	extern const std::string WIDGET_GROUP;
	extern const std::string WIDGET_PANEL;
	extern const std::string WIDGET_BUTTON;
	extern const std::string WIDGET_TEXT;

	//properties
	extern const std::string FONT_FILE;
	extern const std::string IMAGE_URL;
	extern const std::string WIDTH;
	extern const std::string HEIGHT;
	extern const std::string TEXT;
	extern const std::string SIZE;
	extern const std::string ALIGNMENT;
	extern const std::string ALIGNMENT_LEFT;
	extern const std::string ALIGNMENT_RIGHT;
	extern const std::string ALIGNMENT_CENTER;
	extern const std::string TINT_RED;
	extern const std::string TINT_GREEN;
	extern const std::string TINT_BLUE;
	extern const std::string TINT_ALPHA;
	extern const std::string SHADOW_OFFSET_X;
	extern const std::string SHADOW_OFFSET_Y;
	extern const std::string SHADOW_TINT_RED;
	extern const std::string SHADOW_TINT_GREEN;
	extern const std::string SHADOW_TINT_BLUE;
	extern const std::string SHADOW_TINT_ALPHA;
	extern const std::string PRESSED_SCALE_FACTOR;
}

#endif