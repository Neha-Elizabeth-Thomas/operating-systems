#include<stdio.h>
#include<unistd.h>
//#include<sys/types.h>
#include<sys/wait.h>

void main(){
    int pid;
    pid=fork();

    if(pid>0){
        printf("Parent process started\n");
        wait(NULL);
        printf("Parent process terminated\n");
    }else if(pid==0){
        printf("Process id of child=%d\n",getpid());
        sleep(3);
        printf("Process id of parent=%d\n",getppid());
    }
}
