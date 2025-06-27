#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#define PhNUM 5 //make it 4
#define ChNUM 5

int chopstick[ChNUM]={1,1,1,1,1};
int ch_available[ChNUM]={1,1,1,1,1};

void wait(int* S){
    while(*S<=0);
    (*S)--;
}

void signal(int* S){
    (*S)++;
}

void* philosopher(void* arg){
    int i=*(int*)arg;
    int j;
    for(j=0 ; j<1 ;j++){
        printf("Philosopher %d is thinking\n",i);

        while(chopstick[i]==0 || chopstick[(i+1)%ChNUM]==0);
        wait(&chopstick[i]);
        wait(&chopstick[(i+1)%ChNUM]);

/*        if(i%2==0){
            wait(&chopstick[i]);
            wait(&chopstick[(i+1)%ChNUM]);
        }else{
            wait(&chopstick[(i+1)%ChNUM]);
            wait(&chopstick[i]);
        }*/
        

        sleep(0.1);
        printf("philosopher%d is eating\n",i);
        sleep(2);

        signal(&chopstick[i]);
        signal(&chopstick[(i+1)%ChNUM]);
    
        printf("philosopher%d finished eating\n",i);
    }
    free(arg);
    return NULL;
}

void main(){
    pthread_t phil[PhNUM];
    int i;
    for(i=0 ; i<PhNUM ; i++){
        int * num=(int*)malloc(sizeof(int));
        *num=i;
        pthread_create(&phil[i],NULL,philosopher,num);
    }

    for(i=0 ; i<PhNUM ; i++)
        pthread_join(phil[i],NULL);
}
