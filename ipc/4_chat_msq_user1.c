#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>

struct message{
    long mtype;
    char msgtext[100];
};

void main(){
    int n;
    key_t key=ftok("myfile.txt",32);  //create key
    int msgqid=msgget(key,0666); //create message queue

    while(1){
        struct message msg_snd,msg_rcv;

        msgrcv(msgqid,&msg_rcv,sizeof(msg_rcv),1,0);//receive message
        if(strcasecmp(msg_rcv.msgtext,"stop")==0){
            msgctl(msgqid,IPC_RMID,NULL);
            exit(1);
        }
        printf("Got from user0: %s\n\n",msg_rcv.msgtext);

        msg_snd.mtype=2;
        printf("user1: ");
        fgets(msg_snd.msgtext,20,stdin);// take i/p from user.fgets stops reading  when new line is encountered.last char='\n'
        n=strcspn(msg_snd.msgtext,"\n");//search for the no of char before '\n'
        msg_snd.msgtext[n]='\0';        //replace '\n' with '\0'.to make it a string
        msgsnd(msgqid,&msg_snd,sizeof(msg_snd),0); //SEND message
        if(strcasecmp(msg_snd.msgtext,"stop")==0)
            exit(0);
    }
}
