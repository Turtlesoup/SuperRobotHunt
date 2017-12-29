#ifndef STRING_HELPER_H
#define STRING_HELPER_H

#include <string>
#include <vector>

class StringHelper
{
	public:
		static std::wstring loadFromFile(const std::string &filename);
		static void saveToFile(const std::string &filename, std::string stringToSave);
		static std::vector<std::string> &split(const std::string &string, char delimiter, std::vector<std::string> &elements);
		static std::vector<std::string> split(const std::string &string, char delimiter);
		static std::vector<int> &convertVectorOfStringsToVectorOfInts(std::vector<std::string> &strings, std::vector<int> &numbers);
		static std::vector<int> convertVectorOfStringsToVectorOfInts(std::vector<std::string> &strings);
		static std::vector<unsigned int> &convertVectorOfStringsToVectorOfUnsignedInts(std::vector<std::string> &strings, std::vector<unsigned int> &numbers);
		static std::vector<unsigned int> convertVectorOfStringsToVectorOfUnsignedInts(std::vector<std::string> &strings);
		static std::vector<double> &convertVectorOfStringsToVectorOfDoubles(std::vector<std::string> &strings, std::vector<double> &numbers);
		static std::vector<double> convertVectorOfStringsToVectorOfDoubles(std::vector<std::string> &strings);
		static std::wstring stringToWideString(const std::string& str);
		static std::string wideStringToString(const std::wstring& wstr);
		static std::string frontPadString(unsigned int destinationLength, char paddingChar, std::string stringToPad);
};

#endif