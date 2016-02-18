!!!!!Extra Credit!!!!
! This program can handle matrices of various sizes.  It does this by reading the first line in the first file.
! The program assumes the first line of both files is the same and that therefore both matrices are of the same size.
! The program assumes that the first line is in the format "#N = 64" 

One of the expected outputs would be "I am thread 1\n"
The actual output is either "I am thread 0\n" or "I am thread 0\n" "I am thread 2\n" "I am thread 2\n"

After joining the threads, the program outputs
"I am thread 1\n" "I am thread 2\n" "I am thread 0\n"
This is the expected output of the program

This lab caused me to need to develop more of an understanding of pointers.  When passing values as void pointers and re-casting them it was hard for me to understand at first how the values were passed and what they referred to when they were.  Specifically, when to and when not to use a '&' with the variable name.
This program uses one thread to generate one row of the output matrix.  For instance, if there are 32 rows in the input matrices, the program will create 32 threads and each one will output one row of the output matrix.
For this reason, the maximum number of rows this program can handle is limited by the number of threads your system allows it to create.

As the number of threads created increases, the performance gain from each thread created only increases to a certain point.
When the number of threads running on a system increases pass the number of threads a system is able to run at a time, the performance of a program will no longer increase.
This is because the system now needs to take time to perform context switches to accomidate each thread and can no longer just run them all simultainously.
