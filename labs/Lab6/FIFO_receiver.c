/**
 * @file      FIFO_receiver.c
 * @author    Scott Mueller
 * @date      2015-03-25
 * @brief     A program that uses a named to receive messages from FIFO_sender.c
 * @copyright MIT License (c) 2015
 */
 
/*
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
	int fd;
	char *buff = malloc(80 * sizeof(char));
	fd = open("/home/scottm1/cpre308/labs/Lab6/Lab6fifo", O_RDONLY);
	if(fd = 0)
	{
		perror("Cannot open log file");
		exit(-1);
	}
	while(1)
	{
		read(fd, buff, 80);
		printf("%s\n", buff);
	}

	free(buff);
	return 0;
}