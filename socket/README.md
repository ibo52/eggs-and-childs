# Simple TCP/UDP Server/Client
### Simple programs for socket programming on POSIX.

- C programs that maintains Inter process communication on localhost
  1. Object oriented programming concepts applied to be able to understand OOAD better
  2. sockets communication implemented to be able to understand IPC better

## Objects
### Socket.c
- Base class for client/server structures.
- Maintains connection of sys/socket.h structures.
- Manages communicating easy by using send/receive functions

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
## To Do
1. Base socket communication [ :heavy_check_mark: ]
2. TCP socket communication [ :heavy_check_mark: ]
3. UDP socket communication [ :heavy_check_mark: ]
4. RTP/UDP socket communication [ :wavy_dash: ]
   1. Packet re-ordering on client side [ :wavy_dash: ]
5. RTP/UDP video streaming [ :heavy_minus_sign: ]
***
system | specs | of development|
--- | --- | --- |
_Environment_| Ubuntu 22.04| gcc 11.4.0
_kernel_  | 6.2.0-35-generic_
  ***

