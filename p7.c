#include<stdio.h>
#include<stdbool.h>
#include<limits.h>

/*
Enter number of process:4    

Enter Arrival time:1 2 4 5

Enter Bus time:6 2 3 1

Enter Priority:3 4 1 2
   Process      AT      BT      CT      TAT     WT  Priority
        1       1       6       11      10      4    3
        2       2       2       13      11      9    4
        3       4       3       7       3       0    1
        4       5       1       8       3       2    2
ATAT=6.75
AWT=3.75
Throughput=0.33
Cpu Utilization=91.67
Cpu Idleness=8.33
*/
struct process{
	int pid,at,bt,ct,tat,wt,st,priority;
};
int max(int a,int b){
	return (a>b)?a:b;
}
int min(int a,int b){
	return (a<b)?a:b;
}

// “Preemptive Priority” scheduling.
int main(){
	int n;
	printf("Enter number of process:");
	scanf("%d",&n);

	struct process p[n];
	float bus_remaining[100];
    bool is_completed[100]={false},is_first_process=true;

	int current_time = 0;
    int completed = 0;

	float Atat=0,Awt=0,idle_time=0,total_time=0,prev=0;
	float cpu_utilization,cpu_idleness,throughput;

	printf("\nEnter Arrival time:");
	for(int i=0;i<n;i++){
		scanf("%d",&p[i].at);
		p[i].pid=i+1;
	}
	printf("\nEnter Bus time:");
	for(int i=0;i<n;i++){
		scanf("%d",&p[i].bt);
		bus_remaining[i]=p[i].bt;
		
	}
	printf("\nEnter Priority:");
	for(int i=0;i<n;i++){
		scanf("%d",&p[i].priority);
	}
	while(completed!=n){
		int index=-1;
		int max_priority=INT_MAX;

		for(int i=0;i<n;i++){

			if(p[i].at<=current_time && is_completed[i]==false){

				if(p[i].priority<max_priority){
					max_priority=p[i].priority;
					index=i;
				}
				if(p[i].priority==max_priority){
					if(p[i].at<p[index].at){
						max_priority=p[i].priority;
						index=i;
					}
				}
			}
		}
		if(index!=-1){
			if(bus_remaining[index]==p[index].bt){
				p[index].st=current_time;
				idle_time+=p[index].st-prev;
			}

			bus_remaining[index]-=1;
			current_time++;
			prev=current_time;

			if(bus_remaining[index]==0){
				p[index].ct=current_time;
				p[index].tat=p[index].ct-p[index].at;
				p[index].wt=p[index].tat-p[index].bt;
				Atat+=p[index].tat;
				Awt+=p[index].wt;
				is_completed[index]=true;
				completed++;
				
			}
		}
		else{
			current_time++;
		}
		
	}
	int max_ct=INT_MIN;
	int min_at=INT_MAX;
	for(int i=0;i<n;i++){
		max_ct=max(max_ct,p[i].ct);
		min_at=min(min_at,p[i].at);
	}
	total_time=max_ct-min_at;
	cpu_utilization=((total_time-idle_time)/total_time)*100;
	cpu_idleness=(idle_time/total_time)*100;
	throughput=n/total_time;

	printf("   Process	AT	BT	CT	TAT	WT  Priority\n");
	for(int i=0;i<n;i++){
		printf("	%d",p[i].pid);
		printf("	%d",p[i].at);
		printf("	%d",p[i].bt);
		printf("	%d",p[i].ct);
		printf("	%d",p[i].tat);
		printf("	%d",p[i].wt);
		printf("    %d\n",p[i].priority);
	}
	printf("ATAT=%.2f\n",Atat/n);
	printf("AWT=%.2f\n",Awt/n); 
	printf("Throughput=%.2f\n",throughput); 
	printf("Cpu Utilization=%.2f\n",cpu_utilization); 
	printf("Cpu Idleness=%.2f\n",cpu_idleness);     

	return 0;
	
}
