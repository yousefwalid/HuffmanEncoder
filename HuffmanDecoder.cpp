#include <unordered_map>
#include <string>
#include <iostream>
class HuffmanDecoder
{
private:
	std::string decodedStr = "";

public:
	HuffmanDecoder(std::unordered_map<char, std::string> codeDic, std::string encodedStr)
	{
		// 1) Inverse the dictionary

		std::unordered_map<std::string, char> codeDicInv;

		for (std::unordered_map<char, std::string>::iterator i = codeDic.begin(); i != codeDic.end(); ++i)
			codeDicInv[i->second] = i->first;

		// 2) Search for the value and add it or the decoded string

		char decodedLtr = 0;
		std::string keySearch = "";
		for (int i = 0; i < encodedStr.size(); i++)
		{
			keySearch += encodedStr[i];

			if (codeDicInv.count(keySearch))
			{
				decodedStr += codeDicInv[keySearch];
				keySearch = "";
			}
		}
	}
	std::string getDecodedString()
	{
		return decodedStr;
	}
};