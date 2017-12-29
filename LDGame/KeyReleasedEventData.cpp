#include "KeyReleasedEventData.h"

KeyReleasedEventData::KeyReleasedEventData(int keycode) : EventData(),
														  _keycode(keycode)
{
}

KeyReleasedEventData::~KeyReleasedEventData()
{
}

int KeyReleasedEventData::getKeycode()
{
	return _keycode;
}