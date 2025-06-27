#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct message{
    long mtype;
    char msgtext[100];
};

void main(){
    struct message msg;
    key_t key=ftok("myfile.txt",43);
    int msgqid=msgget(key,0666);

    msgrcv(msgqid,&msg,sizeof(msg),1,0);//mtype(identifier for the msg is the only additional parameter)
    //the calling process waits until a message ot mtype 1 arrives in the message queue

    printf("Received message is %s\n",msg.msgtext);

    msgctl(msgqid,IPC_RMID,NULL);
}
