#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char** argv)
{
	long long tim_e;
	tim_e = time(NULL);

	char *command = malloc(80 * sizeof(char));
	printf("%lld\n", tim_e);
	sprintf(command, "git commit -m %lld", tim_e);

	system("git add .");
	system(command);
	system("git push");

	free(command);
}