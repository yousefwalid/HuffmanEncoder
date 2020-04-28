#include "AppManager.cpp"
#include <iostream>
#include <string> 

int main()
{
	std::cout << "Enter the input file name without extension\n";
	std::string fileName;
	std::cin >> fileName;

	AppManager app;
	//app.run(fileName, "bin_" + fileName, fileName + ".out");
	app.run((fileName+".in").c_str(), (fileName+".bin").c_str(), (fileName+".out").c_str());
}