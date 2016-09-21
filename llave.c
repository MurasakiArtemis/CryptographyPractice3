#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generateKey(char *filename, int n);

int main()
{
generateKey("Hola.txt", 66);
}

void generateKey(char *filename, int n)
{
char *aux, *key, *iKey, aux2;
aux=(char *)calloc(n, sizeof(char) );
key=(char *)calloc(n, sizeof(char) );
iKey=(char *)calloc(n, sizeof(char) );
int i, count=0, n2=n;
srand( time(NULL) );

	for ( i=0; i<n; i++ )
	{
	aux[i]=i+1;	
	}

	for ( i=0; i<n2; i++ )
	{
	printf("%d ", aux[i]);
	}

	printf("\n\n");

	while ( n>0 )
	{
	aux2=rand()%n2;

		if ( aux[aux2]!=0 )
		{
		key[count] = aux[aux2];
		iKey[ key[count]-1 ] = count+1;
		aux[aux2] = 0;
		count++;
		n--;
		}
	}

	for ( i=0; i<n2; i++ )
	{
	printf("%d ", key[i]);
	}

	printf("\n\n");

	for ( i=0; i<n2; i++ )
	{
	printf("%d ", iKey[i]);	
	}


FILE *f;
f=fopen( filename, "w+");

	for (i=0; i<n2; i++)
	{
	fprintf(f, "%c", key[i] );
	}

	for (i=0; i<n2; i++)
	{
	fprintf(f, "%c", iKey[i] );
	}

fclose(f);
free(aux);
free(key);
free(iKey);
}
