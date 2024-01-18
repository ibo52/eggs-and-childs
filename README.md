# Inter Process communication Problems 
## Data sharing between processess
### Simple TCP/UDP Server/Client programs for _socket_ programming on POSIX.

- C programs that maintains Inter process communication on localhost
	* _compile: `clear && make`_
  * Object oriented programming concepts applied to be able to understand OOAD better
  * socket communication implemented to be able to understand IPC better

***

## Shared resources problems.
### Simple Consumer-Producer problem on _shared memory_.
* eggs-and-childs.cxx
  * _compile: `g++ eggs-and-childs.cxx`_
  * Uses semaphores,ipc,shared-mem for solution,(UNIX defined)
  * _open two terminals and run the file on two terminal respectively.
  first one will be the chicken which fill the resource,
second one will be the childs which empty the resource._

### Simple _access_ problem on restricted resources
* PhoneOperator.c
  * _compile: `gcc PhoneOperator.c -pthread`_
  * sharing common data between threads
  * Uses threads and semaphores for solution(POSIX defined)

***

# _Threading_ problem: matrix calc
- programmed on java(openjdk-8 based, openjdk-11).
  * _compile: `javac MatrixMultiplication.java`_
  * _run:      `java MatrixMultiplication`_
  * threading solution of multiplication. Every thread solves certain row of result. Then (if remains) jumps another row on range as number of total Processor.
