#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<stdlib.h>

struct area{
    int turn;
    int flag[2];
    char msg[20];
    int first;
};

void main(){
    int shmid;
    struct area* shared_ptr;
    key_t key=ftok("myfile.txt",543);
    shmid=shmget(key,sizeof(struct area),0666|IPC_CREAT);
    shared_ptr=(struct area*)shmat(shmid,NULL,0);
    shared_ptr->first=1;
    
    while(1){
        char buf[50];
        int n;
        shared_ptr->turn=1;
        shared_ptr->flag[0]=1;
        while(shared_ptr->turn==1 && shared_ptr->flag[1]==1);

        if(!shared_ptr->first)
            printf("Get from user1: %s\n",shared_ptr->msg);
        if(strcasecmp(shared_ptr->msg,"stop")==0){
            shmdt(shared_ptr);
            shmctl(shmid,IPC_RMID,NULL);
            exit(0);
        }
        shared_ptr->first=0;

        printf("User0: ");
        fgets(buf,50,stdin);
        n=strcspn(buf,"\n");
        buf[n]='\0';
        strcpy(shared_ptr->msg,buf);
        if(strcasecmp(shared_ptr->msg,"stop")==0){  
            shared_ptr->flag[0]=1;
            shmdt(shared_ptr);
            exit(0);
        }

        shared_ptr->flag[0]=0;
    }
}
