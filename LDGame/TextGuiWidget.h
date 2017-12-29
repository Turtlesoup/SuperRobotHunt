#ifndef TEXT_GUI_WIDGET_H
#define TEXT_GUI_WIDGET_H

#include "BaseGuiWidget.h"
#include "GuiLayoutData.h"
#include "TextDisplayObject.h"
#include "BitmapFont.h"

class TextGuiWidget : public BaseGuiWidget
{
	public:
		TextGuiWidget(GuiLayoutData &guiLayoutData, BitmapFont& bmFont);
		virtual ~TextGuiWidget();
		TextDisplayObject *getText();
		TextDisplayObject *getShadowText();
		void setTextValue(std::string text);
		bool hasShadow();
	protected:
		TextDisplayObject *_text;
		TextDisplayObject *_shadowText;
};

#endif