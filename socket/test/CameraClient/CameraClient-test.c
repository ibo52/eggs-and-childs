#include "CameraClient.h"

int main(int argc, char** argv){
    CameraClient* cli=camera_client__new(INADDR_ANY, UDP_PORT);

    camera_client__start(cli);

    return 0;
}