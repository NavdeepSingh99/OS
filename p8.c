#include<stdio.h>
#include<limits.h>
#include<stdbool.h> 
#include<stdlib.h> 


/*
Enter number of process: 4

Enter Arrival Time:0 2 8 9

Enter Bus Time:3 2 2 4

Enter quantam time:2
   Process      AT      BT      CT      TAT     WT
        1       0       3       5       5       2
        2       2       2       4       2       0
        3       8       2       10      2       0
        4       9       4       14      5       1

ATAT = 3.50
AWT = 0.75
AThroughput = 0.29
CpuUtilization = 78.57
CpuIdealness=21.43
*/

struct process{
    int pid,at,bt,ct,tat,wt,st,bt_remaining;
};

int findmax(int a,int b){
    return(a>b)?a:b;
}

// Round robin
int main(){
    int n,index,qt,front=-1,rear=-1,completed=0,current_time=0; 
    int queue[100]; 
    bool visited[100]={false};
    bool is_first_process=true; 
    float ATAT=0, AWT=0;


    float throughput,cpu_utilization,cpu_idealness,total_time=0,idle_time=0; 
    printf("Enter number of process: "); 
    scanf("%d",&n); 
    struct process p[10]; 
    struct process temp; 

    printf("\nEnter Arrival Time:"); 
    for(int i=0; i<n;i++){
        scanf("%d",&p[i].at); 
        p[i].pid=i+1;
    }

    printf("\nEnter Bus Time:"); 
    for(int i=0; i<n; i++){ 
        scanf("%d",&p[i].bt); 
        p[i].bt_remaining=p[i].bt;
    }

    printf("\nEnter quantam time:"); 
    scanf("%d",&qt); 
    for(int i=0; i<n-1;i++){ 
        for(int j=0; j<n-1-i;j++){ 
            if(p[j].at>p[j+1].at){ 
                temp=p[j]; 
                p[j]=p[j+1]; 
                p[j+1]=temp;
            }
        }
    }


    front = rear = 0; 
    queue[rear] = 0; 
    visited[0] = true; 
    
    while(completed != n){
        index=queue[front]; 
        front++; 
        
        if(p[index].bt_remaining == p[index].bt){
            p[index].st = findmax(current_time,p[index].at); 
            idle_time += (is_first_process == true)?0:p[index].st - current_time; 
            current_time = p[index].st; 
            is_first_process = false;
        }

        if(p[index].bt_remaining - qt  > 0){
            p[index].bt_remaining -= qt; 
            current_time += qt;
        }
        else{
            current_time += p[index].bt_remaining; 
            p[index].bt_remaining = 0; 
            completed++;

            p[index].ct = current_time; 
            p[index].tat = p[index].ct - p[index].at; 
            p[index].wt = p[index].tat - p[index].bt;
            ATAT+=p[index].tat;
            AWT+=p[index].wt;
        }
        for(int i=1; i<n; i++){ 
            if(p[i].bt_remaining > 0 && p[i].at <= current_time && visited[i] == false){
                queue[++rear]=i; 
                visited[i]=true;
            }
        }
        
        if(p[index].bt_remaining > 0){
            queue[++rear]=index;
        }


        if(front>rear){
            for(int i=1; i<n; i++){
                if(p[i].bt_remaining > 0){
                    queue[++rear] = i; 
                    visited[i] = true; 
                    break;
                }
            }
        }
    }

    ATAT=ATAT/n; AWT=AWT/n;
    int max_ct=INT_MIN;

    for(int i=0; i<n; i++){
        max_ct=findmax(max_ct,p[i].ct);
    }

    total_time = max_ct - p[0].at; 
    cpu_utilization = ((total_time-idle_time)/total_time)*100; 
    cpu_idealness = (idle_time/total_time)*100; 
    throughput=n/total_time; 
    
    for(int i=0; i<n-1; i++){ 
        for(int j=0;j<n-1-i;j++){ 
            if(p[j].pid > p[j+1].pid){ 
                temp=p[j]; 
                p[j] = p[j+1]; 
                p[j+1]=temp;
            }
        }
    }

    // printf("ProcessAT\tBT\tCT\tTAT\tWT\n"); 
    // for(int i=0; i<n; i++){ 
    //     printf(" %d",p[i].pid); 
    //     printf(" %d",p[i].at); 
    //     printf(" %d",p[i].bt); 
    //     printf(" %d",p[i].ct); 
    //     printf(" %d",p[i].tat); 
    //     printf(" %d\n",p[i].wt);
    // }
    

    printf("   Process	AT	BT	CT	TAT	WT\n");
	for(int i=0;i<n;i++){
		printf("	%d",p[i].pid);
		printf("	%d",p[i].at);
		printf("	%d",p[i].bt);
		printf("	%d",p[i].ct);
		printf("	%d",p[i].tat);
		printf("	%d\n",p[i].wt);
	}
    printf("\nATAT = %.2f",ATAT); 
    printf("\nAWT = %.2f",AWT); 
    printf("\nAThroughput = %.2f",throughput); 
    printf("\nCpuUtilization = %.2f",cpu_utilization); 
    printf("\nCpuIdealness=%.2f",cpu_idealness); 
	   
    
    return 0;
}
