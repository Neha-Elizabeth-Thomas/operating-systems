#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void* thread1(void* arg){
    int* num=(int*)malloc(sizeof(int));
    *num=9;
    int i;
    for(i=0 ; i<10 ; i++){
        *num+=9;
    }

//    return &num;  you cannot return adderss of a local variable
    //because it will be destroyed
    return num; //dynamically allocated variable //return value of type void*
}

void main(){
    void* result;

    pthread_t t1;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_create(&t1,&attr,thread1,NULL);

    pthread_join(t1,&result); //2nd arg of type void** i.e address of a pointer //void is must

    printf("RESULT=%d\n",*(int*)result);
    free(result);
}
