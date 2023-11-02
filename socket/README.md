# Simple TCP/UDP Server/Client
### Simple programs for socket programming on POSIX.

- C programs that maintains Inter process communication on localhost
  1. Object oriented programming concepts applied to be able to understand OOAD better
  2. sockets communication implemented to be able to understand IPC better

## Objects
### Socket.c
- Defines object 'Socket'
- Socket is base class for TCP/UDP Server/Client files.
- Holds the socket information for communication

### TCPServer.c and TCPClient.c
- Defines objects 'TCPServer' and 'TCPClient'
- Maintains connection oriented communication

### UDPServer.c and UDPClient.c
- Defines objects 'UDPServer' and 'UDPClient'
- Maintains connectionless communication
***
system | specs | of development|
--- | --- | --- |
_Environment_| Ubuntu 22.04| gcc 11.4.0
_kernel_  | 6.2.0-35-generic_
  ***

