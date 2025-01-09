#include "stddef.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include<unistd.h>//sleep
#include<errno.h>
#include "CameraServer.h"
static void camera_server__streamVideo(CameraServer* self, Socket client);

CameraServer* camera_server__new(int address, int port, const char* cameraPath){

    CameraServer* self=calloc(1, sizeof(CameraServer));

    self->server= RTPServerClass.new(address, port);

    self->camera = CameraClass.new(cameraPath);


    sock_util__dealloc_buffer(&(self->server->super->super->send_buff) );
	self->server->super->super->send_buff = sock_util__alloc_buffer( 1280*720*3 );

    return self;
}

void camera_server__destroy(CameraServer** self){

    CameraClass.destroy( &((*self)->camera) );

    RTPServerClass.destroy( &((*self)->server) );

    free( (*self) );
    (*self)=NULL;
}

static void *camera_server__listen(void* argument){

	CameraServer* self=argument;
	CameraClass.activate(self->camera);

    //listen for a client
    //recv.buffer: holds *(struct sockaddr_in*) socket data of incoming request,
	//recv.size	 : holds received message length)
	//1. client request came to server
	dataBuffer recvd=RTPServerClass.receive(self->server);//sock_util__receive__socket(self->super);
	//parse info of client to communicate with socket
	Socket client={ self->server->super->super->fd, *(struct sockaddr_in *)recvd.buffer, self->server->super->super->recv_buff, self->server->super->super->send_buff };

	int addr=client.socket.sin_addr.s_addr;
	
	printf("Received (%i bytes) message: %s | Domain:%s address:%i.%i.%i.%i\n",recvd.size, (char*)self->server->super->super->recv_buff->buffer, (client.socket.sin_family == AF_INET?"AF_INET":"UNKNOWN"),
	(addr&0xff), (addr>>8&0xff), (addr>>16&0xff), addr>>24&0xff);	

	//camera access
	//printf("Streaming #live frame");
	for(int i=0;  ; i++){
		//printf("Streaming #%i. frame",i);
		camera_server__streamVideo(self, client);

		//delay time for 30 FPS
		/*uint8_t FPS=30;
		struct timespec ts;ts.tv_nsec=1000000000/FPS;int res;
		do {
        res = nanosleep(&ts, &ts);
    	} while (res && errno == EINTR);*/
	}
	free(recvd.buffer);
	//conection close request(raw data)
	
	sock_util__buffer_write(client.send_buff, "SOCK_CLOSE_REQUEST");
	RTPServerClass.send(/*self->rtp_header,*/ &client);

	pthread_exit(NULL);

}

int camera_server__start(CameraServer* self){

	return pthread_create( &(self->listenerThread), NULL, camera_server__listen, self);

}

int camera_server__join(CameraServer* self){
	
	void *retval;
	pthread_join( self->listenerThread, &retval);

	return (int)(retval);
}

int camera_server__stop(CameraServer* self){

	return pthread_cancel( self->listenerThread );
}

static void camera_server__streamVideo(CameraServer* self, Socket client){
	//capture camera data
	cameraBuffer camBuff=CameraClass.capture(self->camera, V4L2_PIX_FMT_JPEG);
	
	//prepare acknowledgement data to send back
	printf("[cam buff] lenght: %i\n",camBuff.length);

	//write video data to socket buffer
	sock_util__buffer_write_sizei(client.send_buff, camBuff.address, camBuff.length);

	//send data through socket(RTP packets)
	RTPServerClass.sendRTP(self->server,	&client);
	
	//dataBuffer sent=self->vtable->send(&client);//sock_util__send__socket(&client);
	//printf("Sent (%i bytes) message: %s\n", sent.size, (char*)client.send_buff->buffer);
	printf("camera buffer streamed to client\n");

}
