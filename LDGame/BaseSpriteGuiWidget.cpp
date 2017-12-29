#include "BaseSpriteGuiWidget.h"
#include "Resources.h"
#include "GUIConsts.h"

BaseSpriteGuiWidget::BaseSpriteGuiWidget(GuiLayoutData &guiLayoutData) : BaseGuiWidget(guiLayoutData)
{
	_sprite = new SpriteDisplayObject(guiLayoutData.properties[GUIConsts::IMAGE_URL].asString(), TEXTURE_ATLAS_SPRITES, Vector2<float>(0, 0));

	float width =  guiLayoutData.properties[GUIConsts::WIDTH].asNumber();
	float height =  guiLayoutData.properties[GUIConsts::HEIGHT].asNumber();

	_sprite->setWidth(width);
	_sprite->setHeight(height);
	addChild(_sprite);
}

BaseSpriteGuiWidget::~BaseSpriteGuiWidget()
{
}