#include "StringHelper.h"
#include <sstream>
#include <fstream>
#include <codecvt>
#include <iostream>

std::wstring StringHelper::loadFromFile(const std::string &filename)
{
	std::wstring returnString = L"";
	std::wstring line;

	std::wifstream openfile(filename);
    if(openfile.is_open())
    {
        while(!openfile.eof())
        {
            openfile >> line;
			returnString += line;
			returnString += L'\n';
        }
    }

	return returnString;
}

void StringHelper::saveToFile(const std::string &filename, std::string stringToSave)
{
	std::ofstream openfile;
	openfile.open(filename);
	openfile << stringToSave;
	openfile.close();
}

std::vector<std::string> &StringHelper::split(const std::string &string, char delimiter, std::vector<std::string> &elements)
{
    std::stringstream stringStream(string);
    std::string item;
    while(std::getline(stringStream, item, delimiter))
	{
        elements.push_back(item);
    }
    return elements;
}

std::vector<std::string> StringHelper::split(const std::string &string, char delim)
{
    std::vector<std::string> elements;
    split(string, delim, elements);
    return elements;
}

std::vector<int> &StringHelper::convertVectorOfStringsToVectorOfInts(std::vector<std::string> &strings, std::vector<int> &numbers)
{
	std::vector<std::string>::iterator stringsIterator, stringsEnd;
	stringsEnd = strings.end();
	for(stringsIterator = strings.begin(); stringsIterator != stringsEnd; ++ stringsIterator)
	{
		numbers.push_back(std::atof((*stringsIterator).c_str()));
	}
	return numbers;
}

std::vector<int> StringHelper::convertVectorOfStringsToVectorOfInts(std::vector<std::string> &strings)
{
	std::vector<int> numbers;
	convertVectorOfStringsToVectorOfInts(strings, numbers);
	return numbers;
}

std::vector<unsigned int> &StringHelper::convertVectorOfStringsToVectorOfUnsignedInts(std::vector<std::string> &strings, std::vector<unsigned int> &numbers)
{
	std::vector<std::string>::iterator stringsIterator, stringsEnd;
	stringsEnd = strings.end();
	for(stringsIterator = strings.begin(); stringsIterator != stringsEnd; ++ stringsIterator)
	{
		numbers.push_back(std::atof((*stringsIterator).c_str()));
	}
	return numbers;
}

std::vector<unsigned int> StringHelper::convertVectorOfStringsToVectorOfUnsignedInts(std::vector<std::string> &strings)
{
	std::vector<unsigned int> numbers;
	convertVectorOfStringsToVectorOfUnsignedInts(strings, numbers);
	return numbers;
}

std::vector<double> &StringHelper::convertVectorOfStringsToVectorOfDoubles(std::vector<std::string> &strings, std::vector<double> &numbers)
{
	std::vector<std::string>::iterator stringsIterator, stringsEnd;
	stringsEnd = strings.end();
	for(stringsIterator = strings.begin(); stringsIterator != stringsEnd; ++ stringsIterator)
	{
		numbers.push_back(std::atof((*stringsIterator).c_str()));
	}
	return numbers;
}

std::vector<double> StringHelper::convertVectorOfStringsToVectorOfDoubles(std::vector<std::string> &strings)
{
	std::vector<double> numbers;
	convertVectorOfStringsToVectorOfDoubles(strings, numbers);
	return numbers;
}

std::wstring StringHelper::stringToWideString(const std::string& str)
{
    typedef std::codecvt_utf8<wchar_t> convert_typeX;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.from_bytes(str);
}

std::string StringHelper::wideStringToString(const std::wstring& wstr)
{
    typedef std::codecvt_utf8<wchar_t> convert_typeX;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}

std::string StringHelper::frontPadString(unsigned int destinationLength, char paddingChar, std::string stringToPad)
{
	int numPaddedChars = destinationLength - stringToPad.length();
	if(numPaddedChars > 0)
	{
		return std::string(numPaddedChars, paddingChar).append(stringToPad);
	}

	return stringToPad;
}