#ifndef OPTIONS_POPUP_H
#define OPTIONS_POPUP_H

#include "BasePopup.h"
#include "KeyListener.h"

#include <functional>

class BaseGuiWidget;
class TextGuiWidget;
class EventData;

class OptionsPopup : public BasePopup, public KeyListener
{
	public:
		OptionsPopup(Vector2<float> onScreenPosition, Vector2<float> offScreenPosition, std::function<void()> onPopupClosedCallback);
		virtual ~OptionsPopup();
		virtual void showPopup();
	protected:
		void onKeyPressed(EventData *eventData);
		void onKeyReleased(EventData *eventData);
	private:
		void updateButtonText();
		unsigned int _currentSelectedButtonIndex;
		bool _directionKeyPressed;
		std::function<void()> _onPopupClosedCallback;
		BaseGuiWidget* _soundButton;
		BaseGuiWidget* _musicButton;
		BaseGuiWidget* _backButton;
		TextGuiWidget* _soundButtonText;
		TextGuiWidget* _musicButtonText;
};

#endif