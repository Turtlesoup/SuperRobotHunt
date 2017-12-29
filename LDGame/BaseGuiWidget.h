#ifndef BASE_GUI_WIDGET_H
#define BASE_GUI_WIDGET_H

#include "DisplayObject.h"
#include "GuiLayoutData.h"
#include "Rect.h"

class BaseGuiWidget : public DisplayObject
{
	public:
		BaseGuiWidget(GuiLayoutData &guiLayoutData);
		virtual ~BaseGuiWidget();
		GuiLayoutData &getGuiLayoutData();
	private:
		GuiLayoutData _guiLayoutData;
};

#endif