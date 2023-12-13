#include<stdio.h>
#include<math.h>

/*
Enterthe number of total cylinders : 200

Enter the number of cylinder: 8

Enter initial head position: 53

Enter the number of cylinder in request queue : 98 183 37 122 14 124 65 67

Direction 0: for left 1: for right :: 1

Seek Sequence : 53 65 67 98 122 124 183 199 37 14
Total head movement: 331.000000
Average head movement: 41.375000
*/

// Scan disk Scheduling algorithm.

int fill_both(int request_queue[], int to_left[], int to_right[], int initial_position, int total_head, int n){
    to_left[0] = initial_position;
    to_right[0] = initial_position;

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
    
    // find the index near to initial index.
    int end = 0;
    for(int i=0; i<n; i++){
        if(request_queue[i] > initial_position){
            end = i; break;
        }
    }

    // fill left.
    int index = 1;
    int i = end-1;
    while(i != -1) to_left[index++] = request_queue[i--];
    to_left[index++] = 0;
    i = end;
    while(i < n) to_left[index++] = request_queue[i++];

    // fill right.
    index = 1;
    i = end;
    while(i < n) to_right[index++] = request_queue[i++];
    to_right[index++] = total_head;
    i = end-1;
    while(i != -1) to_right[index++] = request_queue[i--];

    return index;
}

int main(){
    int total_head, initial_position, direction, n;
    float total_head_movement = 0;
    float avg_head_movement = 0;

    printf("Enterthe number of total cylinders : ");scanf("%d", &total_head);printf("\n"); total_head -= 1;

    printf("Enter the number of cylinder: ");scanf("%d", &n); printf("\n");

    printf("Enter initial head position: ");scanf("%d", &initial_position); printf("\n");

    int request_queue[n];
    int to_right[100];
    int to_left[100];

    printf("Enter the number of cylinder in request queue : ");
    for(int i=0; i<n; i++) scanf("%d", &request_queue[i]);
    printf("\n");

    int total_size = fill_both(request_queue, to_left, to_right, initial_position, total_head, n);

    printf("Direction 0: for left 1: for right :: ");scanf("%d", &direction);printf("\n");
    
    printf("Seek Sequence : ");
    
    if(direction == 0){
        printf("%d ", to_left[0]);
        for(int i=1; i<total_size; i++) {
            printf("%d ", to_left[i]);
            total_head_movement += fabs(to_left[i] - to_left[i-1]);
        }
    }
    if(direction == 1){
        printf("%d ", to_right[0]);
        for(int i=1; i<total_size; i++) {
            printf("%d ", to_right[i]);
            total_head_movement += fabs(to_right[i] - to_right[i-1]);
        }
    }
    printf("\n");

    avg_head_movement = total_head_movement/n;

    printf("Total head movement: %f\n", total_head_movement);
    printf("Average head movement: %f\n", avg_head_movement);

    return 0;
}