Module			Size  Used by
filename:		/host/cpre308/labs/Lab7/hello-world/hello_world.ko
description:	A simple hello world driver
author:			Scott Mueller scottm1@iastate.edu
license:		GPL
depends:
vermagic:		3.18.8scottm1 mod_unload
Link Start
Module			Size  Used by
hello_world		 779  0
Link Terminated
Module			Size  Used by

The prototypes are not identical because C does not support overloading
and if the prototype were the same the system would have issues determining
which command to execute.  The extra parameter is used to indicate where
to start reading the file from.

Files can support open, read, write, lock, poll, and iterate.

When the file is opened it prints "I already told you %d times Hello World!\n", counter++
The counter keeps track of the number of times the file was opened.
When writen to the file prints that this operation is not supported.
When read from the file prints the next few bytes of the message. It returns 0 if at the end of the message. Otherwise it returns the number of bytes read.
When closed, the file prints info about the module.

My kernel is tainted by this, cool, I don't really know what that means,
but I find it interesting.

Module was assigned major number 254

							output
mknod /dev/cpre308-0 c 254 0    nothing
cat /dev/cpre308-0		I already told you 0 times Hello World!
cat /dev/cpre308-0		I already told you 1 times Hello World!
echo "hello" > /dev/cpre308-0							//Figure this out
mknod /dev/cpre308-1 c 254 0    nothing
cat /dev/cpre308-0		I already told you 2 times Hello World!
cat /dev/cpre308-1		I already told you 3 times Hello World!
rmmod hello_file.ko		nothing
cat /dev/cpre308-0		No such device or address


This lab took longer than it was stated it should. I blame the network when compiling the kernel.
If the kernel compiled faster we could have asked questions in lab about how to write to a Linux kernel module,
but instead I had to Google for answers and all the results were how to write a Linux kernel module, not how to write to
a Linux kernel module like I wanted.

This lab taught us about how the Linux kernel works with drivers and such.  It was very interesting to learn how
data is passed to and from user space to the kernel and to the driver and such.

