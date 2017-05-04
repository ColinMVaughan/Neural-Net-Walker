//Colin Vaughan, Noah Berman, Alfred Fernandez
//November 2016.
#include "Utilities.h"
#include <fstream>

//Splits the scring into different elements based on a user defined delimitor.
//Pushes string segments into 'elements' vector.
void splitString(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss;
	ss.str(s);
	std::string item;

	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

//Checks if a file exists.
bool is_file_exist(std::string fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}

//Gets the weights for a neuron when passed a sting of numbers
void GetWeights(std::string str, std::vector<float>& w)
{
	std::vector<std::string> vec;
	splitString(str, ',', vec);	//split string into string vector

	for(int i=1; i<vec.size(); i++)	//start at 1 to ignore N character
	{
		w.push_back(std::stof(vec[i]));	//convert string to float
	}

	return;
}