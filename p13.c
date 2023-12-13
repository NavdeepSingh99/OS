#include<stdio.h>
#include<math.h>

/*
Enterthe number of total cylinders : 200 ; 200 - 1 = 0 to 199;

Enter the number of cylinder: 8

Enter initial head position: 53

Enter the number of cylinder in request queue : 98 183 37 122 14 124 65 67 

Seek Sequence : 53 65 67 37 14 98 122 124 183
Total head movement: 236.000000
Average head movement: 29.500000

*/

// SSTF --> Shortest seek time first.
int find_sequence(int request_queue[], int seek_sequence[], int initial_position,int n){
    int is_visited[n];
    seek_sequence[0] = initial_position;
    int seek_index = 1;

    for(int i=0; i<n; i++) is_visited[i] = 0;

    int completed = 0;

    int element = initial_position;
    while(completed != n){
        int index = -1;
        int mini = 1e9;

        // finding minimum index for curr element.
        for(int i=0; i<n; i++){
            if(is_visited[i] == 0 && fabs(request_queue[i] - element) < mini){
                index = i;
                mini = fabs(request_queue[i] - element);
            }
        }

        is_visited[index] = 1;
        completed++;
        seek_sequence[seek_index++] = request_queue[index];
    }

    return seek_index;
}







int main(){
    int total_head, initial_position, n;
    float total_head_movement = 0;
    float avg_head_movement = 0;

    printf("Enterthe number of total cylinders : ");scanf("%d", &total_head);printf("\n"); total_head -= 1;

    printf("Enter the number of cylinder: ");scanf("%d", &n); printf("\n");

    printf("Enter initial head position: ");scanf("%d", &initial_position); printf("\n");

    int request_queue[n];
    int seek_sequence[100];

    printf("Enter the number of cylinder in request queue : ");
    for(int i=0; i<n; i++) scanf("%d", &request_queue[i]);
    printf("\n");

    int size = find_sequence(request_queue, seek_sequence, initial_position, n);

    printf("Seek Sequence : ");
    printf("%d ", seek_sequence[0]);
    for(int i=1; i<size; i++){
        printf("%d ", seek_sequence[i]);
        total_head_movement += fabs(seek_sequence[i] - seek_sequence[i-1]);
    }
    
    printf("\n");

    avg_head_movement = total_head_movement/n;

    printf("Total head movement: %f\n", total_head_movement);
    printf("Average head movement: %f\n", avg_head_movement);

    return 0;
}