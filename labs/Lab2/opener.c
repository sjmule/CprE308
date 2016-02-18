#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

//Evince opens PDFs
//VLC for mp3s

int main(int arg, char* argv[])
{
	int status = 0;
	pid_t child;
	const char file[256];
	strcpy(file, argv[1]);
	const char* extension;	
	const char* program;
	//check what type is
	extension = strrchr(file, '.');
	if(strcmp(extension, ".doc") == 0 || strcmp(extension, ".odt") == 0)
	{
		program = "libreoffice"; //figure out exact later
	}
	else if(strcmp(extension, ".png") == 0 || strcmp(extension, ".PNG") == 0)
	{
		program = "gwenview";
	}
	else if(strcmp(extension, ".txt") == 0)
	{
		program = "gedit";
	}
	else if(strcmp(extension, ".pdf") == 0)
	{
		program = "evince";
	}
	else if(strcmp(extension, ".mp3") == 0)
	{
		program = "vlc";
	}
	else
	{
		printf("Can't open this, not supported");
		return 0;
	}
	
	char* args[] = {program, file, NULL};
	
	child = fork();	

	if(child == 0)
	{
		//child code, open file
		execvp(program, args);
		perror("Child process encountered an error");
		return -1;
	}
	else if(child > 0)
	{
		wait(&status);
		printf("Child process is done, status is: %d\n", status);
		return 0;
	}
	else
	{
		perror("Failed to fork");
		exit(-1);
	}

	return 0;
}



