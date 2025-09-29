# include<stdio.h>
#include <stdlib.h>
#include <sysinfoapi.h>
#include<time.h>
#define OP BOOLEAN //目标数据类型
OP** f1(int num,OP normal,OP different); 
 //生成一个num*num的方阵，op为其中元素的数据类型，返回op**,支持方阵中有一个随机位置的特殊元素
 //随机位置由此实现    srand((unsigned)time(NULL));   int random = rand()%num*num;
void release_square(int num,OP** op);
void  release_print_square(int num,OP** op);
void print_square(int num,OP** op);
 //打印出op方阵
#define THER "%d  "
//配合使用

#define testtime1  	    long long int begin2 = GetTickCount64();		for(int i=0;i<10000;i++)
#define testtime2       long long int end2 = GetTickCount64();	    double elapsed2 = (end2 - begin2)*1e-3;		printf("Time measured: %.7f seconds.\n", elapsed2/10000);
//配合void print_square(int num,OP**);使用，打印你想要的类型ther为你想要的printf中的内容
int innum();
void fillsquare(int num,OP normal,OP different,OP** op,int num_origin,int,int,int,int);

int main(){	
    	while(1){
    	int num=innum();
        printf("you input the num is %d\n",num);
        if (num<=0)printf("the input is falied ,the error code is%d\n",num);
        else 
			{	
	    OP** op=f1(num,TRUE,FALSE);
        if(op==NULL) return -1;
		print_square(num,op);
        fillsquare(num,TRUE,FALSE,op,num,0,0,-1,-1);
		release_square(num,op);
	    testtime1{
			OP** optest=f1(num,TRUE,FALSE);
		    if(optest==NULL){return -1;}
            fillsquare(num,TRUE,FALSE,op,num,0,0,-1,-1);
		    release_square(num,optest);
		         }testtime2
		//  long long int begin2 = GetTickCount64();
		// for(int i=0;i<1000;i++){
        //   OP** optest=f1(num,TRUE,FALSE);
		//   if(optest==NULL){return -1;}
        // fillsquare(num,TRUE,FALSE,op,num,0,0);
		//    release_square(num,optest);
		//  }
		//  long long int end2 = GetTickCount64();
	    // double elapsed2 = (end2 - begin2)*1e-3;
		// 		printf("Time measured: %.14f seconds.\n", elapsed2/1000);
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
    int random = rand()%(num*num);
	square[random/num][random%num]=different;
	// printf("%d  %d   %d",random/num,random%num,random); 测试用
	return square;
}
/// @brief 
/// @details print_square(num_origin,op);//呈现过程
/// @param num 本次问题的规模
/// @param normal 
/// @param different 
/// @param op **
/// @param num_origin 问题原本的规模，用于打印求解过程用
/// @param beginfrom_i 为了处理四个子问题的工具
/// @param beginfrom_j 同理
/// @param pointx 特殊点x
/// @param pointy 特殊点y
void fillsquare(int num,OP normal,OP different,OP** op,int num_origin,int beginfrom_i,int beginfrom_j,int pointx,int pointy){
    int ii,jj;
	int count=0;
if(pointx==-1&&pointy==-1){//特殊点未知
	for(int i=0;i<num;i++){
		for(int j=0;j<num;j++){
			if(op[i+beginfrom_i][j+beginfrom_j]==different){
				ii=i;jj=j;
				pointx=i+beginfrom_i;pointy=j+beginfrom_j;
				count++;
			}
		}
	 }}
	 else {ii=pointx-beginfrom_i;jj=pointy-beginfrom_j;count++;}
	 //特殊点已知
	 if(count>1){printf("error,the code is count-1");system("pause");}
	 if(count==0||num==1){return;}
	 num=num>>1;
	 //这里的num是数组的num*num,而不是数组从零开始计数应有的位置
	 int type=0;
	 num--;
				if(ii>num){op[num+beginfrom_i][num+beginfrom_j]=different;
					op[num+beginfrom_i][num+beginfrom_j+1]=different;
					type++;type++;}//特殊点在三四象限
				else{op[num+beginfrom_i+1][num+beginfrom_j]=different;
					op[num+beginfrom_i+1][num+beginfrom_j+1]=different;}
                if(jj>num){op[num+beginfrom_i][num+beginfrom_j]=different;
					op[num+beginfrom_i+1][num+beginfrom_j]=different;
				type++;}//特殊点在一四象限
				else{op[num+beginfrom_i][num+beginfrom_j+1]=different;
					op[num+beginfrom_i+1][num+beginfrom_j+1]=different;}
	num++;




			//  print_square(num_origin,op);//呈现过程
			
			
			
			
			 if(num==0){return;}

			switch (type)
			{
			case 0:
			{fillsquare(num,normal,different,op,num_origin,beginfrom_i+0,beginfrom_j+0,pointx,pointy);
			fillsquare(num,normal,different,op,num_origin,beginfrom_i,beginfrom_j+num,num-1+beginfrom_i,num+beginfrom_j);
			fillsquare(num,normal,different,op,num_origin,beginfrom_i+num,beginfrom_j,num+beginfrom_i,num-1+beginfrom_j);
			fillsquare(num,normal,different,op,num_origin,beginfrom_i+num,beginfrom_j+num,num+beginfrom_i,num+beginfrom_j);}
				break;
			case 1:
			{fillsquare(num,normal,different,op,num_origin,beginfrom_i+0,beginfrom_j+0,num-1+beginfrom_i,num-1+beginfrom_j);
			fillsquare(num,normal,different,op,num_origin,beginfrom_i,beginfrom_j+num,pointx,pointy);
			fillsquare(num,normal,different,op,num_origin,beginfrom_i+num,beginfrom_j,num+beginfrom_i,num-1+beginfrom_j);
			fillsquare(num,normal,different,op,num_origin,beginfrom_i+num,beginfrom_j+num,num+beginfrom_i,num+beginfrom_j);}
			    break;
            case 2:
			{fillsquare(num,normal,different,op,num_origin,beginfrom_i+0,beginfrom_j+0,num-1+beginfrom_i,num-1+beginfrom_j);
			fillsquare(num,normal,different,op,num_origin,beginfrom_i,beginfrom_j+num,num-1+beginfrom_i,num+beginfrom_j);
			fillsquare(num,normal,different,op,num_origin,beginfrom_i+num,beginfrom_j,pointx,pointy);
			fillsquare(num,normal,different,op,num_origin,beginfrom_i+num,beginfrom_j+num,num+beginfrom_i,num+beginfrom_j);}
			    break;
            case 3:
			{fillsquare(num,normal,different,op,num_origin,beginfrom_i+0,beginfrom_j+0,num-1+beginfrom_i,num-1+beginfrom_j);
			fillsquare(num,normal,different,op,num_origin,beginfrom_i,beginfrom_j+num,num-1+beginfrom_i,num+beginfrom_j);
			fillsquare(num,normal,different,op,num_origin,beginfrom_i+num,beginfrom_j,num+beginfrom_i,num-1+beginfrom_j);
			fillsquare(num,normal,different,op,num_origin,beginfrom_i+num,beginfrom_j+num,pointx,pointy);}
			     break;
			default:
			system("pause");
				break;
			}
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
/// @brief release_print_square
/// @param num 
/// @param op 
void  release_print_square(int num,OP** op){
      for(int i=0;i<num;i++){
			for(int j=0;j<num;j++){
				printf("the square is :");
				printf(THER,op[i][j]);
			}
			free(op[i]);
         printf("\n");
	  }
	  free(op);
}