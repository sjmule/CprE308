Return values: 
On success: The parent returns the PID of the child process
The child returns 0
On failure: The parent returns -1
The child is not created and cannot return

The parent's process ID is the same as it was
The child's process ID is a new ID

This lab we learned how to create child processes with forks, make them do different things from the parent, and have the parent wait till they complete.

We also learned how to use evec
