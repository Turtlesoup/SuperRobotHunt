#ifndef LAYOUT_PROPERTY_H
#define LAYOUT_PROPERTY_H

#include <string>

class GuiLayoutProperty
{
	public:
		GuiLayoutProperty(/*NULL*/);
		GuiLayoutProperty(double value);
		GuiLayoutProperty(std::string value);
		GuiLayoutProperty(bool value);
		virtual ~GuiLayoutProperty();
		bool isNull() const;
		bool isNumber() const;
		bool isString() const;
		bool isBool() const;
		double asNumber() const;
		std::string asString() const;
		bool asBool() const;
	private:
		enum PROPERY_TYPES
		{
			TYPE_NULL,
			TYPE_NUMBER,
			TYPE_STRING,
			TYPE_BOOL
		};
		PROPERY_TYPES _type;
		double _numberValue;
		std::string _stringValue;
		bool _boolValue;
};

#endif