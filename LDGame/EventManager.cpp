#include "EventManager.h"
#include "EventData.h"

#include <algorithm>
#include <typeindex>

EventManager* EventManager::_instance = nullptr;

EventManager::EventManager() : _uniqueAutoID(0)
{
}

EventManager::~EventManager()
{
}

EventManager* EventManager::Get()
{
	if(_instance == nullptr)
	{
		_instance = new EventManager();
	}
		
	return _instance;
}

int EventManager::addEventListener(EVENT_TYPE eventType, std::function<void(EventData*)> callbackFunction)
{
	//add the element to the corresponding vector for the given key
	_callbackFunctions[eventType][_uniqueAutoID] = callbackFunction;

	//increase auto id
	++ _uniqueAutoID;

	return _uniqueAutoID - 1;
}

void EventManager::removeEventListener(EVENT_TYPE eventType, unsigned int unqiueID)
{
	//removes the given callback from the callback list for the given type if such a callback exists
	std::map<int, std::function<void(EventData*)>> &callbacks = _callbackFunctions[eventType];
	std::map<int, std::function<void(EventData*)>>::iterator callbacksIterator, callbacksEnd;
	for(callbacksIterator = callbacks.begin(), callbacksEnd = callbacks.end(); callbacksIterator != callbacksEnd; ++ callbacksIterator)
	{
		if((*callbacksIterator).first == unqiueID)
		{
			callbacks.erase(callbacksIterator);
			break;
		}
	}
}

void EventManager::dispatchEvent(EVENT_TYPE eventType, EventData *eventData)
{
	//dispatch the given event to all callbacks of the given type
	std::map<int, std::function<void(EventData*)>> callbacks = _callbackFunctions[eventType];
	std::map<int, std::function<void(EventData*)>>::iterator callbacksIterator, callbacksEnd;
	std::function<void(EventData*)> callback;
	for(callbacksIterator = callbacks.begin(), callbacksEnd = callbacks.end(); callbacksIterator != callbacksEnd; ++ callbacksIterator)
	{
		callback = (*callbacksIterator).second;
		callback(eventData);
	}

	//destroy the event
	delete eventData;
}