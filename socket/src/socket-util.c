#include<stdio.h>
#include<stdlib.h>

#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close(), sleep
#include<errno.h>
#include<netinet/in.h>
#include <string.h>

#include "socket-util.h"

/*
*	Allocate memory to store incoming/outgoing socket data
*/

dataBuffer* sock_util__alloc_buffer(uint32_t size){//to allocate dataBuffer struct
	/*
	@param size: size of the buffer
	Allocate buffer of bytes to use through sockets
	*/
	dataBuffer* b= (dataBuffer*)calloc(1, sizeof(dataBuffer));
	
	b->buffer = calloc(size+1, sizeof(int8_t));
	b->size=0;
	b->max_size=size;
	
	b->vtable=&dataBuffer_VTable__default;
	return b;
}

/*
*	Free the buffer of bytes which used through socket communication
*/
void sock_util__dealloc_buffer(dataBuffer** buffer){
	/*
	@param dataBuffer: pointer to buffer to be free'd
	*/

	free( (*buffer)->buffer );
	free( (*buffer) );
	(*buffer)=NULL;
}
/*
*	Interface for connection oriented (TCP) socket structs
*	Read from socket file descriptor, and store data read
*/
int sock_util__receive(intptr_t client_fd, dataBuffer* buffer_offset){
	/*
	@param client_fd	: file descriptor of client to receive data from
	@param buffer_offset: buffer of byte to store received bytes
	@return				: Bytes received in total
	*/
	
		int recv_retval;//total received size of message from procedure call 
		if( (recv_retval= recv(client_fd, buffer_offset->buffer , buffer_offset->max_size, 0)) <0 ){
			fprintf(stderr, "Error while receiving from socket(Totally %i bytes received)\n",recv_retval);
			exit(errno);
		
		}
		buffer_offset->size=recv_retval;
	
	return recv_retval;
}


/*
*	Interface for connection oriented (TCP) socket structs
*	write to socket file descriptor, and send data
*/
int sock_util__send(intptr_t client_fd, dataBuffer* buffer_offset){
	/*
	@param client_fd	: file descriptor of client to receive data from
	@param buffer_offset: buffer of byte to read bytes to send
	@return				: Bytes sent in total
	*/
	int sent_size=0;
	
	while( sent_size < buffer_offset->size ){
	
		int size;
		if( (size = send(client_fd, buffer_offset->buffer + sent_size, buffer_offset->size, 0)) <0 ){
			fprintf(stderr, "Error while sending to socket(Totally %i bytes sent)\n",sent_size);
			exit(errno);
		}
		sent_size+=size;
	}//will break safely if equal to 0; will exit if<0

	return sent_size;
}

void sock_util__buffer_write(dataBuffer* buff, const char* string){
	/*
	*	Write string 	data to dataBuffer
	*
	*	@param buff		: 	dataBuffer object to write string data
	*	@param string	: 	data to be written to buffer
	*	@return	   		: 
	*/
	strncpy((char* )buff->buffer, string, buff->max_size);
	buff->size = strlen((char* )buff->buffer);
}


void sock_util__buffer_append(dataBuffer* buff, const char* string){
	/*
	*	append string to end of data on dataBuffer
	*
	*	@param buff		: 	dataBuffer object to append string data
	*	@param string	: 	data to be appended to buffer
	*	@return	   		:
	*/
	uint32_t n=buff->max_size - buff->size;
	strncat((char* )buff->buffer, string , n);
	
	buff->size = strlen((char* )buff->buffer);
}


const char* sock_util__buffer_get(dataBuffer* buff){
	/*
	*	return data on buffer as string
	*
	*	@param buff: 	dataBuffer object to get string data
	*	@return	   : 	buffer as string
	*/
	return (char*)buff->buffer;
}
