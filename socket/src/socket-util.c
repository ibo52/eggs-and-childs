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
	
	b->buffer=(int8_t*)calloc(size, sizeof(int8_t));
	b->size=size;
	
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
*	Read from socket file descriptor, and store data read
*/
int sock_util__receive(intptr_t client_fd, dataBuffer* buffer_offset,uint32_t length){
	/*
	@param client_fd	: file descriptor of client to receive data from
	@param buffer_offset: buffer of byte to store received bytes
	@param length		: data length to store to buffer(offset). Should not exceed maximum length of buffer
	@return				: Bytes received in total
	*/
	
		int recv_retval;//total received size of message from procedure call 
		if( (recv_retval= recv(client_fd, buffer_offset->buffer , length, 0)) <0 ){
			fprintf(stderr, "Error while receiving from socket(Totally %i bytes received)\n",recv_retval);
			exit(errno);
		
		}
	
	return recv_retval;
}

int sock_util__receive__server(Server* self, int client_fd){
	/*
	@param client_fd	: file descriptor of client to receive data from
	@param buffer_offset: buffer of byte to store received bytes
	@param length		: data length to store to buffer(offset). Should not exceed maximum length of buffer
	@return				: Bytes received in total
	*/
	
		int recv_retval;//total received size of message from procedure call 
		if( (recv_retval= recv(client_fd, self->recv_buff->buffer , self->recv_buff->size, 0)) <0 ){
			perror("Error while receiving from socket");
			exit(recv_retval);
		
		}
	
	return recv_retval;
}

int sock_util__send(intptr_t client_fd, dataBuffer* buffer_offset, uint32_t length){
	/*
	@param client_fd	: file descriptor of client to receive data from
	@param buffer_offset: buffer of byte to read bytes to send
	@param length		: data length to send from buffer(offset). Should not exceed maximum length of buffer
	@return				: Bytes sent in total
	*/
	int sent_size=0;
	
	while( sent_size < length ){
	
		int size;
		if( (size = send(client_fd, buffer_offset->buffer + sent_size, length, 0)) <0 ){
			fprintf(stderr, "Error while sending to socket(Totally %i bytes sent)\n",sent_size);
			exit(errno);
		}
		sent_size+=size;
	}//will break safely if equal to 0; will exit if<0

	return sent_size;
}

int sock_util__send__server(Server* self, int client_fd){
	/*
	@param client_fd	: file descriptor of client to receive data from
	@param buffer_offset: buffer of byte to read bytes to send
	@param length		: data length to send from buffer(offset). Should not exceed maximum length of buffer
	@return				: Bytes sent in total
	*/
	int sent_size=0;
	int length=strlen((char *)self->send_buff->buffer);
	
	while( sent_size < length ){
	
		int size;
		
		if( (size = send(client_fd, self->send_buff->buffer + sent_size, length, 0)) <0 ){
			fprintf(stderr, "Error while sending to socket(Totally %i bytes sent)\n",sent_size);
			exit(errno);
		}
		sent_size+=size;
	}//will break safely if equal to 0; will exit if<0
	printf("sent %i bytes of %s\n",sent_size, (char*)self->send_buff->buffer);
	return sent_size;
}
