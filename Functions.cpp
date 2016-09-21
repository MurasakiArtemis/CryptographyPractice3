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

void ECB(ifstream& fIn, ofstream& fOut, const char* key, const int block_size)
{
    fIn.seekg(0, ios::end);
    int origin_size = int(fIn.tellg()) - 1;
    fIn.seekg(0, ios::beg);   
    char* origin = new char[block_size];
    char* result = new char[block_size];
    for(int i = 0; i < origin_size; i += block_size)
    {
	fIn.read(origin, block_size);
	if(fIn.eof())
	    for(int j = fIn.gcount()-1; j < block_size; j++)
		origin[j] = 'A';
	permute(origin, result, key, block_size);
	fOut.write(result, block_size);
    }
    delete[] origin;
    delete[] result;
}

void CBC(ifstream& fIn, ofstream& fOut, const char* key, const int block_size, bool encrypt)
{
    fIn.seekg(0, ios::end);
    int origin_size = int(fIn.tellg()) - 1;
    fIn.seekg(0, ios::beg);   
    char* origin = new char[block_size];
    char* result = new char[block_size];
    //Específico para CBC
    srand(time(nullptr));	      // 
    char* aux = new char[block_size]; // 
    if(encrypt)			      // 
    {
	for(int i = 0; i < block_size; i++) // 
	    result[i] = i + 'A';	    //rand()%block_size;
	fOut.write(result, block_size);	    // 
    }
    else			// 
	fIn.read(aux, block_size); // 
    origin_size -= block_size;	   //
    //Específico para CBC
    for(int i = 0; i < origin_size; i += block_size)
    {
	fIn.read(origin, block_size);
	if(fIn.eof())
	    for(int j = fIn.gcount()-1; j < block_size; j++)
		origin[j] = 'A';
	//Específico para CBC
	if(encrypt)		// 
	{			// 
	    XOR(origin, result, aux, block_size); // 
	    permute(aux, result, key, block_size); // 
	}
	else			// 
	{
	    permute(origin, result, key, block_size); // 
	    XOR(result, aux, result, block_size);     // 
	    memcpy(aux, origin, block_size);	      // 
	}
	//Específico para CBC
	fOut.write(result, block_size);
    }
    delete[] origin;
    delete[] result;
    delete[] aux;//
}

void XOR(char* argument1, char* argument2, char* result, int array_size)
{
    for(int i = 0; i < array_size; i++)
	result[i] = ((argument1[i] - 'A') ^ (argument2[i] - 'A'))%('A' - 'Z') + 'A';
}

void permute(char* origin, char* result, const char* key, const int block_size)
{
    for(int j = 0; j < block_size; j++)
	result[int(key[j])] = origin[j];
}
