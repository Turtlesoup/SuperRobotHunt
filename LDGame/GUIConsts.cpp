#include "GUIConsts.h"

namespace GUIConsts
{
	//JSON keys
	extern const std::wstring ID = L"id";
	extern const std::wstring NAME = L"name";
	extern const std::wstring TYPE = L"type";
	extern const std::wstring X = L"x";
	extern const std::wstring Y = L"y";
	extern const std::wstring PROPERTIES = L"properties";
	extern const std::wstring KEY = L"key";
	extern const std::wstring VALUE = L"value";
	extern const std::wstring CHILDREN = L"children";

	//widget types
	extern const std::string WIDGET_GROUP = "group";
	extern const std::string WIDGET_PANEL = "panel";
	extern const std::string WIDGET_BUTTON = "button";
	extern const std::string WIDGET_TEXT = "text";

	//properties
	extern const std::string FONT_FILE = "fontFile";
	extern const std::string IMAGE_URL = "imageURL";
	extern const std::string WIDTH = "width";
	extern const std::string HEIGHT = "height";
	extern const std::string TEXT = "text";
	extern const std::string SIZE = "size";
	extern const std::string ALIGNMENT = "alignment";
	extern const std::string ALIGNMENT_LEFT = "left";
	extern const std::string ALIGNMENT_RIGHT = "right";
	extern const std::string ALIGNMENT_CENTER = "center";
	extern const std::string TINT_RED = "tintRed";
	extern const std::string TINT_GREEN = "tintGreen";
	extern const std::string TINT_BLUE = "tintBlue";
	extern const std::string TINT_ALPHA = "tintAlpha";
	extern const std::string SHADOW_OFFSET_X = "shadowOffsetX";
	extern const std::string SHADOW_OFFSET_Y = "shadowOffsetY";
	extern const std::string SHADOW_TINT_RED = "shadowTintRed";
	extern const std::string SHADOW_TINT_GREEN = "shadowTintGreen";
	extern const std::string SHADOW_TINT_BLUE = "shadowTintBlue";
	extern const std::string SHADOW_TINT_ALPHA = "shadowTintAlpha";
	extern const std::string PRESSED_SCALE_FACTOR = "pressedScaleFactor";
}