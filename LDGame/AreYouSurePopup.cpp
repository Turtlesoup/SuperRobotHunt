#include "AreYouSurePopup.h"
#include "EventManager.h"
#include "BaseGuiWidget.h"
#include "ButtonGuiWidget.h"
#include "KeyPressedEventData.h"
#include "KeyReleasedEventData.h"
#include "GuiManager.h"
#include "Resources.h"
#include "AudioManager.h"

const std::string CONFIRM_BUTTON_ID = "2";
const std::string CANCEL_BUTTON_ID = "6";

AreYouSurePopup::AreYouSurePopup(Vector2<float> onScreenPosition, Vector2<float> offScreenPosition, std::function<void()> onConfirmPressedCallback, std::function<void()> onCancelPressedCallback) : BasePopup(onScreenPosition, offScreenPosition, GUI_JSON_ARE_YOU_SURE_POPUP),
																																																	 KeyListener(),
																																																	 _currentSelectedButtonIndex(0),
																																																	 _onConfirmPressedCallback(onConfirmPressedCallback),
																																																	 _onCancelPressedCallback(onCancelPressedCallback),
																																																	 _directionKeyPressed(false)
{
	_confirmButton = GuiManager::Get()->getWidgetWithID(CONFIRM_BUTTON_ID, _popupWidget);
	_cancelButton = GuiManager::Get()->getWidgetWithID(CANCEL_BUTTON_ID, _popupWidget);
}

AreYouSurePopup::~AreYouSurePopup()
{
}

void AreYouSurePopup::showPopup()
{
	BasePopup::showPopup();

	_currentSelectedButtonIndex = 1;
	static_cast<ButtonGuiWidget*>(_buttons[_currentSelectedButtonIndex])->onSelected();

	_directionKeyPressed = false;
}

void AreYouSurePopup::onKeyPressed(EventData *eventData)
{
	KeyPressedEventData *keyPressedEventData = dynamic_cast<KeyPressedEventData*>(eventData);
	if(keyPressedEventData != nullptr)
	{
		switch(keyPressedEventData->getKeycode())
		{
			case sf::Keyboard::X:
				static_cast<ButtonGuiWidget*>(_buttons[_currentSelectedButtonIndex])->onPressed();
				break;
			case sf::Keyboard::Up:
			case sf::Keyboard::Down:
				_directionKeyPressed = true;
				break;
		}
	}
}

void AreYouSurePopup::onKeyReleased(EventData *eventData)
{
	KeyReleasedEventData *keyReleasedEventData = dynamic_cast<KeyReleasedEventData*>(eventData);
	if(keyReleasedEventData != nullptr)
	{
		switch(keyReleasedEventData->getKeycode())
		{
			case sf::Keyboard::X:
				if(_buttons[_currentSelectedButtonIndex] == _confirmButton)
				{
					_onConfirmPressedCallback();
				}
				else if(_buttons[_currentSelectedButtonIndex] == _cancelButton)
				{
					_onCancelPressedCallback();
				}
				static_cast<ButtonGuiWidget*>(_buttons[_currentSelectedButtonIndex])->onRelease();
				AudioManager::Get()->playSound(AUDIO_BUTTON_RELEASED);
				break;
			case sf::Keyboard::Up:
				if(_directionKeyPressed)
				{
					static_cast<ButtonGuiWidget*>(_buttons[_currentSelectedButtonIndex])->onDeselected();
					if(_currentSelectedButtonIndex == 0)
					{
						_currentSelectedButtonIndex = _buttons.size() - 1;
					}
					else
					{
						-- _currentSelectedButtonIndex;
					}
					static_cast<ButtonGuiWidget*>(_buttons[_currentSelectedButtonIndex])->onSelected();
					_directionKeyPressed = false;
				}
				break;
			case sf::Keyboard::Down:
				if(_directionKeyPressed)
				{
					static_cast<ButtonGuiWidget*>(_buttons[_currentSelectedButtonIndex])->onDeselected();
					if(_currentSelectedButtonIndex >= _buttons.size() - 1)
					{
						_currentSelectedButtonIndex = 0;
					}
					else
					{
						++ _currentSelectedButtonIndex;
					}
					static_cast<ButtonGuiWidget*>(_buttons[_currentSelectedButtonIndex])->onSelected();
					_directionKeyPressed = false;
				}
				break;
		}
	}
}