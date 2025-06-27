#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

struct message{
    long mtype;
    char msgtext[100];
};

void main(){
    int n;
    key_t key=ftok("myfile.txt",32);
    int msgqid=msgget(key,0666|IPC_CREAT);

    while(1){
        struct message msg_snd,msg_rcv;

        printf("user0:  ");
        fgets(msg_snd.msgtext,20,stdin);
        n=strcspn(msg_snd.msgtext,"\n");
        msg_snd.msgtext[n]='\0';
        msg_snd.mtype=1;
        msgsnd(msgqid,&msg_snd,sizeof(msg_snd),0);
        if(strcasecmp(msg_snd.msgtext,"stop")==0)
            exit(0);

        msgrcv(msgqid,&msg_rcv,sizeof(msg_rcv),2,0);
        if(strcasecmp(msg_rcv.msgtext,"stop")==0){
            msgctl(msgqid,IPC_RMID,NULL);
            exit(0);
        }
        printf("Got from user1: %s\n\n",msg_rcv.msgtext);
    }
}
