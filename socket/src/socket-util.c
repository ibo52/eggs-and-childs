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
static int min(int a, int b){
	if(a<b)
		return a;
		
	return b;
}

dataBuffer* sock_util__alloc_buffer(uint32_t size){//to allocate dataBuffer struct
	/*
	@param size: size of the buffer
	Allocate buffer of bytes to use through sockets
	*/
	dataBuffer* b= (dataBuffer*)calloc(1, sizeof(dataBuffer));
	
	b->buffer = calloc(size+1, sizeof(int8_t));
	b->size=0;
	b->max_size=size;
	
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


dataBuffer sock_util__send__socket(Socket* self){
	/*
	@param self	: sender Socket to forward message to other
	@return		: Bytes sent in total
	*/
	int MAX_BYTES_PER_SEND=65536-28;//28 allocated for is udp protocol headers
	int sent_size=0;
	int length=self->send_buff->size;

	struct sockaddr_in client=self->socket;	//recvfrom will fill this struct destination socket
	socklen_t client_len=sizeof(client);
	
	while( sent_size < length ){
	
		int size;
		int per_send_len=min(MAX_BYTES_PER_SEND, length-sent_size);
		
		if( (size = sendto(self->fd, self->send_buff->buffer + sent_size, per_send_len, 0, (struct sockaddr *)&client, client_len)) <0 ){
			fprintf(stderr, "Error while sending to socket(Totally %i bytes sent): %s\n",sent_size, strerror(errno));
			exit(errno);
		}
		sent_size+=size;
	}//will break safely if equal to 0; will exit if<0
	//printf("sent %i bytes of %s\n",sent_size, (char*)self->send_buff->buffer);
	self->send_buff->size=sent_size;
	dataBuffer retData={NULL, sent_size, 0};
	return retData;
}

dataBuffer sock_util__receive__socket(Socket* self){
	/*
	@param self: Socket to listen for a message receivation from others
	@return	   : Bytes received in total
	*/
	
		int recv_retval;			//total received size of message from procedure call 
		struct sockaddr_in *client=malloc(1*sizeof(struct sockaddr_in));	//recvfrom will fill this struct
		socklen_t client_address_size = sizeof(*client);
			
		if( (recv_retval= recvfrom(self->fd, self->recv_buff->buffer , self->recv_buff->max_size, 0, (struct sockaddr *)client, &client_address_size)) <0 ){
			perror("Error while receiving from socket");
			exit(recv_retval);
		
		}
		
	self->recv_buff->size=recv_retval;
	
	dataBuffer retData={client, recv_retval, 0};
	/*
	int addr=client->sin_addr.s_addr;
	
	
	printf("Receive SOCKET func:  Domain:%s address:%i.%i.%i.%i\n",(client->sin_family == AF_INET?"AF_INET":"UNKNOWN"),
	(addr&0xff), (addr>>8&0xff), (addr>>16&0xff), addr>>24&0xff);	
	*/
	//Next implementation: If socket type==TCP; then do not malloc struct sockaddr_in *client, return NULL
	return retData;
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
