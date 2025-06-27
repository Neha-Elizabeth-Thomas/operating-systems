#define NIL 999
#define SIZE 4
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

int S=1,E=SIZE,F=0;

int arr[SIZE],n=SIZE;

void wait(int* S){
    while(*S<=0);
    (*S)--;
}

void signal(int* S){
    (*S)++;
}

void display(){
    int i;
    for(i=0 ; i<n ; i++)
        if(arr[i]==NIL)
            printf(" _ ");
        else
            printf(" %d ",arr[i]);
    printf("\n\n");
}

void* producer(void* arg){
    int i,j;
    for(i=0 ; i<10 ; i++){
        wait(&E);
        wait(&S);

        srand(time(0));
        for(j=0 ; j<n ; j++)
            if(arr[j]==NIL){
                arr[j]=rand()%1000;
                break;
            }
        printf("PUT:  ");
        display();
        sleep(3);
        
        signal(&S);
        signal(&F);
    }
    return NULL;
}

void* consumer(void* arg){
    int i,j;
    for(i= 0 ; i<10 ; i++){
        wait(&F);
        wait(&S);

//        printf("GET %d from %d\n\n",arr[j],j);
        printf("GET: ");
        for(j=0 ; j<n ; j++)
            if(arr[j]!=NIL){
                arr[j]=NIL;
                break;
            }
        display();
        sleep(3);

        signal(&S); 
        signal(&E);
    }
    return NULL;
}

void main(){
    pthread_t p,c;
    int i;
    for(i=0 ; i<n ; i++)
        arr[i]=NIL;

    pthread_create(&p,NULL,producer,NULL);
    pthread_create(&c,NULL,consumer,NULL);

    pthread_join(p,NULL);
    pthread_join(c,NULL);
}
