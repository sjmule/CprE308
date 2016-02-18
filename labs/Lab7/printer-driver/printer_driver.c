/**
 * @file      printer_driver.c
 * @author    Scott Mueller
 * @date      2015-03-17
 * @brief     Printer driver thing for class
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

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

///--- Prototypes ---///
int init_module(void);
void cleanup_module(void);
static int device_open(struct inode*, struct file*);
static int device_release(struct inode*, struct file*);
static ssize_t device_read(struct file*, char*, size_t, loff_t*);
static ssize_t device_write(struct file*, const char*, size_t, loff_t*);

///--- Macros ---///
#define SUCCESS 0
#define DEVICE_NAME "printer"
/// The max length of the message from the device
#define BUF_LEN 80
 
///--- Global Variables ---///
static int Major;			// Major number assigned to this device driver
static int Device_Open = 0;	// is the device open already?
static char msg[BUF_LEN];
static char *print_ptr;
static char *msg_ptr;

///--- Register Callbacks ---///
static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

///--- Init Module ---///
int __init device_init(void)
{
	Major = register_chrdev(0, DEVICE_NAME, &fops);
	
	if(Major < 0)
	{
		printk(KERN_ALERT "Registering char device failed with %d\n", Major);
		return Major;
	}

	return SUCCESS;
}

///--- Cleanup Module ---///
void __exit device_exit(void)
{
	unregister_chrdev(Major, DEVICE_NAME);
} 

///--- register init and exit functions ---///
module_init(device_init);
module_exit(device_exit);

///--- Device Open ---///
static int device_open(struct inode *inode, struct file *file)
{
	static int counter = 0;
	
	if (Device_Open)
		return -EBUSY;
	
	Device_Open++;
	sprintf(msg, "I already told you %d times Hello World!\n", counter++);
	msg_ptr = msg;
	try_module_get(THIS_MODULE);
	return SUCCESS;
}

///--- Device Release ---///
static int device_release(struct inode *inode, struct file *file)
{
	Device_Open--;
	module_put(THIS_MODULE);
	return SUCCESS;
}

///--- Device Read ---///
static ssize_t device_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
	printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
	return -EINVAL;
}

///--- Device Write ---///
static ssize_t device_write(struct file *file, const char *buffer, size_t len, loff_t *offset)
{
	int bytes_written = 0;
	int lentemp = len;
	print_ptr = msg;
	//printk("%s\n", print_ptr);
	//printk("%d\n", len);

	while(len)
	//while(len && buffer[bytes_written+1] >= ' ' && buffer[bytes_written+1] <= '~')
	{
		get_user(*(print_ptr), buffer++);
		if(*(print_ptr) == '\n')
		{
			*(print_ptr) = 0;
			break;
			
		}
		print_ptr++;
		bytes_written++;
		len--;
	}

	msg[bytes_written] = '\0';
	printk("%s\n", msg);

	print_ptr = NULL;

	return lentemp;
}
