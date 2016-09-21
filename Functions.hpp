#ifndef FUNCTIONS_HPP

#define FUNCTIONS_HPP

#include <string>
#include <fstream>

using std::string;
using std::ofstream;
using std::ifstream;

void generateKey(const string& filename, const int permutation_size);
void ECB(ifstream& fIn, ofstream& fOut, const char* key, const int block_size);
void CBC(ifstream& fIn, ofstream& fOut, const char* key, const int block_size, bool encrypt);
void XOR(char* argument1, char* argument2, char* result, int array_size);
void permute(char* origin, char* result, const char* key, const int block_size);

#endif
