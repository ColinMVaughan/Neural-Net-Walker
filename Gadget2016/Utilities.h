//Colin Vaughan, Noah Berman, Alfred Fernandez
//November 2016.

#pragma once
#include <string>
#include <vector>
#include <sstream>

//used to split strings based on delimitor character
void splitString(const std::string &s, char delim, std::vector<std::string> &elems);
bool is_file_exist(std::string);

//Used to extract neuron weights from a file
void GetWeights(std::string, std::vector<float>& w);
