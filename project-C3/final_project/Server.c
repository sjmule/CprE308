#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

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
	connect(dataSocket, (struct sockaddr*)&ServAddr, ServAddr);

	///////////// Code we're replicating goes below

	/**
	 * This is where code goes
	 */

	 //This redirects the data being cat'd to NetCat
	 write(dataSocket, buffer, strlen(buffer));

	return 0;
}

