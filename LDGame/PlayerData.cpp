#include "PlayerData.h"
#include "PlayerDataConsts.h"
#include "Application.h"
#include "StringHelper.h"

PlayerData* PlayerData::_instance = nullptr;

PlayerData::PlayerData() : PLAYER_SAVE_DATA_PATH("../SaveData.dat")
{
}

PlayerData::~PlayerData()
{
}

PlayerData *PlayerData::Get()
{
	if(_instance == nullptr)
	{
		_instance = new PlayerData();
	}

	return _instance;
}

void PlayerData::saveExternal()
{
	JSONObject jsonObject;

	//save the version
	jsonObject[VERSION] = new JSONValue(StringHelper::stringToWideString(GAME_VERSION));

	//save the bank key value pairs
	JSONArray jsonArray;
	std::map<std::string, double>::iterator statesIterator, statesEnd;
	for(statesIterator = _bank.begin(), statesEnd = _bank.end(); statesIterator != statesEnd; ++ statesIterator)
	{
		JSONObject keyValuePair;
		keyValuePair[KEY] = new JSONValue(StringHelper::stringToWideString((*statesIterator).first));
		keyValuePair[VALUE] = new JSONValue((*statesIterator).second);
		jsonArray.push_back(new JSONValue(keyValuePair));
	}
	jsonObject[BANK] = new JSONValue(jsonArray);

	//save the json save data
	StringHelper::saveToFile(PLAYER_SAVE_DATA_PATH, StringHelper::wideStringToString(JSON::Stringify(new JSONValue(jsonObject))));
}

void PlayerData::loadExternal()
{
	std::wstring jsonString = StringHelper::loadFromFile(PLAYER_SAVE_DATA_PATH);
	if(jsonString != L"")
	{
		JSONObject jsonObject = JSON::Parse(jsonString.c_str())->AsObject();

		//rebuild bank from save data json
		JSONArray bankJSONArray = jsonObject[BANK]->AsArray();
		JSONArray::iterator bankJSONArrayIterator, bankJSONArrayEnd;
		bankJSONArrayEnd = bankJSONArray.end();
		for(bankJSONArrayIterator = bankJSONArray.begin(); bankJSONArrayIterator != bankJSONArrayEnd; ++ bankJSONArrayIterator)
		{
			JSONObject keyValuePair = (*bankJSONArrayIterator)->AsObject();
			std::string key = StringHelper::wideStringToString(keyValuePair[KEY]->AsString());
			double value = keyValuePair[VALUE]->AsNumber();
			_bank[key] = value;
		}
	}
}

void PlayerData::setElement(std::string key, double value)
{
	_bank[key] = value;
}

double PlayerData::getElement(std::string key)
{
	return _bank[key];
}

bool PlayerData::hasElement(std::string key)
{
	std::map<std::string, double>::iterator bankIterator = _bank.find(key);
	return bankIterator != _bank.end();
}