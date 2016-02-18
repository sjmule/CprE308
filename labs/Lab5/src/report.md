The expected output is sum = 18906.314453 and std = 4.348139
The actual from the pthreads is sum = 18518.019531 and std = 4.303257

The discrepancies are caused by multiple pthreads trying to access the same resource at the same time and changing their values.

Adding mutex locks fixed the issue with the original code.

The minimum number of condition needed would be 1.
The condition would be set when there are 2 items in the queue.
The consumer threads would wait until these condition is set, then they would both take an item from the queue to operate on, and the condition would be set back to false.


This program segfaults when trying to join the threads.  I have no clue why.
I am not making a test script since I don't know what more to test besides the one I was given.
My program can parse everything passed into it, it creates a random file with the post script data which I am assuming is the data it parsed.
But then the threads don't get the files off the queue or print them.

