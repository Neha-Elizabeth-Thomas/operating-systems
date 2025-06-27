#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#define nph 5
#define nch 5
sem_t chopstick[nch];

void* philosopher(void* arg){
    int num=*((int*)arg);

    for(int i=0 ; i<1 ; i++){
        printf("Philosopher%d is thinking\n\n",num);

        while(chopstick[num])
        sem_wait(&chopstick[num]);
        sem_wait(&chopstick[(num+1)%nch]);

        sleep(0.5);
        printf("Philosopher%d is eating\n\n",num);
        sleep(3);
        printf("Philosopher%d finished eating\n\n",num);

        sem_post(&chopstick[num]);
        sem_post(&chopstick[(num+1)%nch]);
    }

    free(arg);
    pthread_exit(NULL);
}

void main(){
    pthread_t phil[nph];
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    for(int i=0 ; i<nch ; i++)
        sem_init(&chopstick[i],0,1);

    for(int i=0 ; i<nph ; i++){
        int* num=(int*)malloc(sizeof(int));
        *num=i;
        pthread_create(&phil[i],&attr,philosopher,num);
    }

    for(int i=0 ; i<nph ; i++)
        pthread_join(phil[i],NULL);

    for(int i=0 ; i<nch ; i++)
        sem_destroy(&chopstick[i]);
}
