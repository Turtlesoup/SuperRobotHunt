#include "OptionsPopup.h"
#include "EventManager.h"
#include "BaseGuiWidget.h"
#include "TextGuiWidget.h"
#include "ButtonGuiWidget.h"
#include "KeyPressedEventData.h"
#include "KeyReleasedEventData.h"
#include "GuiManager.h"
#include "Resources.h"
#include "AudioManager.h"

//gui widget ids
const std::string SOUND_BUTTON_ID = "2";
const std::string SOUND_BUTTON_TEXT_ID = "4";
const std::string MUSIC_BUTTON_ID = "6";
const std::string MUSIC_BUTTON_TEXT_ID = "7";
const std::string BACK_BUTTON_ID = "8";

//text strings
const std::string SOUND_ON_TEXT = "Sound : On";
const std::string SOUND_OFF_TEXT = "Sound : Off";
const std::string MUSIC_ON_TEXT = "Music : On";
const std::string MUSIC_OFF_TEXT = "Music : Off";

OptionsPopup::OptionsPopup(Vector2<float> onScreenPosition, Vector2<float> offScreenPosition, std::function<void()> onPopupClosedCallback) : BasePopup(onScreenPosition, offScreenPosition, GUI_JSON_OPTIONS_POPUP),
																																			 KeyListener(),
																																			 _onPopupClosedCallback(onPopupClosedCallback),
																																			 _currentSelectedButtonIndex(0),
																																			 _directionKeyPressed(false)
{
	_soundButton = GuiManager::Get()->getWidgetWithID(SOUND_BUTTON_ID, _popupWidget);
	_musicButton = GuiManager::Get()->getWidgetWithID(MUSIC_BUTTON_ID, _popupWidget);
	_backButton = GuiManager::Get()->getWidgetWithID(BACK_BUTTON_ID, _popupWidget);

	_soundButtonText = static_cast<TextGuiWidget*>(GuiManager::Get()->getWidgetWithID(SOUND_BUTTON_TEXT_ID, _popupWidget));
	_musicButtonText = static_cast<TextGuiWidget*>(GuiManager::Get()->getWidgetWithID(MUSIC_BUTTON_TEXT_ID, _popupWidget));
}

OptionsPopup::~OptionsPopup()
{
}

void OptionsPopup::showPopup()
{
	BasePopup::showPopup();

	_currentSelectedButtonIndex = 0;
	static_cast<ButtonGuiWidget*>(_buttons[_currentSelectedButtonIndex])->onSelected();

	_directionKeyPressed = false;

	//update the button text
	updateButtonText();
}

void OptionsPopup::onKeyPressed(EventData *eventData)
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

void OptionsPopup::onKeyReleased(EventData *eventData)
{
	KeyReleasedEventData *keyReleasedEventData = dynamic_cast<KeyReleasedEventData*>(eventData);
	if(keyReleasedEventData != nullptr)
	{
		switch(keyReleasedEventData->getKeycode())
		{
			case sf::Keyboard::X:

				if(_buttons[_currentSelectedButtonIndex] == _soundButton)
				{
					AudioManager::Get()->toggleSoundMute();
					updateButtonText();
				}
				else if(_buttons[_currentSelectedButtonIndex] == _musicButton)
				{
					AudioManager::Get()->toggleMusicMute();
					updateButtonText();
				}
				else if(_buttons[_currentSelectedButtonIndex] == _backButton)
				{
					disableListeners();
					hidePopup();
					_onPopupClosedCallback();
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

void OptionsPopup::updateButtonText()
{
	if(AudioManager::Get()->isSoundMuted())
	{
		_soundButtonText->setTextValue(SOUND_OFF_TEXT);
	}
	else
	{
		_soundButtonText->setTextValue(SOUND_ON_TEXT);
	}

	if(AudioManager::Get()->isMusicMuted())
	{
		_musicButtonText->setTextValue(MUSIC_OFF_TEXT);
	}
	else
	{
		_musicButtonText->setTextValue(MUSIC_ON_TEXT);
	}
}