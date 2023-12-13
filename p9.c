#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define true 1
#define false 0
#define SIZE 50

/*
Enter the number of process: 5

Enter the number of resources or frame: 3

Enter the initial allocated resources: 0 1 0 2 0 0 3 0 2 2 1 1 0 0 2

Enter the max required resources: 7 5 3 3 2 2 9 0 2 4 2 2 5 3 3

Enter the available resources: 3 3 2

Remaining need :
7 4 3
1 2 2
6 0 0
2 1 1
5 3 1
The system in safe state...
safe sequence is : p1 p3 p4 p0 p2
*/


int not_j_insafe_seq(int safe_sequence[], int j, int n){
    for(int i=0; i<n; i++){
        if(safe_sequence[i] == j) return true;
    }
    return false;
}

// Banker's Algorithm
void banker_algorithm(int allocation[SIZE][SIZE], int max_need[SIZE][SIZE], int available_resource[], int np, int nr){

    int remaining_need[np][nr];

    // Calculate remaining need
    for(int i=0; i<np; i++){
        for(int j=0; j<nr; j++){
            remaining_need[i][j] = fabs(max_need[i][j] - allocation[i][j]);
        }
    }


    // printing remaning need.
    printf("Remaining need :\n");
    for(int i=0; i<np; i++){
        for(int j=0; j<nr; j++){
            printf("%d ", remaining_need[i][j]);
        }
        printf("\n");
    }

    int flag = 0;
    int safe_sequence[np];
    int safe_sequence_index = 0;

    // initialize;
    for(int i=0; i<np; i++) safe_sequence[i] = -1;

    for(int i=0; i<np; i++){

        for(int j=0; j<np; j++){

            int is_safe = true;

            // check from available resource.
            for(int k=0; k<nr; k++){
                if(remaining_need[j][k] > available_resource[k]) is_safe = false;
            }

            if(is_safe == true && not_j_insafe_seq(safe_sequence, j,safe_sequence_index) == false){
                flag = 1;
                safe_sequence[safe_sequence_index] = j;
                safe_sequence_index++;

                // release resouce from allocation by just adding to available resource.
                for(int k=0; k<nr; k++) available_resource[k] += allocation[j][k]; 
            }
        }
    }

    if(flag == 0) {
        printf("Not int safe state...");
        exit(0);
    }
    else{
        // Printing safe sequence.
        printf("The system in safe state...\n");
        printf("safe sequence is : ");
        for(int i=0; i<safe_sequence_index; i++){
            printf("p%d ", safe_sequence[i]);
        }
    }

}



int main(){
    int np, nr;
    printf("Enter the number of process: ");
    scanf("%d", &np);
    printf("\n");


    printf("Enter the number of resources or frame: ");
    scanf("%d", &nr);
    printf("\n");


    int allocation[SIZE][SIZE];
    int max_need[SIZE][SIZE];
    int available_resource[SIZE];


    printf("Enter the initial allocated resources: \n");
    for(int i=0; i<np; i++){
        for(int j=0; j<nr; j++){
            scanf("%d", &allocation[i][j]);
        }
    }
    printf("\n");


    printf("Enter the max required resources: \n");
    for(int i=0; i<np; i++){
        for(int j=0; j<nr; j++){
            scanf("%d", &max_need[i][j]);
        }
    }
    printf("\n");


    printf("Enter the available resources: ");
    for(int i=0; i<nr; i++){
        scanf("%d", &available_resource[i]);
    }
    printf("\n");


    banker_algorithm(allocation, max_need, available_resource, np, nr);

    return 0;
}