#include "HuffmanDecoder.cpp"
#include "FileManager.cpp"
#include "HuffmanEncoder.cpp"
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

class AppManager
{
private:
	FileManager fileMan;

public:
	AppManager()
	{
	}

	void run(const char *inputFile, const char *outputFile, const char *decodedFile)
	{
		// Get frequencies of characters from file

		std::unordered_map<char, int> frequency = fileMan.readASCIIFile(inputFile);

		// Get character codes

		HuffmanEncoder Encoder(frequency);
		std::unordered_map<char, std::string> codes = Encoder.getCodes();

		// Print the codes to console

		for (auto &x : codes)
		{
			std::cout << x.first << ":" << x.second << std::endl;
		}

		// handle extra padding bits

		long long extraNumberOfBits = 0;

		for (auto &x : codes)
		{
			extraNumberOfBits = (extraNumberOfBits % 8 + (frequency[x.first] % 8 * x.second.length() % 8) % 8) % 8;
		}

		extraNumberOfBits = (extraNumberOfBits + 3) % 8;

		extraNumberOfBits = (8 - extraNumberOfBits) % 8;

		// Encode the file

		fileMan.encodeASCIIFile(inputFile, codes, outputFile, extraNumberOfBits);

		// Calculate statistics

		calculateStatisticsASCII(inputFile, outputFile);

		// Read Encoded File
		std::string encodedStr = fileMan.readEncodedFile(outputFile);

		// Get Decoded String
		HuffmanDecoder Decoder(codes, encodedStr);
		std::string decodedStr = Decoder.getDecodedString();

		// Output Decoded File
		fileMan.decodeFile(decodedStr, decodedFile);
	}

	void calculateStatisticsASCII(const char *inputFile, const char *outputFile)
	{
		FILE *file;
		file = fopen(inputFile, "r");
		fseek(file, 0, SEEK_END);
		int inputSize = ftell(file);
		fclose(file);

		file = fopen(outputFile, "r");
		fseek(file, 0, SEEK_END);
		int outputSize = ftell(file);
		fclose(file);

		std::cout << "Size before encoding: " << inputSize << " byte(s)\n"
							<< "Size after encoding: " << outputSize << " byte(s)\n"
							<< "Compression ratio = " << (double)(inputSize) / (double)(outputSize) << '\n';
	}

	~AppManager()
	{
	}
};