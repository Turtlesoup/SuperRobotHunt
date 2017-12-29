#ifndef TITLE_PANEL_H
#define TITLE_PANEL_H

#include "BasePopup.h"
#include "KeyListener.h"

#include <functional>

class BaseGuiWidget;
class EventData;

class TitlePanel : public BasePopup, public KeyListener
{
	public:
		TitlePanel(Vector2<float> onScreenPosition, Vector2<float> offScreenPosition, std::function<void()> onPlayPressedCallback, std::function<void()> onOptionsPressedCallback);
		virtual ~TitlePanel();
		virtual void showPopup();
	protected:
		void onKeyPressed(EventData *eventData);
		void onKeyReleased(EventData *eventData);
	private:
		unsigned int _currentSelectedButtonIndex;
		std::function<void()> _onPlayPressedCallback;
		std::function<void()> _onOptionsPressedCallback;
		bool _directionKeyPressed;
		BaseGuiWidget* _playButton;
		BaseGuiWidget* _optionsButton;
		BaseGuiWidget* _quitButton;
};

#endif