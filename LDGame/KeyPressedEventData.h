#ifndef KEY_PRESSED_EVENT_DATA_H
#define KEY_PRESSED_EVENT_DATA_H

#include "EventData.h"

class KeyPressedEventData : public EventData
{
	public:
		KeyPressedEventData(int keycode);
		virtual ~KeyPressedEventData();
		int getKeycode();
	private:
		int _keycode;
};

#endif