#include "TextGuiWidget.h"
#include "Vector2.h"
#include "GUIConsts.h"

TextGuiWidget::TextGuiWidget(GuiLayoutData &guiLayoutData, BitmapFont& bmFont) : BaseGuiWidget(guiLayoutData)
{
	std::string textString = guiLayoutData.properties[GUIConsts::TEXT].asString();
	float size = guiLayoutData.properties[GUIConsts::SIZE].asNumber();
	std::string alignmentText = guiLayoutData.properties[GUIConsts::ALIGNMENT].asString();

	ALIGNMENT alignment = LEFT_ALIGN;
	if(alignmentText == GUIConsts::ALIGNMENT_RIGHT)
	{
		alignment = RIGHT_ALIGN;
	}
	else if(alignmentText == GUIConsts::ALIGNMENT_CENTER)
	{
		alignment = CENTER_ALIGN;
	}

	//create a shadow text field if the offset is not 0,0
	float shadowOffsetX = guiLayoutData.properties[GUIConsts::SHADOW_OFFSET_X].asNumber();
	float shadowOffsetY = guiLayoutData.properties[GUIConsts::SHADOW_OFFSET_Y].asNumber();
	if(!(shadowOffsetX == 0 && shadowOffsetY == 0))
	{
		sf::Color shadowTint;
		shadowTint.r = guiLayoutData.properties[GUIConsts::SHADOW_TINT_RED].asNumber();
		shadowTint.g = guiLayoutData.properties[GUIConsts::SHADOW_TINT_GREEN].asNumber();
		shadowTint.b = guiLayoutData.properties[GUIConsts::SHADOW_TINT_BLUE].asNumber();
		shadowTint.a = guiLayoutData.properties[GUIConsts::SHADOW_TINT_ALPHA].asNumber();

		_shadowText = new TextDisplayObject(textString, bmFont, size, shadowTint, alignment, Vector2<float>(shadowOffsetX, shadowOffsetY));
		addChild(_shadowText);
	}

	//create main text field
	sf::Color tint;
	tint.r = guiLayoutData.properties[GUIConsts::TINT_RED].asNumber();
	tint.g = guiLayoutData.properties[GUIConsts::TINT_GREEN].asNumber();
	tint.b = guiLayoutData.properties[GUIConsts::TINT_BLUE].asNumber();
	tint.a = guiLayoutData.properties[GUIConsts::TINT_ALPHA].asNumber();

	_text = new TextDisplayObject(textString, bmFont, size, tint, alignment, Vector2<float>());
	addChild(_text);
}

TextGuiWidget::~TextGuiWidget()
{
}

TextDisplayObject *TextGuiWidget::getText()
{
	return _text;
}

TextDisplayObject *TextGuiWidget::getShadowText()
{
	return _shadowText;
}

void TextGuiWidget::setTextValue(std::string text)
{
	_text->setText(text);
	_shadowText->setText(text);
}

bool TextGuiWidget::hasShadow()
{
	return _shadowText != nullptr;
}