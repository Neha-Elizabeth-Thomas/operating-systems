#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>

void main(){
    char buf[100];
    void* shared_memory;
    int shmid=shmget((key_t)624,1024,0666|IPC_CREAT);
    printf("Identifier of shared memory is %d\n",shmid);
    
    shared_memory=shmat(shmid,NULL,0);
    printf("process attached at %p\n",shared_memory);

    puts("Enter the data to write into shared memory: ");

    read(0,buf,100);

    strcpy(shared_memory,buf);
    printf("You wrote \"%s\"\n",(char*)shared_memory);

    shmdt(shared_memory);
//    shmctl(shmid,IPC_RMID,NULL);
}
