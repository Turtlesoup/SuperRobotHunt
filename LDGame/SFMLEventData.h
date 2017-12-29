#ifndef SFML_EVENT_DATA_H
#define SFML_EVENT_DATA_H

#include "EventData.h"

#include <SFML\Window\Event.hpp>

class SFMLEventData : public EventData
{
	public:
		SFMLEventData(sf::Event event);
		virtual ~SFMLEventData();
		const sf::Event &getEvent();
	private:
		const sf::Event _event;
};

#endif