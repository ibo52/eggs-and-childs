#Inter Process communication Problems 
## Simple TCP/UDP Server/Client programs for socket programming on POSIX.

- C programs that maintains Inter process communication on localhost
  * Object oriented programming concepts applied to be able to understand OOAD better
  * sockets communication implemented to be able to understand IPC better

## Objects
### Server.c
- Defines object 'Server'
- Server is base class for TCPServer and UDPServer.
- Holds the socket information

### TCPServer.c and TCPClient.c
- Defines objects 'TCPServer' and 'TCPClient'
- Maintains connection oriented communication

### UDPServer.c and UDPClient.c
- Defines objects 'UDPServer' and 'UDPClient'
- Maintains connectionless communication

***

# Shared resources problems.
## Simple Consumer-Producer problem on shared memory.
* eggs-and-childs.cxx
  * _compile: `g++ eggs-and-childs.cxx`_
  * Uses semaphores,ipc,shared-mem for solution,(UNIX defined)
  * _open two terminals and run the file on two terminal respectively.
  first one will be the chicken which fill the resource,
second one will be the childs which empty the resource._

* PhoneOperator.c
  * _compile: `gcc PhoneOperator.c -pthread`_
  * sharing problem on restricted-shared resources
  * Uses threads and semaphores for solution(POSIX defined)

***

# Threading problem: matrix calc
- programmed on java(openjdk-8 based, openjdk-11).
  * _compile: `javac MatrixMultiplication.java`_
  * _run:      `java MatrixMultiplication`_
  * threading solution of multiplication. Every thread solves certain row of result. Then (if remains) jumps another row on range as number of total Processor.
