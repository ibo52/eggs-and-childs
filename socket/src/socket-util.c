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
*	Interface for connection oriented (TCP) socket structs
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


/*
*	Interface for connection oriented (TCP) socket structs
*	write to socket file descriptor, and send data
*/
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


dataBuffer sock_util__send__socket(Socket* self){
	/*
	@param self	: sender Socket to forward message to other
	@return		: Bytes sent in total
	*/
	int sent_size=0;
	int length=strlen((char *)self->send_buff->buffer);
	struct sockaddr_in client=self->socket;	//recvfrom will fill this struct destination socket
	socklen_t client_len=sizeof(client);
	
	while( sent_size < length ){
	
		int size;
	
		if( (size = sendto(self->fd, self->send_buff->buffer + sent_size, length, 0, (struct sockaddr *)&client, client_len)) <0 ){
			fprintf(stderr, "Error while sending to socket(Totally %i bytes sent): %s\n",sent_size, strerror(errno));
			exit(errno);
		}
		sent_size+=size;
	}//will break safely if equal to 0; will exit if<0
	printf("sent %i bytes of %s\n",sent_size, (char*)self->send_buff->buffer);
	
	dataBuffer retData={NULL, sent_size};
	return retData;
}

dataBuffer sock_util__receive__socket(Socket* self){
	/*
	@param self: Socket to listen for a message receivation from others
	@return	   : Bytes received in total
	*/
	
		int recv_retval;			//total received size of message from procedure call 
		struct sockaddr_in client;	//recvfrom will fill this struct
		socklen_t client_address_size = sizeof(client);
			
		if( (recv_retval= recvfrom(self->fd, self->recv_buff->buffer , self->recv_buff->size, 0, (struct sockaddr *)&client, &client_address_size)) <0 ){
			perror("Error while receiving from socket");
			exit(recv_retval);
		
		}
	
	dataBuffer retData={(int8_t*)&client, recv_retval};
	return retData;
}
