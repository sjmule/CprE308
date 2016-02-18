#Lab Project Part 1

In this lab we explored different scheduling algorithms and implemented 3 different types of algorithms: shortest remaining time
next, round robin, and priority round robin.

##Scheduling Algorithms
Scheduling algorithms are how a processor determines which process to dedicate time and resources to when it has more processes that need 
to run than it can run at one time.  The shortest remaining time next and first in first out algorithms take a process and run it to 
completion before switching to a new task.  Round robin and priority round robin dedicate only a predetermined amount of time to each 
process before switching to a new one.  

##Round Robin and Proirity Round Robin
The round robin algorithm is very fair to all processes as it simply goes through each one and 
runs it until the predetermined amount of time is up or the process finishes, which ever comes first, then switches to a new process. 
This can lead to many context switches which can lead to decreased performance overall.  The priority round robin looks at the priority
of each process when deciding which process to run next.  Priorities are split into levels, the algorithm will run all processes of the 
highest priority first in a round robin fashion before going to the next lower priority and running all those and so on.

##Shortest Remaining Time Next
The shortest remaining time algorithm sorts the list by shortest remaining time every time that a task is added. When it chooses a new task it sorts the currently running task back into the list if it has time left. It then pulls from the head of the list to get the next task to be run.
