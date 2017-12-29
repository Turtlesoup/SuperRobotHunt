#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <map>
#include <vector>
#include <functional>

typedef int EVENT_TYPE;

enum EVENT_TYPES
{
	KEY_PRESSED,
	KEY_RELEASED,
	SFML_EVENT
};

class EventData;

class EventManager
{
	public:
		virtual ~EventManager();
		static EventManager* Get();
		int addEventListener(EVENT_TYPE eventType, std::function<void(EventData*)> callbackFunction);
		void removeEventListener(EVENT_TYPE eventType, unsigned int unqiueID);
		void dispatchEvent(EVENT_TYPE eventType, EventData *event);
	private:
		EventManager();
		static EventManager* _instance;
		std::map<EVENT_TYPE, std::map<int, std::function<void(EventData*)>>> _callbackFunctions;
		unsigned int _uniqueAutoID;
};


#endif