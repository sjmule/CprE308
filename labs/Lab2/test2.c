#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int arg, char** argv)
{
	//char extension[] = argv[1];
	if(strcmp(argv[1], "test.c") == 0)
	{
		printf("This is test.c");
	}
	else
	{
		printf("This is not test.c");
	}
	
	return 0;
}
