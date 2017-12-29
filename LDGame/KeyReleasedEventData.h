#ifndef KEY_RELEASED_EVENT_DATA_H
#define KEY_RELEASED_EVENT_DATA_H

#include "EventData.h"

class KeyReleasedEventData : public EventData
{
	public:
		KeyReleasedEventData(int keycode);
		virtual ~KeyReleasedEventData();
		int getKeycode();
	private:
		int _keycode;
};

#endif