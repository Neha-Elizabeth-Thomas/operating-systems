#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

void* myturn(void* arg){
    int i;
    int* ptr=(int*)arg;
    int* new=(int*)malloc(sizeof(int));
    *new=8;
    for(i=0 ; i<10 ; i++){
        printf("myturn |ptr=%d\n",*ptr);
        (*ptr)++;
        (*new)++;
        sleep(1);
    }
    return new;
}


void yourturn(){
    int i;
    for(i=0 ; i<3 ; i++){
        printf("your turn\n");
        sleep(2);
    }
}

void main(){
    pthread_t mythread;
    int num=11;
    void* result;

    pthread_create(&mythread,NULL,myturn,&num);
    yourturn();
    
    pthread_join(mythread,&result);
    printf("value of num after thread=%d\n",num);
    printf("result=%d\n",*((int*)result));
}
