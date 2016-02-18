In this lab we learned how to push, pull, and commit to and from a github repository.
We learned basic debugging techniques for debugging C code from the Linux terminal.
These techniques included using the GNU Debugging Tool (GDB) to step through code, place break points, check memory at certain spots in the code, and check for seg faults.
We also learned how to use Valgrind to check for memory leaks in our code.
The program is not working properly because on line 32 the for loop is initialized to run to i<=length or until i=11. This causes rand_array to go out of bounds and results in a seg fault on line 40 when we try to access its memory at this out of bounds location.
