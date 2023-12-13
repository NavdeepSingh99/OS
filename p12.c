#include<stdio.h>
#include<math.h>

/*
Enterthe number of total cylinders : 200

Enter the number of cylinder: 8

Enter initial head position: 53

Enter the number of cylinder in request queue : 98 183 37 122 14 124 65 67 


Total head movement: 640.000000
Average head movement: 80.000000

*/

// FCFS --> First come first serve.


int main(){
    int total_head, initial_position, n;
    float total_head_movement = 0;
    float avg_head_movement = 0;

    printf("Enterthe number of total cylinders : ");scanf("%d", &total_head);printf("\n"); total_head -= 1;

    printf("Enter the number of cylinder: ");scanf("%d", &n); printf("\n");

    printf("Enter initial head position: ");scanf("%d", &initial_position); printf("\n");

    int request_queue[n];

    printf("Enter the number of cylinder in request queue : ");
    for(int i=0; i<n; i++) scanf("%d", &request_queue[i]);
    printf("\n");

    total_head_movement = request_queue[0] - initial_position;
    for(int i=1; i<n; i++){
        total_head_movement += fabs(request_queue[i] - request_queue[i-1]);
    }
    
    printf("\n");

    avg_head_movement = total_head_movement/n;

    printf("Total head movement: %f\n", total_head_movement);
    printf("Average head movement: %f\n", avg_head_movement);

    return 0;
}