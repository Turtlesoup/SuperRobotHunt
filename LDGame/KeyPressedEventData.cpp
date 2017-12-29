#include "KeyPressedEventData.h"

KeyPressedEventData::KeyPressedEventData(int keycode) : EventData(),
														_keycode(keycode)
{
}

KeyPressedEventData::~KeyPressedEventData()
{
}

int KeyPressedEventData::getKeycode()
{
	return _keycode;
}