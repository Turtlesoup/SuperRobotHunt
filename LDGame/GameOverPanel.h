#ifndef GAME_OVER_PANEL_H
#define GAME_OVER_PANEL_H

#include "BasePopup.h"
#include "KeyListener.h"

#include <functional>

class BaseGuiWidget;
class EventData;

class GameOverPanel : public BasePopup, public KeyListener
{
	public:
		GameOverPanel(Vector2<float> onScreenPosition, Vector2<float> offScreenPosition, std::function<void()> onRetryPressedCallback, std::function<void()> onQuitPressedCallback);
		virtual ~GameOverPanel();
		virtual void showPopup();
	protected:
		void onKeyPressed(EventData *eventData);
		void onKeyReleased(EventData *eventData);
	private:
		unsigned int _currentSelectedButtonIndex;
		std::function<void()> _onRetryPressedCallback;
		std::function<void()> _onQuitPressedCallback;
		bool _selectKeyPressed;
		bool _directionKeyPressed;
		BaseGuiWidget* _retryButton;
		BaseGuiWidget* _quitButton;
};

#endif