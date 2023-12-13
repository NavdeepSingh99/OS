//  “Shortest Remaining Time First” scheduling.
#include<stdio.h>
#include<limits.h>
#include<stdbool.h>

/*
Enter number of process:5

Enter Arrival time:0 3 4 6 7

Enter Bus time:2 3 3 5 4
   Process      AT      BT      CT      TAT     WT
        1       0       2       2       2       0
        2       3       3       6       3       0
        3       4       3       9       5       2
        4       6       5       18      12      7
        5       7       4       13      6       2

ATAT=5.60
AWT=2.20
Throughput=0.28
Cpu Utilization=94.44
Cpu Idealness=5.56
*/


struct process{
    int PID,AT,BT,CT,TAT,WT,ST;
};
int findmax(int a ,int b){
    return (a>b)?a:b;
}
int findmin(int a,int b){
    return (a<b)?a:b;
}

int main(){
    printf("Enter number of process:");
	int n;
	scanf("%d",&n);

	struct process p[n];
	int bus_remaining[n];
	bool is_completed[100]={false},is_first_process=true;

	int completed=0,current_time=0;
	float TT,prev=0,IT=0,ATAT=0,AWT=0;

	for(int i=0;i<n;i++){
		p[i].PID=i+1;
	}
	printf("\nEnter Arrival time:");
    for(int i=0;i<n;i++){
		scanf("%d",&p[i].AT);
	}
	printf("\nEnter Bus time:");
	for(int i=0;i<n;i++){
		scanf("%d",&p[i].BT);
		bus_remaining[i]=p[i].BT;
	}
	while(completed!=n){
	    int min_index=-1;
	    int minimum=INT_MAX;

	    for(int i=0;i<n;i++){
	        if(p[i].AT<=current_time && is_completed[i]==false){
	            if(bus_remaining[i]<minimum){
	                minimum=bus_remaining[i];
	                min_index=i;
	            }
	            if(bus_remaining[i]==minimum){
	                if(p[i].AT<p[min_index].AT){
	                    minimum=bus_remaining[i];
	                    min_index=i;
	                }
	            }
	        }
	        
	    }

	    if(min_index==-1){
	        current_time++;
	    }
	    else{
	        if(bus_remaining[min_index]==p[min_index].BT){
	            p[min_index].ST=current_time;
	            IT+=(is_first_process==true)?0:p[min_index].ST-prev;
	            is_first_process=false;
	        }
	        bus_remaining[min_index]=bus_remaining[min_index]-1;
	        current_time++;
	        prev=current_time;

	        if(bus_remaining[min_index]==0){
	            p[min_index].CT=current_time;
	            p[min_index].TAT=p[min_index].CT-p[min_index].AT;
	            p[min_index].WT=p[min_index].TAT-p[min_index].BT;
	            completed++;

	            ATAT+=p[min_index].TAT;
	            AWT+=p[min_index].WT;
	            is_completed[min_index]=true;
	        }
	    }
	}

    ATAT=ATAT/n;
    AWT=AWT/n;
    int max_CT=INT_MIN;
    int min_AT=INT_MAX;

    for(int i=0;i<n;i++){
        max_CT=findmax(max_CT,p[i].CT);
        min_AT=findmin(min_AT,p[i].AT);
    }

    TT=max_CT-min_AT;
    float cpu_utilization=((TT-IT)/TT)*100;
    float throughput=n/TT;
    float cpu_idealness=(IT/TT)*100;

    printf("   Process	AT	BT	CT	TAT	WT\n");
	for(int i=0;i<n;i++){
		printf("	%d",p[i].PID);
		printf("	%d",p[i].AT);
		printf("	%d",p[i].BT);
		printf("	%d",p[i].CT);
		printf("	%d",p[i].TAT);
		printf("	%d\n",p[i].WT);
	}
	printf("\nATAT=%.2f",ATAT);
	printf("\nAWT=%.2f",AWT);
	printf("\nThroughput=%.2f",throughput);
	printf("\nCpu Utilization=%.2f",cpu_utilization);
	printf("\nCpu Idealness=%.2f",cpu_idealness);
	return 0;

}
