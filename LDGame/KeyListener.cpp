#include "KeyListener.h"
#include "EventManager.h"
#include "EventData.h"
#include <functional>

KeyListener::KeyListener(bool enable)
{
	if(enable)
	{
		enableListeners();
	}
}

KeyListener::~KeyListener()
{
	disableListeners();
}

void KeyListener::enableListeners()
{
	_keyPressedCallbackID = EventManager::Get()->addEventListener(EVENT_TYPES::KEY_PRESSED, std::bind<void>(&KeyListener::onKeyPressed, this, std::placeholders::_1));
	_keyReleasedCallbackID = EventManager::Get()->addEventListener(EVENT_TYPES::KEY_RELEASED, std::bind<void>(&KeyListener::onKeyReleased, this, std::placeholders::_1));
}

void KeyListener::disableListeners()
{
	EventManager::Get()->removeEventListener(EVENT_TYPES::KEY_PRESSED, _keyPressedCallbackID);
	EventManager::Get()->removeEventListener(EVENT_TYPES::KEY_RELEASED, _keyReleasedCallbackID);
}