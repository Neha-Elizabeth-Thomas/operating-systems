#include<stdio.h>

int n,req[20],total_head_mov,initial_head,size,dir;

int modulus(int num){
    return num>=0?num:-num;
}

void fcfs(){
    int i,j,current;

    total_head_mov=0;
    printf("%d -> ",initial_head);
    current=initial_head;
    for(i=0 ;  i<n ; i++){
        if(i==n-1)
            printf("%d\n",req[i]);
        else
            printf("%d -> ",req[i]);
        total_head_mov+=modulus(current-req[i]);
        current=req[i];
    }
    printf("Total head movement=%d\n\n",total_head_mov);
}

void sort(){
    int i,j;

    for(i=0 ; i<n-1 ; i++)
        for(j=0 ; j<n-i-1 ; j++)
            if(req[j]>req[j+1]){
                int temp=req[j];
                req[j]=req[j+1];
                req[j+1]=temp;
            }
}

int getnxtindex(){
    if(initial_head==size-1)
        return n;
    for(int i=0 ; i<n ; i++)
        if(req[i]>initial_head)
            return i;
}

void scan(){
    int i,j,nxt_index;

    total_head_mov=0;
    nxt_index=getnxtindex();

    printf("%d -> ",initial_head);
    if(dir==1 || initial_head==0){
        for(i=nxt_index ; i<n ; i++)
            printf("%d -> ",req[i]);
        if(req[n-1]!=size-1)
            printf("%d -> ",size-1);
        for(i=nxt_index-1 ; i>=0 ; i--)
            printf("%d -> ",req[i]);

        total_head_mov+=(size-1)-initial_head;
        total_head_mov+=(size-1)-req[0];

    }else if(dir==0 || initial_head==size-1){

            for(i=nxt_index-1 ; i>=0 ; i--)
                printf("%d -> ",req[i]);
            if(req[0]!=0)
                printf("0 -> ");
            for(i=nxt_index ; i<n ; i++)
                printf("%d -> ",req[i]);
            
            total_head_mov+=initial_head-0;
            total_head_mov+=req[n-1]-0;
        }

    printf("\nTotal head movement=%d\n\n",total_head_mov);
}

void cscan(){
    int i,j,nxt_index;

    total_head_mov=0;
    nxt_index=getnxtindex();

    printf("%d -> ",initial_head);
    if(dir==1 || initial_head==0){
        for(i=nxt_index ; i<n ; i++)
            printf("%d -> ",req[i]);
        if(req[n-1]!=size-1)
            printf("%d -> 0 -> ",size-1);
        for(i=0 ; i<=nxt_index-1 ; i++)
            printf("%d -> ",req[i]);

        total_head_mov+=(size-1)-initial_head;
        total_head_mov+=(size-1)-0;
        total_head_mov+=req[nxt_index-1]-0;

    }else if(dir==0 || initial_head==size-1){

            for(i=nxt_index-1 ; i>=0 ; i--)
                printf("%d -> ",req[i]);
            if(req[0]!=0)
                printf("0 -> %d -> ",size-1);
            for(i=n-1 ; i>=nxt_index ; i--)
                printf("%d -> ",req[i]);
            
            total_head_mov+=initial_head-0;
            total_head_mov+=(size-1)-0;
            total_head_mov+=(size-1)-req[nxt_index];
        }

    printf("\nTotal head movement=%d\n\n",total_head_mov);
}

void look(){
    int i,j,nxt_index;

    total_head_mov=0;
    nxt_index=getnxtindex();

    printf("%d -> ",initial_head);
    if(dir==1 || initial_head==0){
        for(i=nxt_index ; i<n ; i++)
            printf("%d -> ",req[i]);

        for(i=nxt_index-1 ; i>=0 ; i--)
            printf("%d -> ",req[i]);

        total_head_mov+=req[n-1]-initial_head;
        total_head_mov+=req[n-1]-req[0];

    }else if(dir==0 || initial_head==size-1){

            for(i=nxt_index-1 ; i>=0 ; i--)
                printf("%d -> ",req[i]);
            
            for(i=nxt_index ; i<n ; i++)
                printf("%d -> ",req[i]);
            
            total_head_mov+=initial_head-req[0];
            total_head_mov+=req[n-1]-req[0];
        }

    printf("\nTotal head movement=%d\n\n",total_head_mov);
}

void clook(){
    int i,j,nxt_index;

    total_head_mov=0;
    nxt_index=getnxtindex();

    printf("%d -> ",initial_head);
    if(dir==1 || initial_head==0){
        for(i=nxt_index ; i<n ; i++)
            printf("%d -> ",req[i]);
    
        for(i=0 ; i<=nxt_index-1 ; i++)
            printf("%d -> ",req[i]);

        total_head_mov+=req[n-1]-initial_head;
        total_head_mov+=req[n-1]-req[0];
        total_head_mov+=req[nxt_index-1]-req[0];

    }else if(dir==0 || initial_head==size-1){

            for(i=nxt_index-1 ; i>=0 ; i--)
                printf("%d -> ",req[i]);
            
            for(i=n-1 ; i>=nxt_index ; i--)
                printf("%d -> ",req[i]);
            
            total_head_mov+=initial_head-req[0];
            total_head_mov+=req[n-1]-req[0];
            total_head_mov+=req[n-1]-req[nxt_index];
        }

    printf("\nTotal head movement=%d\n\n",total_head_mov);
}

void sstf(){
    int i,j,nxt_index,visited[20],min_index,current,count;

    total_head_mov=0;
    for(i=0 ; i<n ; i++)
        visited[i]=0;

    current=initial_head;
    count=0;
    printf("%d -> ",initial_head);
    while(count<n){
        min_index=-1;
        for(i=0 ; i<n ; i++)
            if(!visited[i])
                if(modulus(current-req[i])<modulus(current-req[min_index]) || min_index==-1)
                    min_index=i;
        visited[min_index]=1;
        count++;
        printf("%d -> ",req[min_index]);
        total_head_mov+=modulus(current-req[min_index]);
        current=req[min_index];
        
    }

    printf("\nTotal head movement=%d\n\n",total_head_mov);
}

void main(){
    int i;
    printf("How many request? ");
    scanf("%d",&n);

    printf("Enter %d requests: \n",n);
    for(i=0 ; i<n ; i++)
        scanf("%d",&req[i]);

    printf("Enter the initial head position: ");
    scanf("%d",&initial_head);

    printf("Enter the size of cylinder: ");
    scanf("%d",&size);

    printf("Enter direction of movement(0 to low and 1 to high): ");
    scanf("%d",&dir);

    printf("FCFS\n");
    fcfs();

    sort();

    printf("SCAN\n");
    scan();

    printf("CSCAN\n");
    cscan();

    printf("LOOK\n");
    look();

    printf("CLOOK\n");
    clook();

    printf("SSTF\n");
    sstf();
}