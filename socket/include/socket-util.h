#ifndef HALO_SOCKET_UTILS
#define HALO_SOCKET_UTILS

#include<stdint.h>
#include "Socket.h"

#define DATA_BUFF_DEFAULT_SIZE 1024

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
typedef struct __Socket Socket;//forward declaration to Socket.h
typedef struct __dataBuffer_VTable dataBuffer_VTable;

/*message buffer to use on socket communication*/
typedef struct __dataBuffer{
	void* buffer;		//buffer to hold ADDRESS of data
	uint32_t size;		//written data size of buffer
	uint32_t max_size;	//maximum size of buffer
	
	const dataBuffer_VTable* vtable;//virtual functions table;
}dataBuffer;//message buffer to use on socket communication

struct __dataBuffer_VTable{
	void (*append)(dataBuffer* self, const char* string);
	void (*write)(dataBuffer* self, const char* string);
	const char* (*get)(dataBuffer* self);
};

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
*	@return				: Bytes received in total
*/
int sock_util__receive(intptr_t client_fd, dataBuffer* buffer);


/*
*	Interface for connection oriented (TCP) socket structs
*	write to socket file descriptor, and send data
*
*	@param client_fd	: file descriptor of client to receive data from
*	@param buffer		: buffer to read bytes to send
*	@return				: Bytes sent in total
*/
int sock_util__send(intptr_t client_fd, dataBuffer* buffer);


/*
*	Send message through Socket object. Common interface for TCP and UDP sockets
*	
*	@param self	: destination Socket to forward message
*	@return		: Bytes sent in total
*/
//dataBuffer sock_util__send__socket(Socket* self);


/*
*	Receive message through Socket object. Common interface for TCP and UDP sockets
*	
*	@param self: Socket to listen for a message receivation from others
*	@return	   : Bytes received in total
*/
//dataBuffer sock_util__receive__socket(Socket* self);


/*
*	Write string 	data to dataBuffer
*
*	@param buff: 	dataBuffer object to write string data
*	@param string: 	data to be written to buffer
*	@return	   : 	Bytes written in total
*/
void sock_util__buffer_write(dataBuffer* buff, const char* string);


/*
*	append string to end of data on dataBuffer
*
*	@param buff		: 	dataBuffer object to append string data
*	@param string	: 	data to be appended to buffer
*	@return	   		:
*/	
void sock_util__buffer_append(dataBuffer* buff, const char* string);
/*
*	return data on buffer as string
*
*	@param buff: 	dataBuffer object to get string data
*	@return	   : 	buffer as string
*/
const char* sock_util__buffer_get(dataBuffer* buff);

const static dataBuffer_VTable dataBuffer_VTable__default={
	.append=sock_util__buffer_append,
	.write=sock_util__buffer_write,
	.get=sock_util__buffer_get
};
/*
typedef struct __Socket_VTable Socket_VTable;//forward declaration to Socket
//to easily access functions from definitions
struct SocketUtil_VTable{
	const dataBuffer_VTable* dataBuffer;
	const Socket_VTable* Socket;			
};

const static struct SocketUtil_VTable SocketUtil_VTable__default={
	.dataBuffer=&dataBuffer_VTable__default,
	.Socket=&Socket_VTable__default
};
*/
#endif
