#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <vector>
#include <string>
#include <map>
#include <SFML\Audio.hpp>

class AudioManager
{
	public:
		virtual ~AudioManager();
		static AudioManager* Get();
		void loadSound(std::string soundURL);
		void playSound(std::string soundURL);
		void playMusic(std::string musicURL);
		void stopMusic(std::string musicURL);
		void toggleSoundMute();
		void toggleMusicMute();
		bool isSoundMuted();
		bool isMusicMuted();
		sf::SoundBuffer getSound(std::string soundURL);
		sf::Music* getMusic(std::string musicURL);
	private:
		AudioManager();
		static AudioManager *_instance;
		std::map<std::string, sf::SoundBuffer> _soundURLsToSoundBuffer;
		std::map<std::string, sf::Music*> _musicURLsToMusic;
		std::vector<sf::Sound> _playingSounds;
		bool _soundMuted;
		bool _musicMuted;
};

#endif