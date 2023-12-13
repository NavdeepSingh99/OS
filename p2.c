#include<stdio.h>
#include<unistd.h>

int main()
{
	int n;
	printf("Enter size of array: ");
	scanf("%d",&n);
	int a[n];
	printf("Enter Elements: \n");
	for(int i=0;i<n;i++){
	    scanf("%d",&a[i]);
	}
	int x= fork();
	int oddsum=0,evensum=0;
	if(x==0){		//Child Block
	    for(int i=0;i<n;i++){
	        if(a[i]%2==1){
	            oddsum+=a[i];
	        }
	    }
	    printf("Sum of odd numbers: %d\n",oddsum);
	}
	else{			//Parent Block
	    for(int i=0;i<n;i++){
	        if(a[i]%2==0){
	            evensum+=a[i];
	        }
	    }
	    printf("Sum of even numbers: %d\n",evensum);
	}
	return 0;
}
