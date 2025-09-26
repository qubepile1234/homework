# include<stdio.h>
// # include<time.h>
#include <sysinfoapi.h>

int f1(int num,int max);
int f2(int n,int m);
int innum();
int main(){
    	while(1){
        int num=innum();
        printf("you input the num is %d\n",num);
        if (num<=0)printf("the input is falied ,the error code is%d\n",num);
        else {
			printf("the wari is %d\n",f1(num,num));
		    long long int begin2 = GetTickCount64();
			// clock_t start=clock();
			for(int i=0;i<5000;i++){f1(num,num);}
			// clock_t end=clock();
            long long int end2 = GetTickCount64();
			    double elapsed2 = (end2 - begin2)*1e-3;
			    // double elapsed = (end - start)/CLOCKS_PER_SEC;
        	// printf("Time measured: %.7f seconds.\n", elapsed/5000);
			printf("Time measured: %.7f seconds.\n", elapsed2/5000);
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
int f1(int num,int max)
{
	if(num<=0||max<=0)	return 0;
	else if(max>num)	return f1(num,num);
	else if (max==1||num==1) return 1;
	else if(num==max)  return 1+f1(num,max-1);
	else return f1(num-max,max)+f1(num,max-1);
}
    

