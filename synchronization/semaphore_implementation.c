#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

int semaphore=1;
int thread_no=1;

void wait(){
    while(semaphore<=0);
    semaphore--;
}

void signal(){
    semaphore++;
}

void *display(void* arg){
    int num=(*(int*)arg);
    int no=num;
    while(1){
        wait();
        if(thread_no==num){
            printf("From thread %d=> %d\n\n",num,no);
            no+=2;
            thread_no=3-thread_no;
            sleep(1);
        }
        signal();
    }
    pthread_exit(NULL);
}

void main(){
    pthread_t t1,t2;
    int odd=1,even=2;
    pthread_create(&t1,NULL,(void *)display,&odd);
    pthread_create(&t2,NULL,(void *)display,&even);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
}

