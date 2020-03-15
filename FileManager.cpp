#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include "BitBuffer.cpp"
using namespace std;

class FileManager
{
public:
	std::map<char, int> readASCIIFile(const char *inputFile)
	{
		std::ifstream inpStream;
		inpStream.open(inputFile);

		if (!inpStream)
			exit(1);

		std::string line;
		std::map<char, int> frequency;

		bool firstLine = 1;

		while (std::getline(inpStream, line))
		{
			if (firstLine)
				firstLine = 0;
			else
				frequency['\n']++;

			for (auto c : line)
				frequency[c]++;
		}

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
		BitBuffer bitBuff;

		std::ifstream inpStream(inputFile);
		if (!inpStream)
			exit(1);

		std::ofstream outStream(outputFile);
		if (!outStream)
			exit(1);

		char c;
		while (inpStream.get(c))
		{
			bitBuff.push(codes[c]);

			while (bitBuff.hasByte())
			{
				char outByte = bitBuff.pop();
				outStream << outByte;
			}
		}

		bitBuff.push(codes[3]);

		if (bitBuff.hasByte()) // if it contains more than 1 byte, pop twice
			outStream << bitBuff.pop();

		outStream << bitBuff.pop(); // if it contains less than a byte, pop once

		inpStream.close();
		outStream.close();
	}

	void decodeFile(std::string decodedStr, const char *decodedFile)
	{
		std::ofstream file(decodedFile);
		file << decodedStr;
	}

	std::string readEncodedFile(const char *encodedFile)
	{
		std::string str = "";

		std::ifstream inpStream(encodedFile);
		if (!inpStream)
			exit(1);

		bool firstLine = 1;
		char c;

		while (inpStream.get(c))
		{
			for (int i = 7; i >= 0; i--)
			{
				if (((c >> i) & 1))
					str += '1';
				else
					str += '0';
			}
		}

		inpStream.close();
		return str;
	}
};