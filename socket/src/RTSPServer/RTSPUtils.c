//#include "socket-util.h"
#include <string.h>
#include <stdlib.h>
#include "stdint.h"
#include "stdio.h"
#include "RTSPUtils.h"

RTSPUtils* rtsp_utils__new(){
    RTSPUtils* self=calloc(1, sizeof(RTSPUtils));

    self->TOKEN_LIST_MEM_SIZE=8;
    self->TOKEN_MEM_SIZE=64;

    self->TOKEN_LIST=calloc(self->TOKEN_LIST_MEM_SIZE, sizeof(char*));
    self->nextToken=calloc(self->TOKEN_MEM_SIZE+1, sizeof(char));
    /* //have to be 0 by default since we used calloc
    self->NUM_TOKENS=0;
    self->nextTokenLength=0;
    */
    return self;
};

void rtsp_utils__destroy(RTSPUtils** self){
    free( ( (*self)->nextToken ) );
    free( ( (*self)->TOKEN_LIST ) );

    (*self)=NULL;
}

void rtsp_utils__parse(RTSPUtils* self, const char* request, int size){
    
    //uint8_t IN_BODY_SECTION=0;//determine if parsing reached through nody section

    
    for (int32_t idx = 0; idx < size; idx++){

        char nextChar = *(request+idx);
        
        //extract key,value of additional headers
        if(nextChar==':' && self->NUM_TOKENS >3){
            printf("added: %c  paresed until: %s\n",nextChar, self->nextToken);
            *(self->TOKEN_LIST + self->NUM_TOKENS)=calloc(self->nextTokenLength+1, sizeof(char));
            strncpy( *(self->TOKEN_LIST + self->NUM_TOKENS++), self->nextToken, self->nextTokenLength);
            self->nextTokenLength=0;
            //TODO: store as key, value
        }
        //extract next tokens until newline
        else if( nextChar !=' ' && nextChar!='\n' && nextChar!='\r' ){

            *(self->nextToken + self->nextTokenLength++)=nextChar;
            //self->nextTokenLength;
            //printf("added: %c  paresed until: %s\n",nextChar, self->nextToken);
            //realloc token memory area if token size read exceeds the current memory available
            if( self->nextTokenLength +1 > self->TOKEN_MEM_SIZE ){
                self->TOKEN_MEM_SIZE<<=1;//increase by 1 bit
                self->nextToken=realloc(self->nextToken, self->TOKEN_MEM_SIZE+1);
            }

        //newline reached, store tokens and start again
        }else if( (nextChar=' ' || nextChar=='\n') && self->nextTokenLength>0){
            //printf("token ekle:");
            //fwrite(self->nextToken,1,self->nextTokenLength,stdout);
            //printf("  len:%i  buffer:%s\n",self->nextTokenLength, self->nextToken);

            *(self->TOKEN_LIST + self->NUM_TOKENS)=calloc(self->nextTokenLength+1, sizeof(char));
            strncpy( *(self->TOKEN_LIST + self->NUM_TOKENS++), self->nextToken, self->nextTokenLength);
            self->nextTokenLength=0;
            //*(self->TOKEN_LIST + self->NUM_TOKENS++)=self->nextToken;
            //realloc token list memory area if size read exceeds the current memory available
            if( self->NUM_TOKENS+1 > self->TOKEN_LIST_MEM_SIZE ){
                self->TOKEN_LIST_MEM_SIZE<<=1;//increase by 1 bit
                
                self->TOKEN_LIST=realloc(self->TOKEN_LIST, self->TOKEN_LIST_MEM_SIZE * sizeof(char*));
            }

            //if next line is also whitespace
            //that means we reached to body section of request
            if( (request+self->nextTokenLength+1)=='\n' ){
                //IN_BODY_SECTION=1;
                idx+=2;
            }
        }
    }
}

void rtsp_utils__print(RTSPUtils* self){
printf("tokens:%i\n",self->NUM_TOKENS);
    for (size_t i = 0; i < self->NUM_TOKENS; i++)
    {
        printf("token: %s\n", *(self->TOKEN_LIST +i));
    }    
}
/*
int main(int argc, char** argv){
    
    RTSPUtils* u=RTSPUtilsClass.new();
   const char* text=
   "OPTIONS rtsp://example.com/media.mp4 RTSP/1.0\r\n"
   "Host: example.com\r\n"
   "header1: 123\r\n"
   "header2: 456\r\n"
   "\r\n"
   "data\r\n";
    rtsp_utils__parse(u,text, 99);

    rtsp_utils__print(u);
}*/