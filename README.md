# Shared resources problems.
Setted on Ubuntu GNU/Linux system.
* eggs-and-childs.cxx
  * Producer-consumer problem on shared resources.
  * Uses semaphores,ipc,shared-mem for solution,(UNIX defined)
  * _open two terminals and run the file on two terminal respectively.
  first one will be the chicken which fill the resource,
second one will be the childs which empty the resource._

* PhoneOperator.c
  * sharing problem on restricted-shared sources
  * Uses threads and semaphores for solution(POSIX defined)
