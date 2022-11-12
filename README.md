# Shared resources problems.
- Setted on Ubuntu GNU/Linux system.
* eggs-and-childs.cxx
  * _compile: `g++ eggs-and-childs.cxx`_
  * Producer-consumer problem on shared resources.
  * Uses semaphores,ipc,shared-mem for solution,(UNIX defined)
  * _open two terminals and run the file on two terminal respectively.
  first one will be the chicken which fill the resource,
second one will be the childs which empty the resource._

* PhoneOperator.c
  * _compile: `gcc PhoneOperator.c -pthread`_
  * sharing problem on restricted-shared sources
  * Uses threads and semaphores for solution(POSIX defined)

# Threading problem: matrix calc
- programmed on java(openjdk-8 based, openjdk-11).
  * _compile: `javac MatrixMultiplication.java`_
  * _run:      `java MatrixMultiplication`_
  * threading solution of multiplication. Every thread solves certain row of result. Then (if remains) jumps another row on range as number of total Processor.
