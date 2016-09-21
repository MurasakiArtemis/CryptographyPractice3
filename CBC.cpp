/*
  Eron Romero Argumedo
  Erwin Hernández García
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "Functions.hpp"

using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::string;

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
	cout << "Se debe especificar un modo de uso" << endl;
	return -1;
    }
    string opcion(argv[1]);
    if(opcion.size() != 2)
    {	
	cout << "El modo de uso consiste en un guión seguido de la letra del modo" << endl;
	return -1;
    }
    else if(opcion == "-k")
    {
	if(argc != 4)
	{
	    cout << "El modo de uso es: " << argv[0] << " " << argv[1] << " <nombre del archivo> <tamaño de la llave>" << endl;
	    return -1;
	}
	generateKey(argv[2], std::stoi(argv[3]));
    }
    else if(opcion == "-e" || opcion == "-d")
    {
	if(argc != 5)
	{
	    cout << "El modo de uso es: " << argv[0] << " " << argv[1] << " <llave>" << (opcion == "-e"?" <texto plano> <texto cifrado":"<texto cifrado> <texto plano>") << endl;
	    return -1;
	}
	ifstream fIn(argv[2], ios::binary);
	fIn.seekg(0, ios::end);
	int fileSize = fIn.tellg();
	fIn.seekg(0, ios::beg);
	int block_size = fileSize/2;
	char* key = new char[block_size];
	if(opcion == "-d")
	    fIn.seekg(block_size, ios::beg);
	fIn.read(key, block_size);
	fIn.close();
	fIn.open(argv[3], ios::binary);
	ofstream fOut(argv[4], ios::binary);
	ECB(fIn, fOut, key, block_size);
	fIn.close();
	fOut.close();
	delete[] key;
    }
    else
    {
	cout << "Los modos de uso son: -k -e -d" << endl;
	return -1;
    }
    return 0;
}

