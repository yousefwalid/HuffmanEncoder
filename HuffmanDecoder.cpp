#include <map>
#include <string>
#include <iostream>
class HuffmanDecoder
{
private:
	std::string decodedStr = "";

public:
	HuffmanDecoder(std::map<char, std::string> codeDic, std::string encodedStr)
	{
		// 1) Inverse the dictionary

		std::map<std::string, char> codeDicInv;

		for (std::map<char, std::string>::iterator i = codeDic.begin(); i != codeDic.end(); ++i)
			codeDicInv[i->second] = i->first;

		// 2) Search for the value and add it or the decoded string

		char decodedLtr = 0;
		std::string keySearch = "";
		for (int i = 0; i < encodedStr.size(); i++)
		{
			keySearch += encodedStr[i];

			if (codeDicInv.count(keySearch))
			{
				if (codeDicInv[keySearch] == 3)
					break;
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