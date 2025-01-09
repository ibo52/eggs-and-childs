#include "CameraServer.h"
#include <stdio.h>

int main(int argc, char** argv){
    CameraServer* srv=camera_server__new(INADDR_ANY, UDP_PORT, "/dev/video0");

    camera_server__start(srv);
    
    camera_server__join(srv);
    
    camera_server__destroy(&srv);
    

    return 0;
}