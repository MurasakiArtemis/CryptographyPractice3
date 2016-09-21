/*
  Eron Romero Argumedo
  Erwin Hernández García
*/

#include <iostream>
#include <fstream>
#include <string>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::string;

void generateKey(char *filename, const int n)
{
    char *aux, *key, *iKey;
    short aux2;
    aux = (char*)calloc(n, sizeof(char) );
    key = (char *)calloc(n, sizeof(char) );
    iKey = (char *)calloc(n, sizeof(char) );
    int count=0;
    srand( time(NULL) );

    for(int i=0; i<n; i++)
	aux[i]=i;
    while (count < n)
    {
	aux2 = rand()%n;
	if (aux[aux2] != -1)
	{
	    key[count] = aux[aux2];
	    iKey[key[count]] = count;
	    aux[aux2] = -1;
	    count++;
	}
    }
    FILE *f;
    f=fopen( filename, "w+");

    for (int i=0; i<n; i++)
	fprintf(f, "%c", key[i] );

    for (int i=0; i<n; i++)
	fprintf(f, "%c", iKey[i] );

    fclose(f);
    free(aux);
    free(key);
    free(iKey);
};


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
	int key_size = fileSize/2;
	char* key = new char[key_size];
	if(opcion == "-d")
	    fIn.seekg(key_size, ios::beg);
	fIn.read(key, key_size);
	fIn.close();
	fIn.open(argv[3], ios::binary);
	fIn.seekg(0, ios::end);
	fileSize = fIn.tellg();
	fIn.seekg(0, ios::beg);
	int origin_size = fileSize - 1;
	char* origin = new char[key_size];
	ofstream fOut(argv[4], ios::binary);
	char* result = new char[key_size];
	for(int i = 0; i < origin_size; i += key_size)
	{
	    fIn.read(origin, key_size);
	    if(fIn.eof())
		for(int j = fIn.gcount()-1; j < key_size; j++)
		    origin[j] = ' ';
	    for(int j = 0; j < key_size; j++)
		result[key[j]] = origin[j];
	    fOut.write(result, key_size);
	}
	delete[] key;
	delete[] origin;
	delete[] result;
    }
    else
    {
	cout << "Los modos de uso son: -k -e -d" << endl;
	return -1;
    }
    return 0;
}

