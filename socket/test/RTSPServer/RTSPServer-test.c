#include "RTSPServer.h"
#include <stdio.h>

int main(int argc, char** argv){

    RTSPServer* srv=RTSPServerClass.new(INADDR_ANY, 50007);

    printf("object intiializide\n");
    RTSPServerClass.start(srv);
    printf("object start\n");

    RTSPServerClass.join(srv);
    
    RTSPServerClass.stop(srv);

    printf("done\n");

    RTSPServerClass.destroy(&srv);

    printf("exit\n");
}