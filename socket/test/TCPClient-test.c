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

		strcpy((char* )self->super->send_buff->buffer,"hello from client");

		sock_util__send__socket( self->super );
    	//fprintf(stdout,"sent:%i bytes of %s\n", send_size, self->super->send_buff->buffer);
    	
    	dataBuffer recv=sock_util__receive__socket( self->super );
    	fprintf(stdout,"incoming (%i bytes)from server: %s\n", recv.size, self->super->recv_buff->buffer);
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

