#include<stdio.h>
#define NIL 9999

int ref_seq[30],F[10],n,nf,pagefaultcount;

void initialize(){
    int i;
    pagefaultcount=0;
    for(i=0 ; i<nf ; i++)
        F[i]=NIL;
}

int isHit(int item){
    int j;

    for(j=0 ; j<nf ; j++)
        if(F[j]==item)
            return 1;
    return 0;
}

void displayFrame(){
    int j;

    for(j=0 ; j<nf ; j++)
        if(F[j]==NIL)
            printf(" _  ");
        else
            printf("%-4d",F[j]);
    printf("\n");
}   

void fifo(){
    int i,j;
    initialize();

    printf("referenced page|   Status    |   Frame   \n");
    for(i=0 ; i<n ; i++){
        if(isHit(ref_seq[i])){
            printf("%-15d|  PAGE HIT   |\n",ref_seq[i]);
            //displayFrame();
        }else{
            pagefaultcount++;
            for(j=0 ; j<nf-1 ; j++)
                F[j]=F[j+1];

            F[nf-1]=ref_seq[i];

            printf("%-15d| PAGE FAULT  |",ref_seq[i]);
            displayFrame();
        }
    }

    printf("\npage fault count=%d\n\n\n",pagefaultcount);
}

void optimal(){
    int i,j;
    initialize();

    printf("referenced page|   Status    |   Frame   \n");
    for(i=0 ; i<n ; i++){
        if(isHit(ref_seq[i])){
            printf("%-15d|  PAGE HIT   |\n",ref_seq[i]);
            //displayFrame();
        }else{
            int next_found_index[10],max_index;

            pagefaultcount++;
            for(j=0 ; j<nf ; j++){
                next_found_index[j]=-1;
                for(int k=i+1 ; k<n ; k++){
                    if(ref_seq[k]==F[j]){
                        next_found_index[j]=k;
                        break;
                    }
                }
                if(next_found_index[j]==-1)
                    next_found_index[j]=9999;
            }

            max_index=0;
            for(j=1 ; j<nf ; j++)
                if(next_found_index[j]>next_found_index[max_index])
                    max_index=j;

            F[max_index]=ref_seq[i];
            printf("%-15d| PAGE FAULT  |",ref_seq[i]);
            displayFrame();
        }
    }
    printf("\npage fault count=%d\n\n\n",pagefaultcount);

}

void lru(){
    int i,j;
    initialize();
    printf("referenced page|   Status    |   Frame   \n");

    for(i=0 ; i<n ; i++){
        if(isHit(ref_seq[i])){
            printf("%-15d|  PAGE HIT   |\n",ref_seq[i]);
            //displayFrame();
        }else{
            int last_found_index[10],min_index;

            pagefaultcount++;
            for(j=0 ; j<nf ; j++){
                last_found_index[j]=-1;
                for(int k=i-1 ; k>=0 ; k--){
                    if(ref_seq[k]==F[j]){
                        last_found_index[j]=k;
                        break;
                    }
                }
                if(last_found_index[j]==-1)
                    last_found_index[j]=-9999;
            }

            min_index=0;
            for(j=1 ; j<nf ; j++)
                if(last_found_index[j]<last_found_index[min_index])
                    min_index=j;

            F[min_index]=ref_seq[i];
            printf("%-15d| PAGE FAULT  |",ref_seq[i]);
            displayFrame();
        }
    }
    printf("\npage fault count=%d\n\n\n",pagefaultcount);
}

int getHitIndex(int item){
    int j;
    for(j=0 ; j<nf ; j++)
        if(F[j]==item)
            return j;
}

void lfu(){
    int i,j,used_count[10];

    initialize();
    for(j=0 ; j<nf ; j++)
        used_count[j]=0;
    printf("referenced page|   Status    |   Frame   \n");

    for(i=0 ; i<n ; i++){
        if(isHit(ref_seq[i])){
            printf("%-15d|  PAGE HIT   |\n",ref_seq[i]);
            used_count[getHitIndex(ref_seq[i])]++;
        }else{
            int min_index,sofarcount;
            pagefaultcount++;

            min_index=0;
            for(j=1 ; j<nf ; j++)         
                if(used_count[j]<used_count[min_index]) 
                    min_index=j;

            F[min_index]=ref_seq[i];

            sofarcount=0;
            for(int k=0 ; k<=i ; k++)
                if(ref_seq[k]==F[min_index])
                    sofarcount++;

            used_count[min_index]=sofarcount;
            printf("%-15d| PAGE FAULT  |",ref_seq[i]);
            displayFrame();
        }
    }
    printf("\npage fault count=%d\n\n\n",pagefaultcount);
}

void mfu(){
   int i,j,used_count[10];

    initialize();
    for(j=0 ; j<nf ; j++)
        used_count[j]=9999;//imp
    printf("referenced page|   Status    |   Frame   \n");

    for(i=0 ; i<n ; i++){
        if(isHit(ref_seq[i])){
            printf("%-15d|  PAGE HIT   |\n",ref_seq[i]);
            used_count[getHitIndex(ref_seq[i])]++;
        }else{
            int max_index,sofarcount;
            pagefaultcount++;

            max_index=0;
            for(j=0 ; j<nf ; j++)
                /*if(F[j]==NIL){         
                    max_index=j;
                    break;
                }
                else */if(used_count[j]>used_count[max_index]) 
                        max_index=j;

            F[max_index]=ref_seq[i];

            sofarcount=0;
            for(int k=0 ; k<=i ; k++)
                if(ref_seq[k]==F[max_index])
                    sofarcount++;

            used_count[max_index]=sofarcount;
            printf("%-15d| PAGE FAULT  |",ref_seq[i]);
            displayFrame();
        }
    }
    printf("\npage fault count=%d\n\n\n",pagefaultcount);
}


void main(){
    int i;
    printf("Length of reference string: ");
    scanf("%d",&n);

    printf("Enter the reference string containing %d pages: \n",n);
    for(i=0 ; i<n ; i++)
        scanf("%d",&ref_seq[i]);

    printf("How many frames? ");
    scanf("%d",&nf);

    printf("FIFO\n");
    fifo();

    printf("LRU\n");
    lru();

    printf("Optimal\n");
    optimal();

    printf("LFU\n");
    lfu();

    printf("MFU\n");
    mfu();
}