#308 Project Proposal - USB Copycat
##Team
- Group C3
- Steff Bisinger (Netid: srbising, Section C)
- Scott Meuller (Netid: scottm1, Section C)

##Project Idea
Our project will be a malicious USB driver that... helps... the user transfer files to and from the computer.
This project will have the following objectives:
- Function normally. No one must suspect.
- Copy data to a separate location on the sly
- Use networking to send the data to the attacker
- ???
- (Bonus) Profit?
- (Bonus) Redefining system calls
- (Bonus) Support copying multiple files at the same time

##Concepts from class
This uses the following topics from class:
- Loadable drivers
- Inter-process communication
- (Bonus) Threading

##Timeline
- Week 1:
  * Look up relevent system calls
  * Setup up testing environment
  * Research compiling and installing drivers
- Week 2:
  * Do the bulk of the coding
  * Test basic functionality
- Week 3:
  * Finish up coding
  * Test network functionality

##Rubric
|Part|Unsatisfactory|Satisfactory|Beyond Satisfactory|
|---|---|---|---|
|Functional|Prints a help message (0-25pts)|Copies files to and from the flashdrive(26-50pts)|Looks extremely innocuous (51-75pts)|
|Sockets|Doesn't scream bloody murder when it fails (0-25)|Socket can send data to a listening computer on the same network(26-50)|Socket can send across the interwebs (ie. uses dns server to reach a host)(51-75)|
|Copying data|Prints to console(0-25)|Creates a copy of a single file(26-50)|Creates a copy of multiple files with one command(51-75)|
|Extra Credit|N/A|Redefine a single system call(26-50)|Redefine 2 or more system calls(51-75)|
