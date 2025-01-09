#include "RTSPServer.h"
#include <stdlib.h>

RTSPServer* rtsp_server__new(int address, int port){

    RTSPServer* self=calloc( 1, sizeof(RTSPServer) );

    self->super=UDPServerClass.new(address, port);

    return self;
}

void rtsp_server__destroy(RTSPServer** self){

    UDPServerClass.destroy( &( (*self)->super ) );

    free( (*self) );

    (*self)=NULL;
}

RTSPServer* rtsp_server__start(RTSPServer* self){

    //TODO: implement
    for (size_t i = 0; i < 10; i++){
        
        dataBuffer recvd=UDPServerClass.receive( self->super->super );

        //parse info of client to communicate with socket
	    Socket client={ self->super->super->fd, *(struct sockaddr_in *)recvd.buffer, self->super->super->recv_buff, self->super->super->send_buff };

        //ipv4 addr of client
        int32_t addr=client.socket.sin_addr.s_addr;
	
	    printf("Received (%i bytes) message: %s | Domain:%s address:%i.%i.%i.%i\n",recvd.size, (char*)self->super->super->recv_buff->buffer, (client.socket.sin_family == AF_INET?"AF_INET":"UNKNOWN"),
	    (addr&0xff), (addr>>8&0xff), (addr>>16&0xff), addr>>24&0xff);	
    }
    
}

RTSPServer* rtsp_server__join(RTSPServer* self){

    //TODO: implement
}

RTSPServer* rtsp_server__stop(RTSPServer* self){

    //TODO: implement
}