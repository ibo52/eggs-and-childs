//#include "socket-util.h"
#include <string.h>
#include <stdlib.h>
#include "stdint.h"
#include "stdio.h"

/*
int RTSPParser(dataBuffer* incoming){
    char** parsed=calloc(3, sizeof(char*));

    char INDEX_PARSED=0;//index of which save substring to variable 'parsed': RTSP expects 3 substring: OPTION + link + PROTOCOL
    int32_t substrIdx=0;//index of the substings to be extracted

    char* buffer = incoming->buffer;

    for(int32_t index=0; index < incoming->size & INDEX_PARSED<2; index++){

        if( buffer[index] == ' ' ){

            parsed[INDEX_PARSED] = calloc(index-substrIdx + 1, sizeof(char));//+1 for string escape char(/0)
            
            memcpy(parsed[INDEX_PARSED++] , *(buffer+substrIdx), index-substrIdx);

            substrIdx=index+1;
        }
    }

    printf("PARSED: option:%s link:%s protocol:%s", parsed[0], parsed[1], parsed[2]);
    return 0;
}
*/


int RTSPParser2(const char* incoming, int size){
    char** parsed=calloc(3, sizeof(char*));

    char INDEX_PARSED=0;//index of which save substring to variable 'parsed': RTSP expects 3 substring: OPTION + link + PROTOCOL
    int32_t substrIdx=0;//index of the substings to be extracted

    char* buffer = incoming;

    int32_t index=0;
    for(; index <= size & INDEX_PARSED<=3; index++){

        if( buffer[index] == ' ' ){

            parsed[INDEX_PARSED] = calloc(index-substrIdx + 1, sizeof(char));//+1 for string escape char(/0)
            
            memcpy(parsed[INDEX_PARSED] , (buffer+substrIdx), index-substrIdx);
            
            substrIdx=index+1;//skip empty char(' ')
            INDEX_PARSED++;

        }
    }

    printf("PARSED: option:%s\nlink:%s\nprotocol:%s\n", parsed[0], parsed[1], parsed[2]);
    return 0;
}

int RTSPParser3(const char* incoming, int size){
    char** BASE=calloc(3, sizeof(char*));
    BASE[0]=calloc(16, sizeof(char));//option
    BASE[1]=calloc(512, sizeof(char));//target link
    BASE[2]=calloc(16, sizeof(char));//protocol/version

    int8_t retval=sscanf(incoming, "%s %s %s", BASE[0], BASE[1], BASE[2]);

    char* buffer=calloc(size+1, sizeof(char));
    memcpy(buffer, incoming, size);
    for (char* token = strchr(buffer, '\n'); token; token = strchr(NULL, '\n')){

        printf("ke:%s\n",token);
    }

    if( retval < 3 ){
        printf("Could not found required base fields. Invalid request\n");
        return -1;
    }
    
    printf("PARSED: option:%s\nlink:%s\nprotocol:%s\n", BASE[0], BASE[1], BASE[2]);

    return 0;
}

int main(int argc, char* argv){
    
    /*
    dataBuffer* b=sock_util__alloc_buffer(1024);
    sock_util__buffer_write(b, "OPTIONS rtsp://example.com/media.mp4 RTSP/1.0");
    */
    RTSPParser3("OPTIONS rtsp://example.com/media.mp4 RTSP/1.0\nHost: example.com\n", 62);


    char* a="string1\0string2\0string3\0";
    printf("\n1:%s\n2:%s\n3:%s\n", a, (a+8), (a+16));
}