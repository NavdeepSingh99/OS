#include<stdio.h>
#include<math.h>



int find(int request_queue[], int initial_position, int direction, int n){

    // sort.
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-1-i; j++){
            if(request_queue[j] > request_queue[j+1]){
                int temp = request_queue[j];
                request_queue[j] = request_queue[j+1];
                request_queue[j+1] = temp;
            }
        }
    }

    int end = 0;
    for(int i=0; i<n; i++){
        if(request_queue[i] > initial_position){
            end = i;
            break;
        }
    }

    // if direction 0 then find just smaller to it
    if(direction == 0){
        return request_queue[end];
    }
    
    // if direction is 1 then return just larger to it.
    return request_queue[end-1];
}


// C -scan 
int main(){
    int total_head, initial_position, direction, n;
    float total_head_movement = 0;
    float avg_head_movement = 0;

    printf("Enterthe number of total cylinders : ");scanf("%d", &total_head);printf("\n");  total_head -= 1;

    printf("Enter the number of cylinder: ");scanf("%d", &n); printf("\n");

    printf("Enter initial head position: ");scanf("%d", &initial_position); printf("\n");

    int request_queue[n];

    printf("Enter the number of cylinder in request queue : ");
    for(int i=0; i<n; i++) scanf("%d", &request_queue[i]);
    printf("\n");


    printf("Direction 0: for left 1: for right :: ");scanf("%d", &direction);printf("\n");
    
    int find_num = find(request_queue, initial_position, direction ,n);
    if(direction == 0)
        total_head_movement += initial_position + total_head + fabs(total_head - find_num);
    if(direction == 1)
        total_head_movement += fabs(total_head - initial_position) + total_head + fabs(find_num);
    
    printf("\n");

    avg_head_movement = total_head_movement/n;

    printf("Total head movement: %f\n", total_head_movement);
    printf("Average head movement: %f\n", avg_head_movement);

    return 0;
}