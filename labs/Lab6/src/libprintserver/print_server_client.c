/**
 * @file      print_server_client.c
 * @author    Scott Mueller
 * @date      2015-03-25
 * @brief     The c file of public API of libprinter.so library
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

#include "print_server_client.h"

int printer_print(int* handle, char* driver, char* job_name, char* description, char* data)
{

}

printer_driver_t** printer_list_drivers(int *number)
{
	
}