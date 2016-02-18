/**
 * @file      shm_test.h
 * @author    Jeramie Vens
 * @date      2015-02-24: Last updated
 * @brief     Shared memory space example
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


#ifndef SHM_TEST_H
#define SHM_TEST_H

struct SHM_SHARED_MEMORY
{
	char a_string[100];
	int an_array[5];
	char* a_ptr;
	int count;
};

#endif
