#include<stdio.h>

int max[10][10],allocation[10][10],need[10][10],available[10],work[10],finish[10],n,m;

void Bankers_safety(){
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
        if(finish[i]==0){
            printf("System is unsafe .no safe sequence\n");
            return;
        }
    printf("System is safe\nSafe sequence is:\n");
    for(i=0 ; i<k ; i++)
        printf(" P%d ",safe_seq[i]);
    printf("\n\n");
}

void main(){
    int i,j;
    printf("How many processes? ");
    scanf("%d",&n);

    printf("How many resource types? ");
    scanf("%d",&m);

    printf("Enter the %dx%d max matrix: \n",n,m);
    for(i=0 ; i<n ; i++)
        for(j=0 ; j<m ; j++)
            scanf("%d",&max[i][j]);

    printf("Enter the %dx%d allocation matrix: \n",n,m);
    for(i=0 ; i<n ; i++)
        for(j=0 ; j<m ; j++)
            scanf("%d",&allocation[i][j]);

    printf("Enter the no of instances available for %d resource types: ",m);
    for(j=0 ; j<m ; j++)
        scanf("%d",&available[j]);

    for(i=0 ; i<n ; i++)
            for(j=0 ; j<m ; j++)
                need[i][j]=max[i][j]-allocation[i][j];

    Bankers_safety();
}