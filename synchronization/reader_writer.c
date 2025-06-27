#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int mutex=1,rw_mutex=1,read_count=0;

void wait(int* S){
    while(*S<=0);
    (*S)--;
}

void signal(int* S){
    (*S)++;
}

void* reader(void* arg){
    int num=*((int*)arg);
    printf("reader%d is trying to enter\n\n",num);
    
    wait(&mutex);
    read_count++;
    if(read_count==1)
        wait(&rw_mutex);
    signal(&mutex);

    printf("Reader %d is reading\nread_count=%d\n\n",num,read_count);
    sleep(3);

    wait(&mutex);
    read_count--;
    if(read_count==0){
        printf("Reader %d is outside\nread_count=%d\n\n",num,read_count);
        signal(&rw_mutex);
    }else
        printf("Reader %d is outside\nread_count=%d\n\n",num,read_count);
    signal(&mutex);
    free(arg);
    return NULL;
}

void* writer(void* arg){
    int *num=(int*)arg;
    printf("Writer %d is trying to enter\n\n",*num);

    wait(&rw_mutex);

    printf("writer %d is inside\n\n",*num);
    sleep(3);

    printf("Writer %d outside\n\n",*num);   
    sleep(0.5);
    signal(&rw_mutex);
    free(num);
    return NULL;
}

void main(){
    int r,w,i;
    pthread_t read[20],write[20];

    printf("How many readers?");
    scanf("%d",&r);
    printf("How many writers?");
    scanf("%d",&w);

    for(i=0 ; i<r ; i++){
        int* num=(int*)malloc(sizeof(int));
        *num=i;
        pthread_create(&read[i],NULL,reader,num);
    }
    for(i=0 ; i<w ; i++){
        int* num=(int*)malloc(sizeof(int));
        *num=i;
        pthread_create(&write[i],NULL,writer,num);
    }

    for(i=0 ; i<r ; i++)
        pthread_join(read[i],NULL);
    for(i=0 ; i<w ; i++)
        pthread_join(write[i],NULL);
}
