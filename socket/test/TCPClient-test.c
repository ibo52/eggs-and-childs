#include<stdio.h>
#include<stdlib.h>
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close()
#include<errno.h>
#include<netinet/in.h>
#include<string.h>

#include "TCPClient.h"

static void start(TCPClient* self){

    int i;
	for(i=0; i<1; i++){

		sock_util__buffer_write(self->super->send_buff,"hello from TCP client");

		dataBuffer sent=self->vtable->send( self->super );
    	//int sent=sock_util__send(self->super->fd, self->super->send_buff, self->super->recv_buff->size );
    	
    	printf("Sent:%i bytes of %s\n", sent.size, (char*)self->super->send_buff->buffer);
    	
    	dataBuffer recv=self->vtable->receive( self->super );
    	printf("Incoming (%i bytes)from server: %s\n", recv.size, (char*)self->super->recv_buff->buffer);
	}
}

// Driver Program
int main (int argc, char** argv){
	TCPClient* cli=tcp_client__new(INADDR_LOOPBACK, TCP_PORT);
	
	printf("TCP Client starting to send a message to the connection.\n");
	//tcp_client__start(cli);
	start(cli);
			
	tcp_client__destroy(&cli);
	return 0;
}

