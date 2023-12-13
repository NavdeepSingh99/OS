#include <stdio.h>
#include<unistd.h>

/*
Enter the number of process: 4 
Enter time Quantum: 2
Enter Arrival Time: 0 1 2 3
Enter Burst Time: 5 4 2 1
*/

typedef struct process{
    int PID, AT, BT, CT, TAT, WT;
}process;

int is_present_in_queue(int queue[], int queue_start, int queue_end, int process){
    for(int i=queue_start; i<queue_end; i++){
        if(queue[i] == process) return 1;
    }

    return 0;
}

// Round Robin
void round_robin(process p[], int BT[], int tq, int n){
    int counter = 0;
    int IT = 0;
    float ATAT = 0, AWT = 0;
    int index = 0;
    int count = 0;

    int queue[1000];
    int queue_end = 0;
    int queue_start = 0;

    while(1){
        if(index >= n) index = 0;
        queue[queue_end++] = p[index++].PID;

        int front = queue[queue_start++];

        // if Burst time of process is less then time quantum increase count by 1.
        if(BT[front] <= tq){
            counter += BT[front];
            BT[front] = 0;
            p[front].CT = counter;
            count++;
        }
        else{
            BT[front] -= tq;
            counter += tq;
        }
        
        // include if any process arrive in counter time.
        for(int i=0; i<n; i++){
            if(!is_present_in_queue(queue, queue_start, queue_end, i)){
                queue[queue_end++] = i;
            }
        }
        if(BT[front] != 0) queue[queue_end++] = front;

        if(queue_end == queue_start){
            for(int )
        }
        if(count == n) break;
    }
    
    
    for(int i=0; i<n; i++){
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT = p[i].TAT - p[i].BT;
        
        ATAT += p[i].TAT;
        AWT += p[i].WT;
    }
    
    printf("Process No\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0; i<n; i++){
        printf("%d\t\t%d\t%d\t%d\t%d\t%d\n", i, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
    }
    
    printf("\n");
    
    float TT = p[n-1].CT;
    ATAT = ATAT/n;
    AWT = AWT/n;
    
    float cpu_utilization = ((TT - IT)/TT)*100;
    float cpu_idelness = ((IT/TT)*100);
    float throughput = n/TT;
    
    printf("ATAT = %.2f\nAWT = %.2f\nAThroughput = %.2f\n", ATAT, AWT, throughput);
    printf("cpu Utilization = %.2f \ncup idelness = %.2f\n",cpu_utilization, cpu_idelness );
}



int main(){
    int n, tq;
    printf("Enter the number of process: ");
    scanf("%d",&n);

    printf("Enter time Quantum: ");
    scanf("%d", &tq);
    
    process p[n];
    int BT[n];
    
    printf("Enter Arrival Time: ");
    for(int i=0; i<n; i++){
        scanf("%d", &p[i].AT);
        p[i].PID = i+1;
    }
    printf("\n");
    
    printf("Enter Burst Time: ");
    for(int i=0; i<n; i++){
        scanf("%d", &p[i].BT);
        BT[i] = p[i].BT;
    }
    

    round_robin(p, BT, tq, n);

    return 0;
}