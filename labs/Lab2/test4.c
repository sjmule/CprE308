#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int arg, char** argv)
{
	const char* program = "gedit";
	const char files[256];
	strcpy(files, argv[1]);
	printf("%s\n%s\n", argv[1], files);
	char* args = (program, files, NULL);
	execvp(program, args);
	return 0;
}
