#ifndef MENU_POPUP_H
#define MENU_POPUP_H

#include "BasePopup.h"
#include "KeyListener.h"

#include <functional>

class BaseGuiWidget;
class EventData;

class MenuPopup : public BasePopup, public KeyListener
{
	public:
		MenuPopup(Vector2<float> onScreenPosition, Vector2<float> offScreenPosition, std::function<void()> onContinuePressedCallback, std::function<void()> onOptionsPressedCallback, std::function<void()> onQuitPressedCallback);
		virtual ~MenuPopup();
		virtual void showPopup();
	protected:
		void onKeyPressed(EventData *eventData);
		void onKeyReleased(EventData *eventData);
	private:
		unsigned int _currentSelectedButtonIndex;
		std::function<void()> _onContinuePressedCallback;
		std::function<void()> _onOptionsPressedCallback;
		std::function<void()> _onQuitPressedCallback;
		bool _directionKeyPressed;
		BaseGuiWidget* _continueButton;
		BaseGuiWidget* _optionsButton;
		BaseGuiWidget* _quitButton;
};

#endif