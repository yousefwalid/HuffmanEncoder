#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
class FileManager
{
public:
	std::map<char, int> readASCIIFile(const char *inputFile)
	{
		std::ifstream inpStream;
		inpStream.open(inputFile);

		if (!inpStream)
		{
			exit(1);
		}

		char c;
		std::map<char, int> frequency;

		while (inpStream >> c)
			frequency[c]++;

		inpStream.close();

		if (frequency.size() == 0)
		{
			std::cout << "Input file is empty!" << std::endl;
			exit(1);
		}
		return frequency;
	}

	void encodeASCIIFile(const char *inputFile, std::map<char, std::string> codes, const char *outputFile)
	{
		std::ifstream inpStream;
		inpStream.open(inputFile);
		if (!inpStream)
			exit(1);

		std::ofstream outStream;
		outStream.open(outputFile);
		if (!outStream)
			exit(1);

		char c;
		while (inpStream >> c)
			outStream << codes[c];

		inpStream.close();
		outStream.close();
	}

	void decodeFile(std::string decodedStr , const char *decodedFile)
	{
		std::ofstream file(decodedFile);
		file << decodedStr;
	}

	std::string readEncodedFile(const char *encodedFile)
	{
		std::ifstream inpStream;
		inpStream.open(encodedFile);

		if (!encodedFile)
		{
			exit(1);
		}

		std::stringstream strStream;
		strStream << inpStream.rdbuf();
		std::string str = strStream.str(); 

		inpStream.close();

		return str;
	}
};