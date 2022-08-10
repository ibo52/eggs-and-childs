# Shared resources problems.
Setted on Ubuntu GNU/Linux system.
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
