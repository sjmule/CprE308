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
	int fd, n, s, ClientAddrLen;
	socklen_t ServAddrLen;
	char *line = malloc(80 * sizeof(char));
	size_t lineSize = 80;

	ServAddr.sin_family = AF_UNIX;
	ServAddr.sin_port = 54836it;
	ServAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServAddrLen = sizeof(ServAddr);

	fd = socket(AF_UNIX, SOCK_STREAM, 0);
	bind(fd, (struct sockaddr*)&ServAddr, ServAddrLen);

	listen(fd, 2);
	s = accept(fd, (struct sockaddr*)&ClientAddr, &ClientAddrLen);

	for(;;)
	{
		n = read(s, line, lineSize);
		printf("%s\n", line);
		if(strncmp(line, "quit", 4) == 0)
		{
			break;
		}
	}

	free(line);
	close(fd);
	close(s);
	return 0;
}