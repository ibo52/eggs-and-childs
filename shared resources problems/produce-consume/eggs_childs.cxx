/*
       The producer/consumer problem  ->SHARED MEM OKUYAMIYORUM
 */
#include <iostream>                    // Section ONE
#include <cstdio>
#include <time.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define BUFFER "./buffer"

#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
                              // definition in <sys/sem.h>
#else
union semun {                 // We define:
  int val;                    // value  for SETVAL
  struct semid_ds *buf;       // buffer for IPC_STAT, IPC_SET
  unsigned short int *array;  // array  for GETALL, SETALL
  struct seminfo *__buf;      // buffer for IPC_INFO
};
#endif
using namespace std;

void showEggList(char* a){

	printf("[");
	for(int w=0;w< sizeof(a)/sizeof(a[0]) ;a++){
		printf("%c ",a[w]);
	}
	printf("]\n");
}
int
main(int argc, char *argv[ ]) {
  	//shared mem----------------------- for placing eggs
  	key_t shmkey=ftok(".",'x');
  	int shmid;char *memBuff,*eggHolder;int holderLength=10;
  	
  	//create shared memory location with shmkey
  	if ((shmid=shmget(shmkey,holderLength,IPC_CREAT|0660))< 0) {
    	perror("shmget fail");
    	return 1;
   }
   //attach the char array to that shared memory location
	if ((memBuff = (char *)shmat(shmid, 0, 0)) == (char *) -1) {
    	perror("shmat : parent");
    	return 2;
   }
   eggHolder=memBuff;//char array for accessing egg holder
   int i;
   
  	for(i=0;i<holderLength;i++){
  		*(eggHolder+i) ='_';
  	}
  	//shared mem----------------------- for placing eggs
  
	static struct sembuf acquire = {0, -1, SEM_UNDO},//acces semaphore values
                       release = {0,  1, SEM_UNDO};//release semaphore values
	pid_t           c_pid;
	key_t           ipc_key;
  	static unsigned short   semaphores_start_val[2] = {1, 0};//means chicken access first and place some egg as semafor initial value
  	int             semid, producer = 0, n, p_sleep, c_sleep;
  	union semun     arg;
  	enum { PUT, EAT };//values-> put==change sem->0, sem->1
  	if (argc != 2) {
    	cerr << argv[0] <<  " sleep_time" << endl;
    return 1;
  }
  
  	ipc_key = ftok(".", 'S');
  	//create semaphore with ipc_key
  	if ((semid=semget(ipc_key, 2, IPC_CREAT|IPC_EXCL|0660)) != -1) {
  		producer = 1;
    	arg.array = semaphores_start_val;
    //set the initial values of sempahore
    if (semctl(semid, 0, SETALL, arg) == -1) {
    	perror("semctl -- producer -- initialization");
    	return 2;
    }
    //if you are consumer; access the semaphore location to use later
  } else if ((semid = semget(ipc_key, 2, 0)) == -1) {
    	perror("semget -- consumer -- obtaining semaphore");
    	return 3;
  }
	cout << (producer==1 ? "Chicken" : "Childs" ) << " starting" << endl;
  
	
  	cout<<"init holder: "<<memBuff<<endl;
  	srand( time(0) ); //seed the random function with current time to obtain arbitrary random values
  	
	switch (producer) {
  		case 1:{
  			p_sleep = atoi(argv[1]);
  			sleep(p_sleep);
  			int idx=0;//last index of placed eggs
  			int nEggs=0;
  			for(int o=0;o<10;o++){
  			int eggs=random()%5 +1;
  			nEggs+=eggs;
  			cout<<"chickens gave "<<eggs<<" eggs"<<endl;
  		
  			acquire.sem_num=PUT;//try to access semaphore
  			if( semop(semid,&acquire,1)==-1 ){
  				perror("semop acquire:");
  			}
  			int toWhere=idx+nEggs;
  			for(int i=idx;i<toWhere;i++){
  				if(*(eggHolder+idx)=='_'){
  					*(eggHolder+idx)='*';
  					idx=(idx+1) % (holderLength);
  					nEggs--;
  				}
  				else{
  					cout<<"No space.There is"<<nEggs<<" to be placed"<<endl;
  					break;}
  			}
  					
  			cout<<"some eggs placed.There is"<<nEggs<<" to be placed"<<endl;
  			cout<<"holder: "<<memBuff<<endl;
  			sleep(p_sleep);
  			release.sem_num=EAT;//release semaphore for others to access
  			if( semop(semid,&release,1)==-1 ){
  				perror("semop acquire:");
  			}
  			
  			}
  			if (semctl(semid, 0, IPC_RMID, 0) == -1) {
      			perror("semctl -- producer");
      			return 7;
    		}
    		
    		//program finished. Close shared resources
    		cout << "Semaphore removed" << endl;
    		shmdt(memBuff);
     		shmctl(shmid, IPC_RMID, (struct shmid_ds *) 0);
     		cout<<"shared mem removed"<<endl;
  			break;}
  		
  		case 0:{
  			int c_idx=0;
  			c_sleep = atoi(argv[1]);
  			c_pid = getpid();
  			int eated=0;
  			while (1){
  				sleep(c_sleep);
  				int willEat=random()%5 +1;
  				acquire.sem_num=EAT;
  				if( semop(semid,&acquire,1)==-1 ){
  					perror("child acquire:");return 8;
  				}
  				
  				cout<<"child wants to eat "<<willEat<<" eggs + "<<eated<<" from before.looks the egg holder"<<endl;
  				cout<<"holder: "<<memBuff<<endl;
  				eated+=willEat;
  				for(int f=c_idx;f<c_idx+eated;f++){
  					if( *(eggHolder+f)=='*'){
  						*(eggHolder+f)='_';
  						c_idx=(c_idx+1) % holderLength;
  						eated--;
  					}
  					else{
  					cout<<"There is no eggs to eat."<<endl;break;}
  				}
  				cout<<"child eated "<<willEat-eated<<" eggs and gone:"<<endl;
  				cout<<"holder: "<<memBuff<<endl;
  				sleep(c_sleep);
  				
  				release.sem_num=PUT;//release semaphore
  				if( semop(semid,&release,1)==-1 ){
  					perror("child release:");return 10;
  				}
  				
  			}
  	}
  	}
	return 0;
}
