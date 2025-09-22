# include<stdio.h>
void f1(int num);
int f2(int n,int m);
int innum();
int main(){
	
    	while(1){
        int num=innum();
        printf("you input the num is %d\n",num);
        if (num<=0)printf("the input is falied ,the error code is%d\n",num);
        else f1(num);
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
void f1(int num)
{
	printf("please intput a number\n");
	
	for(int i=0;i<num;i++){
		for(int j=0;j<num;j++){
	}
	printf("\n");
	}
}
    

