#include<stdlib.h>
#include <stdio.h>

#include "RTP.h"

int main(int argc, char** argv){
	printf("Test for RTP class\n\n");
	
	RTP* self=rtp__new();
	
	rtp__toString(self);
	
	rtp__destroy(&self);
	
	printf("\nTest for RTP class done\n");
	return 0;
}
