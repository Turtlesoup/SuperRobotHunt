#include "ButtonGuiWidget.h"
#include "StringHelper.h"
#include "GUIConsts.h"

ButtonGuiWidget::ButtonGuiWidget(GuiLayoutData &guiLayoutData) : BaseSpriteGuiWidget(guiLayoutData),
																 _defaultScaleFactorX(1),
																 _defaultScaleFactorY(1),
																 _selectedScaleFactorX(1.1),
																 _selectedScaleFactorY(1.1),
																 _defaultTint(sf::Color(150,150,150,255)),
																 _selectedTint(sf::Color(255,255,255,255)),
																 _selected(false)
{
	_pressedScaleFactor = guiLayoutData.properties[GUIConsts::PRESSED_SCALE_FACTOR].asNumber();
	onDeselected();
}

ButtonGuiWidget::~ButtonGuiWidget()
{
}

void ButtonGuiWidget::setOnPressedCallback(std::function<void()> value)
{
	_onPressedCallback = value;
}

void ButtonGuiWidget::onPressed()
{
	BaseSpriteGuiWidget::setScale(_pressedScaleFactor, _pressedScaleFactor);

	if(_onPressedCallback)
	{
		_onPressedCallback();
	}
}

void ButtonGuiWidget::onRelease()
{
	if(_selected)
	{
		BaseSpriteGuiWidget::setScale(_selectedScaleFactorX, _selectedScaleFactorY);
	}
	else
	{
		BaseSpriteGuiWidget::setScale(_defaultScaleFactorX, _defaultScaleFactorY);
	}
}

void ButtonGuiWidget::onSelected()
{
	BaseSpriteGuiWidget::setScale(_selectedScaleFactorX, _selectedScaleFactorY);
	_sprite->setTint(_selectedTint);
	_selected = true;
}

void ButtonGuiWidget::onDeselected()
{
	BaseSpriteGuiWidget::setScale(_defaultScaleFactorX, _defaultScaleFactorY);
	_sprite->setTint(_defaultTint);
	_selected = false;
}

void ButtonGuiWidget::setScale(float scaleX, float scaleY)
{
	BaseSpriteGuiWidget::setScale(scaleX, scaleY);

	_defaultScaleFactorX = scaleX;
	_defaultScaleFactorY = scaleY;
}

void ButtonGuiWidget::setScale(Vector2<float> scale)
{
	BaseSpriteGuiWidget::setScale(scale);

	_defaultScaleFactorX = scale.x;
	_defaultScaleFactorY = scale.y;
}