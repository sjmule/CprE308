/**
 * @file      signal_thing2.c
 * @author    Scott Mueller
 * @date      2015-03-23
 * @brief     Part of a signal test thing
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
#include <signal.h>

void my_sig_handler(int i)
{
	printf("I got a signal!\n");
}

int main(int argc, char** argv)
{
	printf("%d\n", getpid());
	signal(42, my_sig_handler);
	while(1);
	return 0;
}