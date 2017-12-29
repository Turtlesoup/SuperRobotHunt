#include "BaseGuiWidget.h"
#include "StringHelper.h"
#include "Vector2.h"

BaseGuiWidget::BaseGuiWidget(GuiLayoutData &guiLayoutData) : DisplayObject(Vector2<float>(guiLayoutData.x, guiLayoutData.y)),
															 _guiLayoutData(guiLayoutData)
{
}

BaseGuiWidget::~BaseGuiWidget()
{
}

GuiLayoutData &BaseGuiWidget::getGuiLayoutData()
{
	return _guiLayoutData;
}