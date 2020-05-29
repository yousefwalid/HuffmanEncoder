#include "AppManager.cpp"
#include <iostream>
#include <string>

int main()
{
	std::cout << "Enter the input file name without extension\n";
	std::string fileName;
	std::cin >> fileName;

	AppManager app;
	app.run(("./bin/" + fileName + ".in").c_str(), ("./bin/" + fileName + ".bin").c_str(), ("./bin/" + fileName + ".out").c_str());
}