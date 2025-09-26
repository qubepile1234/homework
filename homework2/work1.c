# include<stdio.h>
#include <stdlib.h>
#include <sysinfoapi.h>
#include<time.h>
#define OP BOOLEAN //目标数据类型
OP** f1(int num,OP normal,OP different); 
 //生成一个num*num的方阵，op为其中元素的数据类型，返回op**,支持方阵中有一个随机位置的特殊元素
 //随机位置由此实现    srand((unsigned)time(NULL));   int random = rand()%num*num;
void release_aquare(int num,OP** op);
void  release_print_square(int num,OP** op);
void print_square(int num,OP** op);
 //打印出op方阵
#define THER "%d  "
//配合使用

#define testtime1  	    long long int begin2 = GetTickCount64();		for(int i=0;i<10000;i++)
#define testtime2       long long int end2 = GetTickCount64();	    double elapsed2 = (end2 - begin2)*1e-3;		printf("Time measured: %.7f seconds.\n", elapsed2/10000);
//配合void print_square(int num,OP**);使用，打印你想要的类型ther为你想要的printf中的内容
int innum();
void fillsquare(int num,OP normal,OP different,OP** op);

int main(){	
    	while(1){
    	int num=innum();
        printf("you input the num is %d\n",num);
        if (num<=0)printf("the input is falied ,the error code is%d\n",num);
        else 
			{	
	    OP** op=f1(num,TRUE,FALSE);
        if(op==NULL) return -1;
        fillsquare(num,TRUE,FALSE,op);
		release_aquare(num,op);
	    testtime1{OP** optest=f1(num,TRUE,FALSE); release_print_square(num,optest);}testtime2
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
/// @brief create a square
/// @param num int
/// @param normal 类型OP 宏定义
/// @param different 类型OP 宏定义
/// @return 一个方阵，num*num大小，有一个特殊元素，位置随机
OP** f1(int num,OP normal,OP different)
{
	OP **square=(OP **)malloc(num*sizeof(OP *));
	    if (square == NULL) 
			{
				printf("Memory allocation failed.\n");
				return NULL;
			}
	    for (int i = 0; i < num; i++) {
        square[i] = (OP *)malloc(num*sizeof(OP));
        if (square[i] == NULL) {
            printf("Memory allocation failed.\n");
            for (int j = 0; j < i; j++) {
                free(square[j]);
            }
            free(square);
            return NULL;
        }
    }
	for(int i=0;i<num;i++){
		for(int j=0;j<num;j++){
			square[i][j]=normal;
		}
	}
    srand((unsigned)time(NULL));
    int random = rand()%num*num;
	square[random/num][random%num]=different;
	return square;
}

int the_num_in_fillsquare;
void fillsquare(int num,OP normal,OP different,OP** op){
    int ii,jj;
	int count=0;
	for(int i=0;i<num;i++){
		for(int j=0;j<num;j++){
			if(op[i][j]==different){
				ii=i;jj=j;
				count++;
                // op[num][num+jj]=different;
				// op[num+ii][num]=different;
			}
		}
	 }
	 if(count>1){printf("error,the code is count-1");system("pause");}
	 num=num>>1;
				if(ii>num){op[num][num]=different;op[num][num+1]=different;}
				else{op[num+1][num]=different;op[num+1][num+1]=different;}
                if(jj>num){op[num][num]=different;op[num+1][num]=different;}
				else{op[num][num+1]=different;op[num+1][num+1]=different;}
			print_square(the_num_in_fillsquare<<1,op);
			if(num==0){return;}
			fillsquare(num,normal,different,op);
}
/// @brief release_aquare
/// @param num 
/// @param op 
void release_aquare(int num,OP** op){
	      for(int i=0;i<num;i++){
			for(int j=0;j<num;j++){
             free(op[i][j]);
			}
	  }
	  free(op);
}
/// @brief print_square
/// @param num 
/// @param op 
void  print_square(int num,OP** op){
      for(int i=0;i<num;i++){
			for(int j=0;j<num;j++){
				printf("the square is :");
				printf(THER,op[i][j]);
			}
			printf("/n");
	  }
}
/// @brief release_print_square
/// @param num 
/// @param op 
void  release_print_square(int num,OP** op){
      for(int i=0;i<num;i++){
			for(int j=0;j<num;j++){
				printf("the square is :");
				printf(THER,op[i][j]);
				free(op[i][j]);
			}
         printf("/n");
	  }
	  free(op);
}