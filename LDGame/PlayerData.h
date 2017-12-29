#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H

#include <map>
#include <string>

#include "JSON.h"

class PlayerData
{
	public:
		static PlayerData *Get();
		virtual ~PlayerData();
		void saveExternal();
		void loadExternal();
		void setElement(std::string key, double value);
		double getElement(std::string key);
		bool hasElement(std::string key);
	private:
		PlayerData();
		static PlayerData *_instance;
		const std::string PLAYER_SAVE_DATA_PATH;
		std::map<std::string, double> _bank;
};

#endif