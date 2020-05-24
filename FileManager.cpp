#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include "BitBuffer.cpp"

class FileManager
{
public:
	std::unordered_map<char, int> readASCIIFile(const char *inputFile)
	{
		std::ifstream inpStream;
		inpStream.open(inputFile, std::ios::binary);

		if (!inpStream)
			exit(1);

		std::string line;
		std::unordered_map<char, int> frequency;

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

	void encodeASCIIFile(const char *inputFile, std::unordered_map<char, std::string> codes, const char *outputFile, const int &extraBits)
	{
		BitBuffer bitBuff;

		std::ifstream inpStream(inputFile, std::ios::binary);
		if (!inpStream)
			exit(1);

		std::ofstream outStream(outputFile, std::ios::binary);
		if (!outStream)
			exit(1);

		for (int i = 0; i < 3; i++)
		{
			bitBuff.push(((extraBits >> (2 - i)) & 1) + '0');
		}

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

		if (bitBuff.hasByte()) // if it contains more than 1 byte, pop twice
			outStream << bitBuff.pop();

		outStream << bitBuff.pop(); // if it contains less than a byte, pop once

		inpStream.close();
		outStream.close();
	}

	void decodeFile(std::string decodedStr, const char *decodedFile)
	{
		std::ofstream file(decodedFile, std::ios::binary);
		file << decodedStr;
	}

	std::string readEncodedFile(const char *encodedFile)
	{
		std::string str = "";

		std::ifstream inpStream(encodedFile, std::ios::binary);
		if (!inpStream)
			exit(1);

		bool firstLine = 1;
		char c;

		int paddingLength = 0;
		int paddingNum = 3;
		while (inpStream.get(c))
		{
			for (int i = 7; i >= 0; i--)
			{
				if (paddingNum)
				{
					paddingLength <<= 1;
					paddingLength += ((c >> i) & 1);
					paddingNum--;
					continue;
				}

				if (((c >> i) & 1))
					str += '1';
				else
					str += '0';
			}
		}

		str.erase(str.end() - paddingLength, str.end());

		inpStream.close();
		return str;
	}
};