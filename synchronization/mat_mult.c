#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int A[5][5],B[5][5],C[5][5],m,n,p,q;
int S;
struct indices{
    int i;
    int j;
};
void readMat(int A[][5],int m,int n){
    int i,j;
    printf("Enter the elements of a %dx%d matrix: ",m,n);
    for(i=0 ; i<m ; i++)
        for(j=0 ; j<n ; j++)
            scanf("%d",&A[i][j]);
}

void displayMat(int A[][5],int m,int n){
    int i,j;
    for(i=0 ; i<m ; i++){
        for(j=0 ; j<n ; j++)
            printf("%5d",A[i][j]);
        printf("\n");
    }
}

void* matMult(void* arg){
    int k,sum=0;
    int i=((struct indices*)arg)->i;
    int j=((struct indices*)arg)->j;

    for(k=0 ; k<n ; k++){
        sum+=A[i][k]*B[k][j];
    }

    C[i][j]=sum;

    free(arg);
    return NULL;
}

void main(){
    int i,j;
    pthread_t multThread[5][5];

    printf("Enter the order of 1st matrix: ");
    scanf("%d %d",&m,&n);

    printf("Enter the order of 2nd matrix: ");
    scanf("%d %d",&p,&q);

    if(n!=p){
        printf("INVALID ORDER\n");
        exit(1);
    }

    readMat(A,m,n);
    readMat(B,p,q);

    for(i=0 ; i<m ; i++)
        for(j=0 ; j<q ; j++){
            struct indices* temp=(struct indices*)malloc(sizeof(struct indices));
            temp->i=i;
            temp->j=j;
            pthread_create(&multThread[i][j],NULL,matMult,temp);
        }

    for(i=0 ; i<m ; i++)
        for(j=0 ; j<q ; j++)
            pthread_join(multThread[i][j],NULL);

    printf("Matrix A: \n");
    displayMat(A,m,n);
    printf("Matrix B: \n");
    displayMat(B,p,q);
    printf("Matrix C: \n");
    displayMat(C,m,q);
}
