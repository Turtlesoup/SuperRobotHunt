#include "SFMLEventData.h"

SFMLEventData::SFMLEventData(sf::Event event) : EventData(),
												_event(event)
{
}

SFMLEventData::~SFMLEventData()
{
}

const sf::Event &SFMLEventData::getEvent()
{
	return _event;
}