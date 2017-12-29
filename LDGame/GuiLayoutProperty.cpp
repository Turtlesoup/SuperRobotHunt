#include "GuiLayoutProperty.h"

GuiLayoutProperty::GuiLayoutProperty(/*NULL*/) : _type(TYPE_NULL)
{
}

GuiLayoutProperty::GuiLayoutProperty(double value) : _numberValue(value),
													 _type(TYPE_NUMBER)
{
}

GuiLayoutProperty::GuiLayoutProperty(std::string value) : _stringValue(value),
														  _type(TYPE_STRING)
{
}

GuiLayoutProperty::GuiLayoutProperty(bool value) : _boolValue(value),
												   _type(TYPE_BOOL)
{
}

GuiLayoutProperty::~GuiLayoutProperty()
{
}

bool GuiLayoutProperty::isNull() const
{
	return _type == TYPE_NULL;
}

bool GuiLayoutProperty::isNumber() const
{
	return _type == TYPE_NUMBER;
}

bool GuiLayoutProperty::isString() const
{
	return _type == TYPE_STRING;
}

bool GuiLayoutProperty::isBool() const
{
	return _type == TYPE_BOOL;
}

double GuiLayoutProperty::asNumber() const
{
	return _numberValue;
}

std::string GuiLayoutProperty::asString() const
{
	return _stringValue;
}

bool GuiLayoutProperty::asBool() const
{
	return _boolValue;
}