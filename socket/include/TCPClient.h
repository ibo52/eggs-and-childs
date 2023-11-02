#ifndef HALO_SOCKET_TCPCLIENT
#define HALO_SOCKET_TCPCLIENT

#include<stdint.h>
#include "socket-util.h"

typedef struct __TCPClient{
	Socket* super;
}TCPClient;

/*
*	Create new object (Allocate data on memory)
*/
TCPClient* tcp_client__new(int addr, int port);

/*
*	Destroy the object(free the address that memory points)
*/
void tcp_client__destroy(TCPClient** self);

/*
*	starts the client to send data to connection
*/
void tcp_client__start(TCPClient* self);

#endif
