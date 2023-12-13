//Orphan Process
#include<stdio.h>
#include<unistd.h>
void main()
{
    int x=fork();
    if(x==0)
    {
        //Child block
        sleep(5);
        printf("Orphan process created\n");
        printf("Process Id : %d\n",getpid());
    }
    else
    {
        // Parent block
        printf("Parent Terminated\n");
        printf("Process Id: %d\n",getpid());
    }
}
 
//Zombie Process
#include<stdio.h>
#include<unistd.h>
void main()
{
    int x=fork();
    if(x==0)
    {
        //Child block
        sleep(5);
        printf("Child terminated\n");
        printf("Process Id : %d\n",getpid());
    }
    else
    {
        // Parent block
        printf("Zombie Process created\n");
        printf("Process Id: %d\n",getpid());
    }
}
