#include <stdio.h>
#include<unistd.h>

/*
Enter the number of process: 5
Enter Burst Time: 3 7 2 4 3
Process No      AT      BT      CT      TAT     WT
3               0       2       2       2       0
1               0       3       5       5       2
5               0       3       8       8       5
4               0       4       12      12      8
2               0       7       19      19      12

ATAT = 9.20
AWT = 5.40
AThroughput = 0.26
cpu Utilization = 100.00
cup idelness = 0.00
*/


typedef struct process{
    int PID, AT, BT, CT, TAT, WT;
}process;

//Shortest Job First
int main()
{
    int n;
    printf("Enter the number of process: ");
    scanf("%d",&n);
    
    process p[n];
    
    
    printf("Enter Burst Time: ");
    for(int i=0; i<n; i++){
        scanf("%d", &p[i].BT);
        p[i].AT = 0;
        p[i].PID = i+1;
    }
    
    // Sort on the basis of burst time.
    for(int i=0; i<n; i++){
        for(int i=0; i<n-1; i++){
            if(p[i].BT > p[i+1].BT) {
                process temp = p[i];
                p[i] = p[i+1];
                p[i+1] = temp;
            }
        }
    }
    
    p[0].CT = p[0].BT;
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
        printf("%d\t\t%d\t%d\t%d\t%d\t%d\n", p[i].PID, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
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

    return 0;
}
