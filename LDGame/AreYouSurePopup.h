#ifndef ARE_YOU_SURE_H
#define ARE_YOU_SURE_H

#include "BasePopup.h"
#include "KeyListener.h"

#include <functional>

class BaseGuiWidget;
class EventData;

class AreYouSurePopup : public BasePopup, public KeyListener
{
	public:
		AreYouSurePopup(Vector2<float> onScreenPosition, Vector2<float> offScreenPosition, std::function<void()> onConfirmPressedCallback, std::function<void()> onCancelPressedCallback);
		virtual ~AreYouSurePopup();
		virtual void showPopup();
	protected:
		void onKeyPressed(EventData *eventData);
		void onKeyReleased(EventData *eventData);
	private:
		unsigned int _currentSelectedButtonIndex;
		std::function<void()> _onConfirmPressedCallback;
		std::function<void()> _onCancelPressedCallback;
		bool _directionKeyPressed;
		BaseGuiWidget* _confirmButton;
		BaseGuiWidget* _cancelButton;
};

#endif