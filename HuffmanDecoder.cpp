#include <map>
#include <string>

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

		std::string decodedLtr = "";
		std::string keySearch = "";
		for (int i = 0; i < encodedStr.size(); i++)
		{
			keySearch += encodedStr[i];
			decodedLtr = codeDicInv[keySearch];

			if (decodedLtr[0] != 0)
			{
				decodedStr.append(decodedLtr);
				keySearch = "";
				decodedLtr = "";
			}
		}
	}
	std::string getDecodedString()
	{
		return decodedStr;
	}
};