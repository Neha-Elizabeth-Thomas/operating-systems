#include<stdio.h>
#include<unistd.h>

void main(){
    fork();
    fork();
    fork();
    printf("Helo world\n");
    printf("Process id=%d\n",getpid());
    printf("Parent process id=%d\n\n",getppid());
}
