#include<stdio.h>
#include<unistd.h>
//#include<sys/types.h>
#include<sys/wait.h>

void main(int argc,char* argv[]){
    int pid;
    pid=fork();
    
    if(pid>0){
        printf("Parent process started\n");
        wait(NULL); 
        printf("Parent process terminated\n");
    }else if(pid==0){
        execlp("./add","addition",(char*)NULL);
    }
}


