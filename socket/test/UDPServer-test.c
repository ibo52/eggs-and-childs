#include<stdio.h>
#include<stdlib.h>

#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close(), sleep
#include<errno.h>
#include<netinet/in.h>
#include<string.h>

#include "socket-util.h"
#include "UDPServer.h"
#include "Socket.h"

static void start(UDPServer* self){
	//recv.buffer: holds *(struct sockaddr_in*) socket data of incoming request,
	//recv.size	 : holds received message length)
	dataBuffer recvd=sock_util__receive__socket(self->super);

	//to communicate with socket that reach server
	Socket client={ self->super->fd, *(struct sockaddr_in *)recvd.buffer, self->super->recv_buff, self->super->send_buff };

	int addr=client.socket.sin_addr.s_addr;
	
	printf("Received (%i bytes) message: %s | Domain:%s address:%i.%i.%i.%i\n",recvd.size, (char*)self->super->recv_buff->buffer, (client.socket.sin_family == AF_INET?"AF_INET":"UNKNOWN"),
	(addr&0xff), (addr>>8&0xff), (addr>>16&0xff), addr>>24&0xff);	
	
	//prepare acknowledgement data to send back
	sock_util__buffer_write(client.send_buff, (char*)self->super->recv_buff->buffer);
	sock_util__buffer_append(client.send_buff, "ACKNOWLEDGED.");
	
	dataBuffer sent=sock_util__send__socket(&client);
	printf("Sent (%i bytes) message: %s\n", sent.size, (char*)client.send_buff->buffer);
	
	free(recvd.buffer);
}

//Driver program
int main(int argc, char** argv){
	UDPServer* server=udp_server__new(INADDR_ANY, UDP_PORT);
	
	printf("UDP Server started. Waiting for a connection.\n");
	
	start(server);
	
	udp_server__destroy(&server);
	
	return 0;
}

