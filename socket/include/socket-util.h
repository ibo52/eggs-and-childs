#ifndef HALO_SOCKET_UTILS
#define HALO_SOCKET_UTILS

#include<stdint.h>
#include "Socket.h"

#define MAX_ALLOWED_CONN 1
#define TCP_PORT 50004 
#define UDP_PORT 50005 

#define CONN_TYPE_TCP_SERVER 0
#define CONN_TYPE_UDP_SERVER 1

#define CONN_TYPE_TCP_CLIENT 2
#define CONN_TYPE_UDP_CLIENT 3
/*
*
*/
typedef struct __Socket Socket;//forward declaration to Server.h


/*message buffer to use on socket communication*/
typedef struct __dataBuffer{
	int8_t* buffer;		//buffer to hold data
	uint32_t size;		//maximum size of buffer
}dataBuffer;//message buffer to use on socket communication


/*
	@param size: size of the buffer
	Allocate buffer of bytes to use through sockets
*/
dataBuffer* sock_util__alloc_buffer(uint32_t size);


/*
	@param dataBuffer: pointer to buffer to be free'd
	Deallocate buffer of bytes which used through socket communication
*/
void sock_util__dealloc_buffer(dataBuffer** buffer);


/*
*	Interface for connection oriented (TCP) socket structs
*	Read from socket file descriptor, and store data read
*
*	@param client_fd	: file descriptor of client to receive data from
*	@param buffer		: buffer to store received bytes
*	@param length		: maximum store length to fill buffer
*	@return				: Bytes received in total
*/
int sock_util__receive(intptr_t client_fd, dataBuffer* buffer,uint32_t length);


/*
*	Interface for connection oriented (TCP) socket structs
*	write to socket file descriptor, and send data
*
*	@param client_fd	: file descriptor of client to receive data from
*	@param buffer		: buffer to read bytes to send
*	@param length		: maximum read length of buffer
*	@return				: Bytes sent in total
*/
int sock_util__send(intptr_t client_fd, dataBuffer* buffer,uint32_t length);


/*
*	Send message through Socket object. Common interface for TCP and UDP sockets
*	
*	@param self	: destination Socket to forward message
*	@return		: Bytes sent in total
*/
dataBuffer sock_util__send__socket(Socket* self);


/*
*	Receive message through Socket object. Common interface for TCP and UDP sockets
*	
*	@param self: Socket to listen for a message receivation from others
*	@return	   : Bytes received in total
*/
dataBuffer sock_util__receive__socket(Socket* self);
#endif
