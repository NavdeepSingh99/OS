#include <stdio.h>
#include<unistd.h>

/*
Enter the number of process: 5
Enter Arrival Time: 0 2 4 6 8
Enter Burst Time: 1 3 3 4 6

Process No      AT      BT      CT      TAT     WT
0               0       1       1       1       0
1               2       3       5       3       0
2               4       3       8       4       1
3               6       4       12      6       2
4               8       6       18      10      4

ATAT = 4.80
AWT = 1.40
AThroughput = 0.28
cpu Utilization = 94.44
cup idelness = 5.56
*/


/*
Enter the number of process: 4
Enter Arrival Time: 0 1 3 5
Enter Burst Time: 10 6 2 4

Process No      AT      BT      CT      TAT     WT
0               0       10      10      10      0
1               1       6       16      15      9
2               3       2       18      15      13
3               5       4       22      17      13

ATAT = 14.25
AWT = 8.75
AThroughput = 0.18
cpu Utilization = 100.00
cup idelness = 0.00
*/



typedef struct process{
    int AT, BT, CT, TAT, WT;
}process;


// First Come First Serve
void FCFS(process p[], int n){

    p[0].CT = p[0].BT;
    int counter = p[0].CT;
    int IT = 0;
    float ATAT = 0, AWT = 0;
    
    for(int i=1; i<n; i++){
        if(p[i].AT <= p[i-1].CT){
            p[i].CT = p[i-1].CT + p[i].BT;
            
        }else{
            int prevDiff = p[i].AT - p[i-1].CT;
            IT += prevDiff;
            p[i].CT = prevDiff + p[i-1].CT + p[i].BT;
        }
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

int main()
{
    int n;
    printf("Enter the number of process: ");
    scanf("%d",&n);
    
    process p[n];
    
    printf("Enter Arrival Time: ");
    for(int i=0; i<n; i++){
        scanf("%d", &p[i].AT);
    }
    printf("\n");
    
    printf("Enter Burst Time: ");
    for(int i=0; i<n; i++){
        scanf("%d", &p[i].BT);
    }
    

    FCFS(p, n);

    return 0;
}
