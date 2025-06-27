#include<stdio.h>
#define NIL 0

int n,m,process_size[10],block_size[10],allocation[10],filled[10];

void initialize(){
    int i,j;

    for(i=0 ; i<n ; i++)
        allocation[i]=-1;

    for(j=0 ; j<m ; j++)
        filled[j]=NIL;
}

void display(){
    int i,j,total=0;

    printf("\nPID|process_size|allocated_block|block_size|internal_fragmentation\n");
    for(i=0 ; i<n ; i++){
        int int_frag=block_size[allocation[i]]-process_size[i];
        total+=int_frag;

        if(allocation[i]==-1)
            printf("%-3d|%-12d|NIL\n");
        else
            printf("%-3d|%-12d|%-15d|%-10d|%-d\n",i,process_size[i],allocation[i],block_size[allocation[i]],int_frag);
    }
    printf("Total internal fragmentation=%d\n",total);
}

void ext_fragmentation(){
    int total=0,j;
    printf("\nEXTERNAL FRAGMENTATION \n");
    printf("Unfilled blocks|block_size\n");
    for(j=0 ; j<m ; j++)
        if(filled[j]==NIL){
            total+=block_size[j];
            printf("%-15d|%-d\n",j,block_size[j]);
        }

    printf("Total external fragmentation=%d\n",total);
}

void first_fit(){
    int i,j;

    initialize();

    for(i=0 ; i<n ; i++)
        for(j=0 ; j<m ; j++)
            if(block_size[j]>=process_size[i] && !filled[j]){
                allocation[i]=j;
                filled[j]=1;
                break;
            }

    display();
    ext_fragmentation();
}

void best_fit(){
    int i,j;

    initialize();

    for(i=0 ; i<n ; i++){
        int best_index=-1;
        for(j=0 ; j<m ; j++){
            if(block_size[j]>=process_size[i] && filled[j]==NIL)
                if(best_index==-1)
                    best_index=j;
                else if(block_size[j]<block_size[best_index])
                            best_index=j;
        }
        if(best_index!=-1){
            allocation[i]=best_index;
            filled[best_index]=1;
        }
    }
    display();
    ext_fragmentation();
}

void worst_fit(){
    int i,j;

    initialize();

    for(i=0 ; i<n ; i++){
        int worst_index=-1;
        for(j=0 ; j<m ; j++){
            if(block_size[j]>=process_size[i] && !filled[j])
                if(worst_index==-1)
                    worst_index=j;
                else if(block_size[j]>block_size[worst_index])
                            worst_index=j;
        }
        if(worst_index!=-1){
            allocation[i]=worst_index;
            filled[worst_index]=1;
        }
    }
    display();
    ext_fragmentation();
}

void main(){
    int i,j;

    printf("How many processes? ");
    scanf("%d",&n);

    printf("How many blocks? ");
    scanf("%d",&m);

    printf("Enter the size of %d processes: \n",n);
    for(i=0 ; i<n ; i++)
        scanf("%d",&process_size[i]);

    printf("Enter the size of %d blocks:\n",m);
    for(j=0 ; j<m ; j++)
        scanf("%d",&block_size[j]);

    printf("\nFIRST FIT\n");
    printf("-------------\n");
    first_fit();

    printf("\nBEST FIT\n");
    printf("-------------\n");
    best_fit();

    printf("\nWORST FIT\n");
    printf("-------------\n");
    worst_fit();
}