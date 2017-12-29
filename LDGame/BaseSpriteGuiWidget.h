#ifndef BASE_SPRITE_GUI_WIDGET_H
#define BASE_SPRITE_GUI_WIDGET_H

#include "SpriteDisplayObject.h"
#include "BaseGuiWidget.h"
#include "GuiLayoutData.h"

class BaseSpriteGuiWidget : public BaseGuiWidget
{
	public:
		BaseSpriteGuiWidget(GuiLayoutData &guiLayoutData);
		~BaseSpriteGuiWidget();
	protected:
		SpriteDisplayObject *_sprite;
};

#endif