#include <unistd.h>

int main(int arg, char** argv)
{
	const char* program = "gedit";
	const char files[] = "report.md";
	char* args[] = {program, files, NULL};	
	execvp(program, args);
	return 0;

}
