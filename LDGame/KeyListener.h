#ifndef KEY_LISTENER_H
#define KEY_LISTENER_H

class EventData;

class KeyListener
{
	public:
		KeyListener(bool enable = true);
		virtual ~KeyListener();
		void enableListeners();
		void disableListeners();
	protected:
		virtual void onKeyPressed(EventData *eventData) = 0;
		virtual void onKeyReleased(EventData *eventData) = 0;
		unsigned int _keyPressedCallbackID;
		unsigned int _keyReleasedCallbackID;
};

#endif