/**
 * @file      signal_thing1.c
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

int main(int argc, char** argv)
{
	kill(atoi(argv[1]), 42);
	return 0;
}