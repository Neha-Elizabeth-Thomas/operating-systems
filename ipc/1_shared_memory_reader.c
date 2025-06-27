#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>

void main(){
    char* shared_str;
    int shmid=shmget((key_t)624,1024,0666);
    printf("Identifier of shared memory is %d\n",shmid);

    shared_str=(char*)shmat(shmid,NULL,0);

    printf("DATA written by writer is %s\n",shared_str);

    shmdt(shared_str);
    shmctl(shmid,IPC_RMID,NULL);
}
    

