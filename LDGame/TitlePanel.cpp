#include "TitlePanel.h"
#include "EventManager.h"
#include "BaseGuiWidget.h"
#include "ButtonGuiWidget.h"
#include "KeyPressedEventData.h"
#include "KeyReleasedEventData.h"
#include "GuiManager.h"
#include "Resources.h"
#include "AudioManager.h"
#include "Application.h"

//gui widget ids
const std::string PLAY_BUTTON_ID = "2";
const std::string OPTIONS_BUTTON_ID = "6";
const std::string QUIT_BUTTON_ID = "8";

TitlePanel::TitlePanel(Vector2<float> onScreenPosition, Vector2<float> offScreenPosition, std::function<void()> onPlayPressedCallback, std::function<void()> onOptionsPressedCallback) : BasePopup(onScreenPosition, offScreenPosition, GUI_JSON_TITLE_PANEL),
																																													     KeyListener(),
																																													     _currentSelectedButtonIndex(0),
																																													     _onPlayPressedCallback(onPlayPressedCallback),
																																													     _onOptionsPressedCallback(onOptionsPressedCallback),
																																													     _directionKeyPressed(false)
{
	_playButton = GuiManager::Get()->getWidgetWithID(PLAY_BUTTON_ID, _popupWidget);
	_optionsButton = GuiManager::Get()->getWidgetWithID(OPTIONS_BUTTON_ID, _popupWidget);
	_quitButton = GuiManager::Get()->getWidgetWithID(QUIT_BUTTON_ID, _popupWidget);
}

TitlePanel::~TitlePanel()
{
}

void TitlePanel::showPopup()
{
	BasePopup::showPopup();

	_currentSelectedButtonIndex = 0;
	static_cast<ButtonGuiWidget*>(_buttons[_currentSelectedButtonIndex])->onSelected();

	_directionKeyPressed = false;
}

void TitlePanel::onKeyPressed(EventData *eventData)
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

void TitlePanel::onKeyReleased(EventData *eventData)
{
	KeyReleasedEventData *keyReleasedEventData = dynamic_cast<KeyReleasedEventData*>(eventData);
	if(keyReleasedEventData != nullptr)
	{
		switch(keyReleasedEventData->getKeycode())
		{
			case sf::Keyboard::X:
				if(_buttons[_currentSelectedButtonIndex] == _playButton)
				{
					_onPlayPressedCallback();
				}
				else if(_buttons[_currentSelectedButtonIndex] == _optionsButton)
				{
					_onOptionsPressedCallback();
				}
				else if(_buttons[_currentSelectedButtonIndex] == _quitButton)
				{
					Application::exitGame();
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