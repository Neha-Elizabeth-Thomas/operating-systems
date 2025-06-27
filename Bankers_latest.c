#include<stdio.h>
#include<stdlib.h>

int n,m,max[10][10],allocation[10][10],available[10],need[10][10],work[10],finish[10],request[10],p;

int Bankers_safety(){
    int i,j,count,safe_seq[10],k=0;

    for(i=0 ; i<n ; i++)
        finish[i]=0;

    for(j=0 ; j<m ; j++)
        work[j]=available[j];

    i=0;
    count=0;
    while(count<n){
        int req_meet=1;
        if(finish[i])
            req_meet=0;
        for(j=0 ; j<m ; j++)
            if(need[i][j]>work[j]){
                req_meet=0;
                break;
            }

        if(req_meet){
            finish[i]=1;
            for(j=0 ; j<m ; j++)
                work[j]+=allocation[i][j];
            safe_seq[k++]=i;
            i=(i+1)%n;
            count=0;            
        }else{
            count++;
            i=(i+1)%n;
        }
    }
    for(i=0 ; i<n ; i++)
        if(finish[i]==0)
            break;
    if(i==n){
        printf("The system is in safe state\n");
        printf("Safe sequence: ");
        for(j=0 ; j<k ; j++)
            printf("P%d  ",safe_seq[j]);
        printf("\n");
        return 1;
    }else{
        printf("The system is in unsafe state\n");
        return 0;
    }
}

void resource_request(){
    int i,j;
    printf("Wich process is requesting ? ");
    scanf("%d",&p);

    printf("Enter its request: ");
    for(j=0 ; j<m ; j++)
        scanf("%d",&request[j]);

    for(j=0 ; j<m ; j++)
        if(request[j]>need[p][j])
        {
            printf("Exceeded max request\n");
            exit(1);
        }

    for(j=0 ; j<m ; j++)
        if(request[j]>available[j]){
            printf("Process %d has to wait\n",p);
            exit(1);
        }

    for(j=0 ; j<m ; j++){
        available[j]-=request[j];
        allocation[p][j]+=request[j];
        need[p][j]-=request[j];
    }

    if(!Bankers_safety()){
        available[j]+=request[j];
        allocation[p][j]-=request[j];
        need[p][j]+=request[j];
        printf("The request cannot be granted.The resource allocation state is restored\n");
    }else{
        printf("The request can be granted\n");
    }
}

void main(){
    int i,j;
    printf("How many processes? ");
    scanf("%d",&n);
    printf("How many resource types: ");
    scanf("%d",&m);

    printf("Enter the %dx%d max matrix(max requirement of each of the processes):\n",n,m);
    for(i=0 ; i<n ; i++)
        for(j=0 ; j<m ; j++)
            scanf("%d",&max[i][j]);

    printf("Enter the %dx%d allocation matrix: \n",n,m);
    for(i=0 ; i<n ; i++)
        for(j=0 ; j<m ; j++)
            scanf("%d",&allocation[i][j]);

    printf("Enter the available matrix: \n");
    for(j=0 ; j<m ; j++)
        scanf("%d",&available[j]);

    for(i=0 ; i<n ; i++)
        for(j=0 ; j<m ; j++)
            need[i][j]=max[i][j]-allocation[i][j];

    resource_request();
    //Bankers_safety();
}