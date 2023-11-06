/*
*		Simple TCP Server to send Video data of camera
*		through socket
*/
#include<stdio.h>
#include<stdlib.h>

#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close(), sleep
#include<errno.h>
#include<netinet/in.h>
#include<string.h>
#include<pthread.h>

#include "TCPServer.h"
#include "Socket.h"
//---thread functions--------------------
static void* client_handler(void* argument);
static void* tcp_server__starter_task(void* argument);
//---thread functions--------------------

TCPServer* tcp_server__new(int addr, int port){

	Socket* super = socket__new(addr, port, CONN_TYPE_TCP_SERVER );
	
	TCPServer* self=calloc(1, sizeof(TCPServer));
	self->super=super;

	return self;
}

void tcp_server__destroy(TCPServer** self){
	
	//(*self)->super->vtable->destroy( (*self)->super );
	socket__destroy( &((*self)->super) );
	free( (*self) );
	(*self)=NULL;
	printf("TCPServer object destructed\n");
}

void tcp_server__start(TCPServer* self){

	pthread_t starter_id;
    pthread_create(&starter_id, NULL, tcp_server__starter_task, self);
    self->starter_thread=starter_id;
    
	//listen for incoming connecitons
}

void tcp_server__join(TCPServer* self){
		pthread_join(self->starter_thread, NULL);
}

/*
void tcp_server__stop(TCPServer* self){
		pthread_cancel(self->starter_thread, NULL);
}
*/

static void* client_handler(void* argument){
	
	TCPServer* self=argument;

	struct sockaddr_in client;
	socklen_t client_len=sizeof(client);
	int client_fd;
    //accept incoming connection
    if( ( client_fd = accept(self->super->fd, (struct sockaddr*)&client, &client_len) )<0 ){
        perror("Error while accepting incoming connection");
        exit(errno);
    }
    
    int rAddr=client.sin_addr.s_addr;
    fprintf(stdout, "connected: %i.%i.%i.%i\n",((rAddr)&0xff), ((rAddr<<8)&0xff), ((rAddr<<16)&0xff), ((rAddr<<24)&0xff));
    
    int i;
    for(i=0; i<1; i++){
		//int recv_size=0, send_size=0;
    	
    	int recv_size=sock_util__receive(client_fd, self->super->recv_buff, self->super->recv_buff->max_size);
    	
    	//sock_util__receive__socket(self->super);
    	
    	fprintf(stdout, "incoming (%i bytes) from client: %s\n", recv_size, self->super->recv_buff->buffer);
    	
    	strcat((char*)self->super->recv_buff->buffer, " ACKNOWLEDGED.");
    	
    	sock_util__send(client_fd, self->super->recv_buff, strlen((char*)self->super->recv_buff->buffer));
    	
    	//sock_util__send__socket(self->super);
    	//strcpy((char*)self->send_buff->buffer, (char*)self->recv_buff->buffer);
    	//sock_util__send__server(self);
	}
	
	
	fprintf(stdout, "client Done. Exiting. \n");
	
	pthread_exit( NULL );
}

static void* tcp_server__starter_task(void* argument){

	TCPServer* self=argument;
	
	if( listen(self->super->fd, MAX_ALLOWED_CONN)<0 ){
        perror("Error while listening for incoming connections");
        exit(errno);
    }
    
    pthread_t accept_cli_id;
    pthread_create(&accept_cli_id, NULL, client_handler, self);
    pthread_join(accept_cli_id, NULL);
    pthread_exit(NULL);
	
}
