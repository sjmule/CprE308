#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

#define DEBUG 0

//Define global variables to be used by the threads
int** a;
int** b;
int** out;
int N;
FILE* OUT;
FILE* A;
FILE* B;

//The function for the pthreads to operate in, does the multiplication of the arrays and puts the outputs in the output array
void multiplication(void* args)
{
	int line = (int) args;
	int i = 0;
	int j = 0;
	int tmp = 0;
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			tmp += a[line][j] * b[j][i];
		}
		out[line][i] = tmp;
		tmp = 0;
	}
}

//atoi(char* s); converts ASSCI to int, itoa for reverse
//Only get at most 1024 threads
//There are 4096 elements between the two matrices
/* 
 * 	[ 5   4	]  	[ 5   1	]	[ 5*5+4*2  5*1+4*9 ]	[ 33  41 ]
 * A = 	[ 	]  B =	[	]  C =	[ 			   ] =	[ 		 ]
 * 	[ 6   2	]  	[ 2   9	]	[ 6*5+2*1  6*1+2*9 ]	[ 34  24 ]
 */
int main(int args, char** argv)
{
	//make sure that the appropriate number of files are being passed in
	if(args != 4)
	{
		printf("Must provide two .dat files to open and multiply together as well as an OUTput .dat file\n");
		exit(-1);
	}
	
	N = 0;
	int t = NULL;
	char* size = malloc(10 * sizeof(char));

	//Try to open the first file, exit if if fails
	char* input = argv[1];
	A = fopen(input, "r");

	if(A == 0)
	{
		perror("Cannot open first file");
		exit(-1);
	}
	
	//Try to open the second file, exit if it fails
	input = argv[2];
	B = fopen(input, "r");
	
	if(B == 0)
	{
		perror("Cannot open second file");
		exit(-1);
	}
	
	//Open the third file for writing
	input = argv[3];
	OUT = fopen(input, "w");
	
	//Get the first line of file A to determine the size of the matrix
	getline(&size, &t, A);
	
	//Get the size of the matrix from the line and into an integer
	int i = 0;
	char sizeN[6];
	for(i; !(size[i] >= '0' && size[i] <= '9') && i < strlen(size); i++);
	strcpy(sizeN, size+i);
	
	N = atoi(sizeN);
	
	//Allocate memory to our two dimensional arrays which will hold the data from the two input arrays and the result of the multiplication before it is written to the output file
	a = malloc(N * sizeof(int *));
	b = malloc(N * sizeof(int *));
	out = malloc(N * sizeof(int *));
	
	for(i = 0; i < N; i++)
	{
		a[i] = malloc(N * sizeof(int *));
	}
	for(i = 0; i < N; i++)
	{
		b[i] = malloc(N * sizeof(int *));
	}
	for(i = 0; i < N; i++)
	{
		out[i] = malloc(N * sizeof(int *));
	}
	
	//Allocate memory to char arrays to read lines from the files
	char* Aline = malloc((N*2) * sizeof(char));
	char* Bline = malloc((N*2) * sizeof(char));
	getline(&Bline, &t, B);
	
	//Put the data from the files into the global arrays
	int j = 0;
	int k = 0;
	int l = 0;
	char numBuff[3];
	int number = 0;
	for(i=0; i<N; i++)
	{
		getline(&Aline, &t, A);
		for(j=0; j<strlen(Aline); j++)
		{
			if(!(Aline[j] >= '0' && Aline[j] <= '9'))
			{
				numBuff[k] = '\0';
				number = atoi(numBuff);
				a[i][l++] = number;
				k = 0;
			}
			else
			{
				numBuff[k++] = Aline[j];
			}
		}
		l=0;
	}
	
	//Populate array the array for file B
	j = 0;
	k = 0;
	l = 0;
	for(i=0; i<N; i++)
	{
		getline(&Bline, &t, B);
		for(j=0; j<strlen(Bline); j++)
		{
			if(!(Bline[j] >= '0' && Bline[j] <= '9'))
			{
				numBuff[k] = '\0';
				number = atoi(numBuff);
				b[i][l++] = number;
				k = 0;
			}
			else
			{
				numBuff[k++] = Bline[j];
			}
		}
		l = 0;
	}
	
	//Create some threads, check to make sure each one was created
	int err = 0;
	pthread_t threads[N];
	
	int tN = 0;
	for(tN; tN<N; tN++)
	{

		err = pthread_create(&threads[tN], NULL, (void *)multiplication, (void *)tN);
		if(err != 0)
		{
			perror("pthread_create encountered an error");
			exit(-1);
		}
	}
	
	//Join all the threads
	for(tN=0; tN<N; tN++)
	{
		err = pthread_join(threads[tN], NULL);
		if(err != 0)
		{
			perror("failed joining threads");
			exit(-1);
		}
	}
	
	//Print the output array to the output file
	fprintf(OUT, "#N = %d\n", N);	
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			fprintf(OUT, "%d ", out[i][j]);
		}
		fprintf(OUT, "\n");
	}
	
	return 0;
}
