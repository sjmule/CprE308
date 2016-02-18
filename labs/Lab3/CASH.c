#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

//Line contains 80 chars, use getline
//man 2 chdir
//man 3 getcwd
//man 3 setenv
int main(int arg, char** argv)
{
	if(arg == 1)
	{
		printf("This is not a CASH script\n");
		printf("Files must start with the line \"#! /bin/cash\"\n");
		return 0;
	}
	char* input = argv[1];
	FILE* file;	
	
	file = fopen(input, "r");

	if(file == 0)
	{
		perror("Cannot open file");
		exit(-1);
	}
	else
	{
		char* firstLine = malloc(81* sizeof(char));
		char* line = malloc(81* sizeof(char));
		int t;
		t = NULL;
		getline(&firstLine, &t, file);
		//printf("%s", firstLine);
		if(strcmp(firstLine, "#! /bin/cash\n") == 0)
		{
			while(!feof(file))
			{
				getline(&line, &t, file);
				if(strlen(line) == 0)
					continue;
				if(line[0] == '#')
					continue;
				int i=0;
				char* command = malloc(81 * sizeof(char));
				for(; (i<9) && (i<strlen(line)) && (line[i] != ' ') && (line[i] != '\n'); i++)
				{
					command[i] = line[i];
				}
				command[i] = '\0';
				//printf("%s", command);
				if(strcmp(command, "echo") == 0)
				{
					char* args[] = {"/bin/bash", "-c", line, NULL};
					int child = fork();
					int status = 0;
					if(child == 0)
					{
						execvp("/bin/bash", args);
						perror("Error occured while trying to echo");
						return -1;
					}
					else if(child > 0)
						wait(&status);
					else
					{
						perror("Failed to execute echo");
						exit(-1);
					}
				}
				else if(strcmp(command, "cd") == 0)
				{
					char* path = malloc(81 * sizeof(char));
					int status = 0;
					i++;
					int j = 0;
					for(i; (i<strlen(line)) && (line[i] != '\n'); i++)
					{
						path[j++] = line[i];
					}
					//printf("%s\n", path);
					status = chdir(path);
					if(status == -1)
					{
						perror("Failed to change directory");
						exit(-1);
					}
				}
				else if(strcmp(command, "pwd") == 0)
				{
					char cwd[1024];
					char* cwdr;
					cwdr = getcwd(cwd, sizeof(cwd));
					//printf("%d\n", strlen(cwdr));
					printf("%s\n", cwdr);
				}
				else if(strcmp(command, "export") == 0)
				{
					char* var = malloc(81 * sizeof(char));
					char* value = malloc(81 * sizeof(char));
					int j = 0;
					i++;
					int g = 0;
					for(i; (i<strlen(line)) && (line[i] != '='); i++)
					{
						var[j++] = line[i];
					}
					i++;
					for(i; (i<strlen(line)) && (line[i] != '\n'); i++)
					{
						if(line[i] == '"')
							continue;
						value[g++] = line[i];
					}
					int status = 0;
					status = setenv(var, value, 0);
					//printf("I'm setting shit, %s = %s", var, value);
					if(status == -1)
					{
						perror("Failed to set Environment");
						exit(-1);
					}
				}
				else
				{	
					/*char* arguments = malloc(81 * sizeof(char));
					char* args[] = {command, arguments, NULL};
					int g = 0;
					if((i!=strlen(line)) && (line[i] != '\n'))
					{
						for(i; (i<strlen(line)) && (line[i] != '\n'); i++)
						{
							arguments[g] = line[i];
						}
					}
					else
					{
						args[1] = NULL;
					}
					execvp(command, args);
					perror("Failed to execute user program");
					exit(-1);*/
				}	
			}
		}
		else
		{
			printf("This is not a CASH script\n");
			printf("Files must start with the line \"#! /bin/cash\"\n");
		}
	}
	return 0;
}
