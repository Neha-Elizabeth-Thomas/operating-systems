#include<unistd.h>
#include<stdio.h>

void main(){
    int pid;
    int i;

    for(i=0 ; i<2 ; i++)
        pid=fork();
    printf("forked.\n");
   
}
