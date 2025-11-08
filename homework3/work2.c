# include<stdio.h>
#include <stdlib.h>
#include <sysinfoapi.h>
#include<time.h>
#define OP int //目标数据类型
OP** f1(int num,OP normal); 
 //生成一个num*num的方阵，op为其中元素的数据类型，返回op**,支持方阵中有一个随机位置的特殊元素
void release_square(int num,OP** op);
void print_square(int num,OP** op);
 //打印出op方阵
#define THER "%d  "
//配合使用
void fill_square(int num,OP** op,int x_plus,int y_plus,int base);
 //填充方阵，num为方阵的大小，op为方阵，x_plus,y_plus为起始位置，base为初始值
  //配合void print_square(int num,OP**);使用，打印你想要的类型ther为你想要的printf中的内容

#define testtime1  	    long long int begin2 = GetTickCount64();		for(int i=0;i<test_iterations;i++)
#define testtime2       long long int end2 = GetTickCount64();	    double elapsed2 = (end2 - begin2)*1e-3;		printf("Time measured: %.7f seconds.\n", elapsed2/1000);
#define testcount1      clock_t start_testcount = clock(); for(int i = 0; i < test_iterations; i++)
#define testcount2      clock_t end_testcount = clock();    double total_time = ((double)(end_testcount - start_testcount)) / CLOCKS_PER_SEC;    printf("总操作数: %d\n",test_iterations);    printf("总时间: %f 秒\n", total_time);    printf("操作速度: %.0f 次操作/秒\n", test_iterations / total_time);    
const int test_iterations = 10000;

int main(){
    int num;  
    while(1){
    printf("please input a number n to create a 2^n*2^n square :");
    scanf("%d", &num);
    if (num <= 0) {
        printf("the input is falied ,the error code is 1");
        return 1;
    }
    //2的0次方是1
    //2的1次方是2
    OP** op=f1(num=1<<num,0);//默认值为0
    if(op==NULL) return -1;
    fill_square(num,op,0,0,0);
    if(num<=32){
    print_square(num,op);
               }
    release_square(num,op);
    testtime1{
        op=f1(num,0);//默认值为0
        if(op==NULL) return -1;
        fill_square(num,op,0,0,0);
        release_square(num,op);
    }testtime2
    testcount1{
        op=f1(num,0);//默认值为0
        if(op==NULL) return -1;
        fill_square(num,op,0,0,0);
        release_square(num,op);
    }testcount2;
}    return 0;
}

/// @brief print_square
/// @param num 
/// @param op 
void  print_square(int num,OP** op){
printf("the square is :\n");
      for(int i=0;i<num;i++){
			for(int j=0;j<num;j++){
				printf(THER,op[i][j]);
			}
			printf("\n");
	  }
}

/// @brief create a square
/// @param num int
/// @param normal 类型OP 宏定义
/// @return 一个方阵，num*num大小，有一个特殊元素，位置随机
OP** f1(int num,OP normal)
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
	return square;
}

/// @brief release_aquare
/// @param num 
/// @param op 
void release_square(int num,OP** op){
	      for(int i=0;i<num;i++){
			for(int j=0;j<num;j++){
			}
			free(op[i]);
	  }
	  free(op);
}

/// @brief 
/// @param num ^2 is the size of the square
/// @param op  defoult is 0
/// @param x_plus defoult is 0
/// @param y_plus defoult is 0
/// @param base defoult is 0
void fill_square(int num,OP** op,int x_plus,int y_plus,int base){
    if(num==2){
        op[0+x_plus][0+y_plus]=1+base;op[0+x_plus][1+y_plus]=2+base;
        op[1+x_plus][0+y_plus]=2+base;op[1+x_plus][1+y_plus]=1+base;
        return;
    }
    else if(num==1){
        system("pause");
        printf_s(" error : code num is 1");
        return;
    }
    num=num>>1;
    fill_square(num,op,x_plus,y_plus,base);
    fill_square(num,op,x_plus,y_plus+num,base+num);
    fill_square(num,op,x_plus+num,y_plus,base+num);  
    fill_square(num,op,x_plus+num,y_plus+num,base);
}