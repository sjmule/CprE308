The program outputed:
My child asked "Are you my mummy?"
Then returned 42

These lines are printed right before the parent process returns.

If a process tries to write more bytes to a pipe than there are availible it will block until there are enough bytes availible.
It doesn't change.
Since Linux 2.6.11, the pipe capacity is 65536 bytes.



The terminal that the cat command was run in prints "hello fifo".
The terminal that the echo command was run in waits for the cat command to be run in the other terminal, the terminal the cat command was 
run in then prints "hello fifo".
The kernel handles all data internally and does not store it on the file system.



The six types of sockets are SOCK_STREAM, SOCK_DGRAM, SOCK_SEQPACKET, SOCK_RAW, SOCK_RDM, and SOCK_PACKET.
Two domains are AF_UNIX and AF_INET.



mq_test2 outputs:
Received message "I am the Doctor"
Received message "I am the Master"
Then mq_test1 outputs:
Received message "I am Clara"

The output is the same if the programs are opened in reverse order.

mq_test2 outputs:
Received message "I am the Doctor"
Received message "I am the Master"
mq_test1 outputs:
Received message "I am Captain Jack Harkness"



shm_test1 outputs first and outputs:
a_string = "I am a buffer in the shared memory area"
an_array[] = {42, 1, 4, 9, 16}
a_ptr = 140733856488928 = "I am a string allocated on main's stack!"
Then shm_test2 outputs:
a_string = "I am a buffer in the shared memory area"
an_array[] = {42, 1, 4, 9, 16}
Segmentation fault (core dumped)

When run in reverse shm_test2 outputs first outputing:
a_string = "I am a buffer in the shared memory area"
an_array[] = {0, 1, 4, 9, 16}
Segmentation fault (core dumped)
shm_test1 then outputs and outputs:
a_string = "I am a buffer in the shared memory area"
an_array[] = {0, 1, 4, 9, 16}
a_ptr = 140737400680816 = "I am a string allocated on main's stack!"

When run individually shm_test1 outputs the same as above.
a_string = "I am a buffer in the shared memory area"
an_array[] = {0, 1, 4, 9, 16}
a_ptr = 140733796143952 = "I am a string allocated on main's stack!"
shm_test2 outputs:
a_string = "I am a buffer in the shared memory area"
an_array[] = {42, 1, 4, 9, 16}
Segmentation fault (core dumped)

shm_test2 is segfaulting because the memory address it is trying to read is allocated on the stack of shm_test1 and not in shared memory space.

It's hard to tell if the two apps read and tried to set the variable at the same time, but it looks like they had no problems incrementing
the variable shared_mem->count.  Count was set to 0 originally, and was 2 after both programs terminated.

Shared memory could be deleted by using O_TRUNC



Semaphores last in the kernel until destroyed.
They are destoryed by calls such as sem_unlink for named semaphores and sem_destroy for unnamed semaphores.

To use a named semaphore, the following functions would be needed:
sem_open(semaphore_name);
Then sem_post(semaphore_name) and sem_wait(semaphore_name) can be used.



When Ctrl+C is pressed, the signal handler in the program activates and catches the signal, it calls another function which causes the
program to print a message.
The signal number Ctrl+C sends is 2.
When forking, the child uses the parent's signal handler.
When using exec, the signal handlers of the new process are set to default.



signal_test1 takes the pid of signal_test2 as a commandline argument then sends the signal to signal_test2 which prints "I got a signal!"
Upon running signal_test2 it prints its pid to be fed into signal_test1



The program could not run, message displayed:
./lib_test: error while loading shared libraries: libhello.so: cannot open shared object file: No such file or directory

The program outputs:
Hello
World
World
World
i=42

