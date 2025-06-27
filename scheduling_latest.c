#include<stdio.h>
#include<stdlib.h>
#define SIZE 10
int ts,n;
struct process{
    int arr_time;
    int burst_time;
    int prio;
    int res_time;
    int turnaround_time;
    int comp_time;
    int wait_time;
    int completed;
    int isfirst;
    int rem_time;
}*p[SIZE];

void initialize(){
    int i;
    for(i=0 ; i<n ; i++){
        p[i]->completed=0;
        p[i]->rem_time=p[i]->burst_time;
        p[i]->isfirst=1;
    }
}

void sort(){
    int i,j;
    for(i=0 ; i<n-1 ; i++)
        for(j=0 ; j<n-i-1 ; j++)
            if(p[j]->arr_time>p[j+1]->arr_time){
                struct process *temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }   
}

void display(){
    int i;
    printf("PID | Arr_time | Burst_time | Priority | Resp_time | Comp_time | turnaround_time | wait_time\n");
    printf("-----------------------------------------------------------------------------------------------\n");
    for(i=0 ; i<n ; i++){
        printf("%-4d|%-10d|%-12d|%-10d|%-11d|%-11d|%-17d|%-d\n",i,p[i]->arr_time,p[i]->burst_time,p[i]->prio,p[i]->res_time,p[i]->comp_time,p[i]->turnaround_time,p[i]->wait_time);
    }
    printf("\n\n");
}

void fcfs(){
    int i,sys_time=0;
    float avgtt=0,avgwt=0;
    initialize();
    for(i=0 ; i<n ; i++){
        if(sys_time>=p[i]->arr_time && !p[i]->completed){
            p[i]->res_time=sys_time-p[i]->arr_time;
            sys_time+=p[i]->burst_time;
            p[i]->comp_time=sys_time;
            p[i]->turnaround_time=p[i]->comp_time-p[i]->arr_time;
            p[i]->wait_time=p[i]->turnaround_time-p[i]->burst_time;

            p[i]->completed=1;

            avgtt+=p[i]->turnaround_time;
            avgwt+=p[i]->wait_time;
        }else{
            sys_time++;
            i--;
        }
    }
    display();
    avgtt/=n;
    avgwt/=n;
    printf("Avg turnaround time=%.2f\n",avgtt);
    printf("Avg waiting time=%.2f\n",avgwt);
    printf("--------------------------------------------------------------------------------------\n\n");
}

int remain(){
    int i;
     for(i=0 ; i<n ; i++)
        if(p[i]->completed==0)
            return 1;
    return 0;
}

void sjf(){
    struct process* temp[SIZE];
    int i,j,sys_time=0,min_index;
    float avgtt=0,avgwt=0;

    initialize();

    while(remain()){
        j=0;
        for(i=0 ; i<n ; i++)
            if(sys_time>=p[i]->arr_time && p[i]->completed==0)
                temp[j++]=p[i];

        if(j==0){
            sys_time++;
            continue;
        }

        min_index=0;
        for(i=1 ; i<j ; i++)
            if(temp[i]->burst_time<temp[min_index]->burst_time)
                min_index=i;

        temp[min_index]->res_time=sys_time-temp[min_index]->arr_time;
        sys_time+=temp[min_index]->burst_time;
        temp[min_index]->comp_time=sys_time;
        temp[min_index]->turnaround_time=temp[min_index]->comp_time-temp[min_index]->arr_time;
        temp[min_index]->wait_time=temp[min_index]->turnaround_time-temp[min_index]->burst_time;

        temp[min_index]->completed=1;

        avgtt+=temp[min_index]->turnaround_time;
        avgwt+=temp[min_index]->wait_time;
    }

    display();
    avgtt/=n;
    avgwt/=n;
    printf("Avg turnaround time=%.2f\n",avgtt);
    printf("Avg waiting time=%.2f\n",avgwt);
    printf("--------------------------------------------------------------------------------------\n\n");
}

void priority_sched(){
    struct process* temp[SIZE];
    int i,j,sys_time=0,min_index;
    float avgtt=0,avgwt=0;

    initialize();

    while(remain()){
        j=0;
        for(i=0 ; i<n ; i++)
            if(sys_time>=p[i]->arr_time && p[i]->completed==0)
                temp[j++]=p[i];

        if(j==0){
            sys_time++;
            continue;
        }

        min_index=0;
        for(i=1 ; i<j ; i++)
            if(temp[i]->prio<temp[min_index]->prio)
                min_index=i;

        temp[min_index]->res_time=sys_time-temp[min_index]->arr_time;
        sys_time+=temp[min_index]->burst_time;
        temp[min_index]->comp_time=sys_time;
        temp[min_index]->turnaround_time=temp[min_index]->comp_time-temp[min_index]->arr_time;
        temp[min_index]->wait_time=temp[min_index]->turnaround_time-temp[min_index]->burst_time;

        temp[min_index]->completed=1;

        avgtt+=temp[min_index]->turnaround_time;
        avgwt+=temp[min_index]->wait_time;
    }

    display();
    avgtt/=n;
    avgwt/=n;
    printf("Avg turnaround time=%.2f\n",avgtt);
    printf("Avg waiting time=%.2f\n",avgwt);
    printf("--------------------------------------------------------------------------------------\n\n");
}

struct process* Q[SIZE];
int f=-1,r=-1;

void enqueue(struct process* item){
    if(f==(r+1)%SIZE)
        printf("queue full\n");
    else{
        if(f==-1)
            f=0;
        r=(r+1)%SIZE;
        Q[r]=item;
    }
}

struct process* dequeue(){
    if(f==-1){
        printf("queue empty\n");
        exit(1);
    }
    else{
        struct process* item=Q[f];
        f=(f+1)%SIZE;
        if(f==(r+1)%SIZE)
            f=r=-1;
        return item;
    }
}

void round_robin(){
    int i,j,sys_time=0;
    float avgtt=0,avgwt=0;
    initialize();
    for(i=0 ; i<n ; i++)
         enqueue(p[i]);

    while(remain()){
        struct process* temp=dequeue();
        if(sys_time>=temp->arr_time){
            if(temp->rem_time<ts){
                if(temp->isfirst){
                    temp->res_time=sys_time-temp->arr_time;
                    temp->isfirst=0;
                }

                sys_time+=temp->rem_time;
                temp->comp_time=sys_time;
                temp->turnaround_time=temp->comp_time-temp->arr_time;
                temp->wait_time=temp->turnaround_time-temp->burst_time;

                temp->completed=1;
                temp->rem_time=0;

                avgtt+=temp->turnaround_time;
                avgwt+=temp->wait_time;
            }else{
                if(temp->isfirst){
                    temp->res_time=sys_time-temp->arr_time;
                    temp->isfirst=0;
                }

                temp->rem_time-=ts;
                sys_time+=ts;

                if(temp->rem_time==0){
                    temp->comp_time=sys_time;
                    temp->turnaround_time=temp->comp_time-temp->arr_time;
                    temp->wait_time=temp->turnaround_time-temp->burst_time;

                    temp->completed=1;

                    avgtt+=temp->turnaround_time;
                    avgwt+=temp->wait_time;
                }else
                    enqueue(temp);
            }
        }else{
            enqueue(temp);
            for(j=0 ; j<n ; j++)
                if(sys_time>=p[j]->arr_time && !p[j]->completed)
                    break;
            if(j==n)
                sys_time++;
        }
    }
    display();
    avgtt/=n;
    avgwt/=n;
    printf("Avg turnaround time=%.2f\n",avgtt);
    printf("Avg waiting time=%.2f\n",avgwt);
    printf("----------------------------------------------------------------------------------------\n\n");
}

void Free(){
    int i;
    for(i=0 ; i<n ; i++)
        free(p[i]);
}

/*void main(){
    int i;
    printf("How many processes?");
    scanf("%d",&n);

    printf("Enter the arrival time of %d processes: \n",n);
    for(i=0 ; i<n ; i++){
        p[i]=(struct process*)malloc(sizeof(struct process));
        scanf("%d",&(p[i]->arr_time));
    }

    printf("Enter the burst time of %d processes: \n",n);
    for(i=0 ; i<n ; i++)
        scanf("%d",&(p[i]->burst_time));
    
    printf("Enter the priority of %d processes: \n",n);
    for(i=0 ; i<n ; i++)
        scanf("%d",&(p[i]->prio));

    printf("Enter timeslice: ");
    scanf("%d",&ts);

    sort();

    printf("FCFS:\n");
    fcfs();

    printf("SJF:\n");
    sjf();

    printf("PRIORITY SCHEDULING:\n");
    priority_sched();

    printf("ROUND ROBIN:\n");
    round_robin();

    Free();
}*/

void main(){
    int choice;
    int i;

    while(1){
        printf("Enter your choice:\n1)FCFS\n2)SJF\n3)Priority Scheduling\n4)Round Robin\n5)exit\n");
        scanf("%d",&choice);
        if(choice==5)
            exit(0);
        printf("How many processes?");
        scanf("%d",&n);

        printf("Enter the arrival time of %d processes: \n",n);
        for(i=0 ; i<n ; i++){
            p[i]=(struct process*)malloc(sizeof(struct process));
            scanf("%d",&(p[i]->arr_time));
        }

        printf("Enter the burst time of %d processes: \n",n);
        for(i=0 ; i<n ; i++)
            scanf("%d",&(p[i]->burst_time));

        sort();
        switch(choice){
            case 1: printf("FCFS:\n");
                    //sort();
                    fcfs();
                    Free();
                    break;
            case 2: printf("SJF:\n");
                    //sort();
                    sjf();
                    Free();
                    break;
            case 3: printf("Enter the priority of %d processes: \n",n);
                    for(i=0 ; i<n ; i++)
                        scanf("%d",&(p[i]->prio));
                    printf("Priority Scheduling:\n");
                    //sort();
                    priority_sched();
                    Free();
                    break;
            case 4: printf("Enter timeslice: ");
                     scanf("%d",&ts);
                    printf("Round Robin:\n");
                    //sort();
                    round_robin();
                    Free(); 
                    break;
        }
    }           
}