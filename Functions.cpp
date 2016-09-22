#include <string>
#include <fstream>
#include <cstring>
#include "Functions.hpp"

using std::string;
using std::ofstream;
using std::ifstream;
using std::ios;

void generateKey(const string& filename, const int permutation_size)
{
    char *aux, *key, *inverse_key;
    aux = new char[permutation_size];
    key = new char[permutation_size];
    inverse_key = new char[permutation_size];
    srand(time(nullptr));
    for(int i = 0; i < permutation_size; i++)
	aux[i] = i;
    for(int count = 0; count < permutation_size;)
    {
	short aux2 = rand()%permutation_size;
	if (aux[aux2] != -1)
	{
	    key[count] = aux[aux2];
	    inverse_key[int(aux[aux2])] = count;
	    aux[aux2] = -1;
	    count++;
	}
    }
    ofstream fOut(filename, ios::binary | ios::trunc);
    fOut.write(key, permutation_size);
    fOut.write(inverse_key, permutation_size);
    fOut.close();
    delete[] aux;
    delete[] key;
    delete[] inverse_key;
}

void Process_Request(ifstream& fIn, ofstream& fOut, const char* key, const int block_size, const bool encrypt, const string& operation_mode)
{
    srand(time(nullptr));
    fIn.seekg(0, ios::end);
    int origin_size = int(fIn.tellg()) - 1;
    fIn.seekg(0, ios::beg);   
    char* origin = new char[block_size];
    char* result = new char[block_size];
    char* aux = nullptr;
    char* IV = nullptr;
    if(operation_mode != "ECB")
    {
	aux = new char[block_size];
	IV = new char[block_size];
	if(encrypt)
	{
	    for(int i = 0; i < block_size; i++)
	        IV[i] = i + 'A';
	    fOut.write(IV, block_size);
	    if(operation_mode == "CBC")
		memcpy(result, IV, block_size);
	}
	else
	{
	    fIn.read(IV, block_size);
	    origin_size -= block_size;
	    if(operation_mode == "CBC")
		memcpy(aux, IV, block_size);
	}
    }
    for(int i = 0; i < origin_size; i += block_size)
    {
	fIn.read(origin, block_size);
	if(fIn.eof())
	    for(int j = fIn.gcount()-1; j < block_size; j++)
		origin[j] = 'A';
	if(operation_mode == "ECB")
	    permute(origin, result, key, block_size);
	else if(operation_mode == "CBC")
	    CBC(origin, aux, result, key, block_size, encrypt);
	else if(operation_mode == "CTR")
	    CTR(origin, IV, result, key, block_size, encrypt);
	fOut.write(result, block_size);
    }
    delete[] origin;
    delete[] result;
    if(aux != nullptr)
    {
	delete[] aux;
	delete[] IV;
    }
}

void CBC(const char* origin, char* aux, char* result, const char* key, const int block_size, bool encrypt)
{
    if(encrypt)
    {
	XOR(origin, result, aux, block_size);
	permute(aux, result, key, block_size);
    }
    else
    {
	permute(origin, result, key, block_size);
	XOR(result, aux, result, block_size);
	memcpy(aux, origin, block_size);
    }
}

void CTR(const char* origin, char* IV, char* result, const char* key, const int block_size, bool encrypt)
{
    permute(IV, result, key, block_size);
    XOR(result, origin, result, block_size);
    add(IV, 1, block_size);
}

void add(char* array, int number, int array_size)
{
    for(int i = array_size - 1; i >= 0; i++)
    {
	array[i] = (array[i] - 'A' + number)%26 + 'A';
	if(array[i] == 'A' && number != 0)
	    number = 1;
	else break;
    }
}

void XOR(const char* argument1, const char* argument2, char* result, int array_size)
{
    for(int i = 0; i < array_size; i++)
	result[i] = ((argument1[i] - 'A') ^ (argument2[i] - 'A'))%('Z' - 'A') + 'A';
}

void permute(const char* origin, char* result, const char* key, const int block_size)
{
    for(int j = 0; j < block_size; j++)
	result[int(key[j])] = origin[j];
}
