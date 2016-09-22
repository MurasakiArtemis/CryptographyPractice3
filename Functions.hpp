#ifndef FUNCTIONS_HPP

#define FUNCTIONS_HPP

#include <string>
#include <fstream>

using std::string;
using std::ofstream;
using std::ifstream;

void generateKey(const string& filename, const int permutation_size);
void Process_Request(ifstream& fIn, ofstream& fOut, const char* key, const int block_size, const bool encrypt, const string& operation_mode);
void CBC(const char* origin, char* aux, char* result, const char* key, const int block_size, bool encrypt);
void CTR(const char* origin, char* IV, char* result, const char* key, const int block_size, bool encrypt);
void add(char* array, int number, int array_size);
void XOR(const char* argument1, const char* argument2, char* result, int array_size);
void permute(const char* origin, char* result, const char* key, const int block_size);

#endif
