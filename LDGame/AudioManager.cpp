#include "AudioManager.h"

AudioManager* AudioManager::_instance = nullptr;

AudioManager::AudioManager() : _soundMuted(false),
							   _musicMuted(false)
{
}

AudioManager::~AudioManager()
{
}

AudioManager* AudioManager::Get()
{
	if(_instance == nullptr)
	{
		_instance = new AudioManager();
	}

	return _instance;
}

void AudioManager::loadSound(std::string soundURL)
{
	if(_soundURLsToSoundBuffer.find(soundURL) == _soundURLsToSoundBuffer.end())
	{
		_soundURLsToSoundBuffer[soundURL] = sf::SoundBuffer();
		if(!_soundURLsToSoundBuffer[soundURL].loadFromFile(soundURL))
		{
			//load error
			throw std::exception("cannot load audio file");
		}
	}
}

void AudioManager::playSound(std::string soundURL)
{
	//removed sounds which have stopped
	for(std::vector<sf::Sound>::iterator soundIter = _playingSounds.begin(); soundIter != _playingSounds.end();)
	{
		if(soundIter->getStatus() == sf::SoundSource::Status::Stopped)
		{
			soundIter = _playingSounds.erase(soundIter);
		}
		else
		{
			++soundIter;
		}
	}

	//get the sound buffer for the given url
	sf::SoundBuffer& soundBuffer = _soundURLsToSoundBuffer[soundURL];

	//create the sound to reference the sound buffer
	_playingSounds.push_back(sf::Sound(soundBuffer));

	//play the sound
	_playingSounds[_playingSounds.size()-1].play();

	if(_soundMuted)
	{
		_playingSounds[_playingSounds.size()-1].setVolume(0.0f);
	}
}

void AudioManager::playMusic(std::string musicURL)
{
	sf::Music *music = new sf::Music();
	music->openFromFile(musicURL);
	//add the music to the list of music instances
	_musicURLsToMusic[musicURL] = music;
	//play the music
	music->play();

	if(_musicMuted)
	{
		music->setVolume(0.0f);
	}
}

void AudioManager::stopMusic(std::string musicURL)
{
	sf::Music *music = _musicURLsToMusic[musicURL];
	music->stop();
	_musicURLsToMusic.erase(musicURL);
	delete music;
}

void AudioManager::toggleSoundMute()
{
	_soundMuted = !_soundMuted;

	unsigned int numSoundsPlaying = _playingSounds.size();
	unsigned int soundIndex;

	if(_soundMuted)
	{
		for(soundIndex = 0; soundIndex < numSoundsPlaying; ++ soundIndex)
		{
			_playingSounds[soundIndex].setVolume(0.0f);
		}
	}
	else
	{
		for(soundIndex = 0; soundIndex < numSoundsPlaying; ++ soundIndex)
		{
			_playingSounds[soundIndex].setVolume(100.0f);
		}
	}
}

void AudioManager::toggleMusicMute()
{
	_musicMuted = !_musicMuted;

	std::map<std::string, sf::Music*>::iterator musicIter, musicEnd;
	musicEnd = _musicURLsToMusic.end();
	if(_musicMuted)
	{
		for(musicIter = _musicURLsToMusic.begin(); musicIter != musicEnd; ++musicIter)
		{
			(*musicIter).second->setVolume(0.0f);
		}
	}
	else
	{
		for(musicIter = _musicURLsToMusic.begin(); musicIter != musicEnd; ++musicIter)
		{
			(*musicIter).second->setVolume(100.0f);
		}
	}
}

bool AudioManager::isSoundMuted()
{
	return _soundMuted;
}

bool AudioManager::isMusicMuted()
{
	return _musicMuted;
}

sf::SoundBuffer AudioManager::getSound(std::string soundURL)
{
	return _soundURLsToSoundBuffer[soundURL];
}

sf::Music* AudioManager::getMusic(std::string musicURL)
{
	return _musicURLsToMusic[musicURL];
}