#include "MenuPopup.h"
#include "EventManager.h"
#include "BaseGuiWidget.h"
#include "ButtonGuiWidget.h"
#include "KeyPressedEventData.h"
#include "KeyReleasedEventData.h"
#include "GuiManager.h"
#include "Resources.h"
#include "AudioManager.h"

const std::string CONTINUE_BUTTON_ID = "2";
const std::string OPTIONS_BUTTON_ID = "4";
const std::string QUIT_BUTTON_ID = "6";

MenuPopup::MenuPopup(Vector2<float> onScreenPosition, Vector2<float> offScreenPosition, std::function<void()> onContinuePressedCallback, std::function<void()> onOptionsPressedCallback, std::function<void()> onQuitPressedCallback) : BasePopup(onScreenPosition, offScreenPosition, GUI_JSON_MENU_POPUP),
																																																										KeyListener(),
																																																										_currentSelectedButtonIndex(0),
																																																										_onContinuePressedCallback(onContinuePressedCallback),
																																																										_onOptionsPressedCallback(onOptionsPressedCallback),
																																																										_onQuitPressedCallback(onQuitPressedCallback),
																																																										_directionKeyPressed(false)
{
	_continueButton = GuiManager::Get()->getWidgetWithID(CONTINUE_BUTTON_ID, _popupWidget);
	_optionsButton = GuiManager::Get()->getWidgetWithID(OPTIONS_BUTTON_ID, _popupWidget);
	_quitButton = GuiManager::Get()->getWidgetWithID(QUIT_BUTTON_ID, _popupWidget);
}

MenuPopup::~MenuPopup()
{
}

void MenuPopup::showPopup()
{
	BasePopup::showPopup();

	_currentSelectedButtonIndex = 0;
	static_cast<ButtonGuiWidget*>(_buttons[_currentSelectedButtonIndex])->onSelected();

	_directionKeyPressed = false;
}

void MenuPopup::onKeyPressed(EventData *eventData)
{
	KeyPressedEventData *keyPressedEventData = dynamic_cast<KeyPressedEventData*>(eventData);
	if(keyPressedEventData != nullptr)
	{
		switch(keyPressedEventData->getKeycode())
		{
			case sf::Keyboard::X:
				dynamic_cast<ButtonGuiWidget*>(_buttons[_currentSelectedButtonIndex])->onPressed();
				break;
			case sf::Keyboard::Up:
			case sf::Keyboard::Down:
				_directionKeyPressed = true;
				break;
		}
	}
}

void MenuPopup::onKeyReleased(EventData *eventData)
{
	KeyReleasedEventData *keyReleasedEventData = dynamic_cast<KeyReleasedEventData*>(eventData);
	if(keyReleasedEventData != nullptr)
	{
		switch(keyReleasedEventData->getKeycode())
		{
			case sf::Keyboard::X:
				if(_buttons[_currentSelectedButtonIndex] == _continueButton)
				{
					_onContinuePressedCallback();
				}
				else if(_buttons[_currentSelectedButtonIndex] == _optionsButton)
				{
					_onOptionsPressedCallback();
				}
				else if(_buttons[_currentSelectedButtonIndex] == _quitButton)
				{
					_onQuitPressedCallback();
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