/**
 * @file      FIFO_sender.c
 * @author    Scott Mueller
 * @date      2015-03-25
 * @brief     A program that uses a named to send messages to FIFO_receiver.c
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
#include <unistd.h>

int main(int argc, char** argv)
{
	int fd;
	char *buff = malloc(80 * sizeof(char));
	mkfifo("/home/scottm1/cpre308/labs/Lab6/Lab6fifo", S_IRWXU);
	fd = open("/home/scottm1/cpre308/labs/Lab6/Lab6fifo", O_WRONLY);
	if(fd = 0)
	{
		perror("Cannot open log file");
		exit(-1);
	}
	while(1)
	{
		scanf("%s", buff);
		write(fd, buff, sizeof(buff));
		fsync(fd);
	}

	free(buff);
	return 0;
}