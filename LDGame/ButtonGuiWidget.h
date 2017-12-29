#ifndef BUTTON_GUI_WIDGET
#define BUTTON_GUI_WIDGET

#include <functional>
#include "BaseSpriteGuiWidget.h"
#include "GuiLayoutData.h"

#include <SFML\Graphics\Color.hpp>

class ButtonGuiWidget : public BaseSpriteGuiWidget
{
	public:
		ButtonGuiWidget(GuiLayoutData &guiLayoutData);
		virtual ~ButtonGuiWidget();
		void setOnPressedCallback(std::function<void()> value);
		virtual void onPressed();
		virtual void onRelease();
		virtual void onSelected();
		virtual void onDeselected();
		virtual void setScale(float scaleX, float scaleY);
		virtual void setScale(Vector2<float> scale);
	protected:
		float _pressedScaleFactor;
		float _defaultScaleFactorX;
		float _defaultScaleFactorY;
		float _selectedScaleFactorX;
		float _selectedScaleFactorY;
		bool _selected;
		sf::Color _defaultTint;
		sf::Color _selectedTint;
		std::function<void()> _onPressedCallback;
};

#endif