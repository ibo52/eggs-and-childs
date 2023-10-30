/* Halil Ibrahim MUT -- 190315037 
 *Semaphore and Thread usage example on 
 *GNU/Linux system.
 *-----------------------------------------
 * A phone system that have two operators,
 *and one connection wire. When an user tries
 *to communicate with his/her relative, firstly 
 *accessing one of the two operators. Then operator
 *sets the communication line between them.
 *Since there is only one wire, one user 
 *connection set at a time
 */

/* 
 * File:   main.c
 * Author: ibrahim
 *
 * Created on April 8, 2022, 12:27 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include<pthread.h>    //thread library
#include<semaphore.h> //(wire and operators,to share restricted resources)
#include<unistd.h>   // header file for sleep() function
#include<time.h>    //to establish random time seed for srand() function
/*
 * 
 */
//-----declare the semaphores globally-----
sem_t connectionEstablish;
sem_t operators;
//-----declare the semaphores globally-----

void *Users(void *thread_id){
    int id;        		 //id of the user
    id=(int)(thread_id);//on cell operator
    
    sem_wait(&operators);   //user trying to reach operator.
    printf("User #%d reached the operator.\n",id);
    
    sem_wait(&connectionEstablish); //user waits for operator
                                    //to connect s/he to her/his relative
    
    sem_post(&operators); //drop the operator to start phone call.
    
    printf("connection established. #%d is On call...\n",id);
    
    sleep( rand()%3 +1 );//users communicating
    
    printf("User #%d ended the phone call.Now connection wire is free.\n",id);
    
    sem_post(&connectionEstablish); //user ends the call. Drops the wire
    
    pthread_exit( NULL ); //user done. Service ends.
}

int main(int argc, char** argv) {
    srand( time(NULL) );//seeding to obtain random val by current time
    printf("--------Phone Operator--------\n");
    
    //------initialize semaphores-----------
    sem_init(&connectionEstablish,0,1);
    sem_init(&operators,0,2);
    //------initialize semaphores-----------
    
    //thread to simulate users
    int numOfUsers=20;int i;int threadFailed;
    
    pthread_t thread_id[numOfUsers]; //user thread list
    
    for(i=0;i<numOfUsers;i++){
        
        //users accesing the cell Service to make phone calls
        //with (void*)i parameter;we send variable to function that will be threaded
        threadFailed=pthread_create(&thread_id[i],NULL,Users,(void*)i);
        
        if(threadFailed){
            printf("ERROR: thread create failed. RETURN VALUE:#%d\n",threadFailed);
            exit(-1);
        }
    }
    
    for(i=0;i<numOfUsers;i++){
        
        pthread_join(thread_id[i],NULL);//with joining threads, main
    }								   //waits for others to terminate.
    
    //-----close semaphores-----------
    sem_destroy(&operators);
    sem_destroy(&connectionEstablish);
    //-----close semaphores-----------
    printf("\n<<--------Simulation ends-------->>\n");
    //pthread_exit(NULL);
    return (EXIT_SUCCESS);
}

