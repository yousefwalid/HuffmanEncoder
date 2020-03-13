#include "FileManager.cpp"
#include "HuffmanEncoder.cpp"
#include <map>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class AppManager
{
private:
	FileManager fileMan;

public:
	AppManager()
	{
	}

	void run(const char *inputFile, const char *outputFile)
	{
		// Get frequencies of characters from file

		std::map<char, int> frequency = fileMan.readASCIIFile(inputFile);

		// Get character codes

		HuffmanEncoder Encoder(frequency);
		std::map<char, std::string> codes = Encoder.getCodes();

		// Print the codes to console

		for (auto &x : codes)
		{
			std::cout << x.first << ":" << x.second << std::endl;
		}

		// Encode the file

		fileMan.encodeASCIIFile(inputFile, codes, outputFile);

		// Calculate statistics

		calculateStatisticsASCII(inputFile, outputFile);
	}

	void calculateStatisticsASCII(const char *inputFile, const char *outputFile)
	{
		std::ifstream inputStream;
		char dummy;

		inputStream.open(inputFile);
		int inpCharNum = 0;
		while (inputStream >> dummy)
			inpCharNum++;

		inputStream.close();

		inputStream.open(outputFile);
		int outBitsNum = 0;
		while (inputStream >> dummy)
			outBitsNum++;

		inputStream.close();

		std::cout << "Size before encoding: " << inpCharNum << " byte(s)\n"
				  << "Size after encoding: ~" << outBitsNum / 8 + 1 << " byte(s)\n";
	}

	~AppManager()
	{
	}
};