#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int arg, char** argv)
{
	char *file = argv[1];
	const char *extension;
	extension = strrchr(file, '.');
	if(strcmp(extension, ".c") == 0)
	{
		printf("This is a C file");
	}
	else
	{
		printf("This not is a C file");
	}
	
	return 0;
}
