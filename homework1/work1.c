# include<stdio.h>
#include <stdlib.h>
#include <sysinfoapi.h>
int** f1(int num);
int innum();
int main(){
	
    	while(1){
    	        int num=innum();
        printf("you input the num is %d\n",num);
        if (num<=0)printf("the input is falied ,the error code is%d\n",num);
        else {	
		int **a=f1(num);
		if(a==NULL) return -1;
		for(int i=0;i<num;i++){
			for(int j=0;j<num;j++){
			printf("  %d",a[i][j]);
		}
        	printf("\n");
		}
		free(a);
	    long long int begin2 = GetTickCount64();
		for(int i=0;i<10000;i++){free(f1(num));}
        long long int end2 = GetTickCount64();
	    double elapsed2 = (end2 - begin2)*1e-3;
		printf("Time measured: %.7f seconds.\n", elapsed2/10000);

}
		}
}

int innum()
{
	printf("please intput a number\n");
	int n;
	    scanf("%d",&n);
        if (n <= 0)
            {
          	printf("please intput a number\n");
            return -1;
			}
	    else return n;
}
int** f1(int num)
{
//	int a[num][num];
// int a[4][4];num=4;
int * * a=(int **)malloc(num * sizeof(int *));
if(a==NULL){
	printf("the mem allocation failed\n");
	return NULL;

}
    for (int i = 0; i < num; i++) {
        a[i] = (int *)malloc(num * sizeof(int));
        if (a[i] == NULL) {
            printf("Memory allocation failed.\n");
            for (int j = 0; j < i; j++) {
                free(a[j]);
            }
            free(a);
            return NULL;
        }
    }
	// int ** temppoint=a;
	int i=0,j=0,c=num*num;
	int all;
	int temp_int=num;
	while(c>0){
		all=num-1;
	    while(all--&&c>0)
		{
			a[i][j]=c--;
			j++;
		}
		all=num-1;
		while(all--&&c>0)
		{
			a[i][j]=c--;
			i++;
		}
		all=num-1;
		while(all--&&c>0)
		{
			a[i][j]=c--;
			j--;
		}
		all=num-1;
		while(all--&&c>0)
		{
			a[i][j]=c--;
			if(all)
			i--;
			else
			j++;
		}
		num--;
		num--;
//		scanf("%d",&num);
	// printf("please intput a number\n");
	}
	// a=temppoint;
	num=temp_int;
	// for(int i=0;i<num;i++){
	// 	for(int j=0;j<num;j++){
	// 	printf("  %d",a[i][j]);
	// }
	// printf("\n");
	// }
	return a;
}
    

