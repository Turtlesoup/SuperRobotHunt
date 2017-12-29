#ifndef LAYOUT_DATA_H
#define LAYOUT_DATA_H

#include <vector>
#include <string>
#include <map>
#include "GuiLayoutProperty.h"
#include "DisplayObject.h"
#include "WidgetTypes.h"

class GuiLayoutData
{
	public:
		GuiLayoutData();
		virtual ~GuiLayoutData();
		std::string id;
		WIDGET_TYPE type;
		std::string name;
		float x;
		float y;
		std::map<std::string, GuiLayoutProperty> properties;
		std::vector<GuiLayoutData> children;
	private:
};

#endif