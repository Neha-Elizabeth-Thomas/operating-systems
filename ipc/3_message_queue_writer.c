#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct message{
    long mtype;//identifier for the msg
    char msgtext[100];
};

void main(){
    struct message msg;
    key_t key=ftok("myfile.txt",43);
    int msgqid=msgget(key,0666|IPC_CREAT);  //create the message queue

    printf("Enter a line of text: ");
    scanf(" %[^\n]",msg.msgtext);

    msg.mtype=1;

    msgsnd(msgqid,&msg,sizeof(msg),0);

    printf("Message send to message queue is %s\n",msg.msgtext);
}
