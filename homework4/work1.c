#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sysinfoapi.h>

#define MAX_SIZE 100
#define OP int //目标数据类型
OP** f1(int num,OP normal); 
 //生成一个num*num的方阵，op为其中元素的数据类型，返回op**,支持方阵中有一个随机位置的特殊元素
void release_square(int num,OP** op);
 //释放方阵内存

 
#define testtime1  	    long long int begin2 = GetTickCount64();		for(int i=0;i<test_iterations;i++)
#define testtime2       long long int end2 = GetTickCount64();	    double elapsed2 = (end2 - begin2)*1e-3;		printf("Time measured: %.7f seconds.\n", elapsed2/1000);
#define testcount1      clock_t start_testcount = clock(); for(int i = 0; i < test_iterations; i++)
#define testcount2      clock_t end_testcount = clock();    double total_time = ((double)(end_testcount - start_testcount)) / CLOCKS_PER_SEC;    printf("总操作数: %d\n",test_iterations);    printf("总时间: %f 秒\n", total_time);    printf("操作速度: %.0f 次操作/秒\n", test_iterations / total_time);    
const int test_iterations = 10000;




///动态规划求解矩阵连乘问题
///@param p 矩阵维度数组
///@param n 矩阵个数     
///@param m 存储最小乘法次数的矩阵
///@param s 存储分割点的矩阵 
void matrixChainOrder(int p[], int n, int** m, int** s) {
    int i, j, k, l, q;
    //@ i 是链的起始位置
    //@ j 是链的结束位置
    //@ k 是分割点
    //@ l 是链的长度
    //@ q 是当前计算的乘法次数

    // 对角线初始化为0（单个矩阵不需要乘法）
    for (i = 1; i <= n; i++) {
        m[i][i] = 0;
    }
    
    // l是链长度
    for (l = 2; l <= n; l++) {
        for (i = 1; i <= n - l + 1; i++) {
            j = i + l - 1;// 计算链的结束位置
            m[i][j] = INT_MAX;// 初始化为最大值
            
            for (k = i; k <= j - 1; k++) {// 遍历所有可能的分割点
                // 计算乘法次数
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];// 计算当前分割点的乘法次数
                //m[i][k]：计算从矩阵 i 到矩阵 k 的最少乘法次数。
                //m[k+1][j]：计算从矩阵 k+1 到矩阵 j 的最少乘法次数。
                //p[i-1] * p[k] * p[j]：计算将两个结果矩阵相乘所需的乘法次数。
                //其中，第一个矩阵的维度是 p[i-1] × p[k]，第二个矩阵的维度是 p[k] × p[j]，因此两个矩阵相乘的乘法次数为 p[i-1] * p[k] * p[j]。
                //m[i][j]：存储从矩阵 i 到矩阵 j 的最少乘法次数。
                //s[i][j]：存储在计算从矩阵 i 到矩阵 j 的最优括号化方案时的分割点 k。
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;  // 记录分割点
                }
            }
        }
    }
}


void brute_force_matrixChainOrder(int p[], int n, int m[MAX_SIZE][MAX_SIZE], int s[MAX_SIZE][MAX_SIZE]) {
    int i, j, k, l, q;

    // 对角线初始化为0（单个矩阵不需要乘法）
    for (i = 1; i <= n; i++) {
        m[i][i] = 0;
    }
          l=n;
           i=1;// 计算链的起始位置
           j=i+l-1;// 计算链的结束位置
        for(int i =1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                m[i][j]=INT_MAX;
            }
        }
            for (k = i; k <= j - 1; k++) {// 遍历所有可能的分割点
                // 计算乘法次数
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];// 计算当前分割点的乘法次数
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;  // 记录分割点
                }
    }
}

// 打印最优括号化方案
void printOptimalParens(int** s, int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimalParens(s, i, s[i][j]);
        printOptimalParens(s, s[i][j] + 1, j);
        printf(")");
    }
}

// 打印矩阵
void printMatrix(int** mat, int n) {
    printf("m矩阵（最小乘法次数）:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j >= i) {
                printf("%8d", mat[i][j]);
            } else {
                printf("        ");
            }
        }
        printf("\n");
    }
}

int main() {
    // 矩阵维度数组：A1:30×35, A2:35×15, A3:15×5, A4:5×10, A5:10×20, A6:20×25
    // p[0]=30, p[1]=35, p[2]=15, p[3]=5, p[4]=10, p[5]=20, p[6]=25
    // int p[] = {30, 35, 15, 5, 10, 20, 25};
    // int n = sizeof(p) / sizeof(p[0]) - 1;  // 矩阵个数
    
    int m[MAX_SIZE][MAX_SIZE] = {0};  // 存储最小乘法次数
    int s[MAX_SIZE][MAX_SIZE] = {0};  // 存储分割点
    printf("scanf a num: ");
    int num;//矩阵个数
    scanf("%d",&num);
    int *p2=(int *)malloc((num+1)*sizeof(int));
    if(p2==NULL) return -1;
    printf("scanf n+1 nums: ");
    //num个矩阵需要num+1个矩阵维度
    for(int i=0;i<=num;i++){
        scanf("%d",&p2[i]);
    }
    
    if(num<=0){
        printf("the input is falied ,the error code is 1");
        return 1;
    }
    OP** m2=f1(num+1,0);//默认值为0
    if(m2==NULL) return -1;
    OP** s2=f1(num+1,0);//默认值为0
    if(s2==NULL) return -1;

    printf("矩阵链信息:\n");
    for (int i = 0; i < num; i++) {
        printf("A%d: %d×%d\n", i + 1, p2[i], p2[i + 1]);
    }
    printf("\n");
    
    // 计算最优解
    matrixChainOrder(p2, num, m2, s2);
    
    // 输出结果
    printf("最少乘法次数: %d\n", m2[1][num]);
    printf("\n");
    
    printf("最优计算顺序: ");
    printOptimalParens(s2, 1, num);
    printf("\n\n");
    
    // 打印m矩阵和s矩阵
    printMatrix(m2, num);

    printf("\ns矩阵（分割点）:\n");
    for (int i = 1; i <= num; i++) {
        for (int j = 1; j <= num; j++) {
            if (j > i) {
                printf("%4d", s[i][j]);
            } else {
                printf("    ");
            }
        }
        printf("\n");
    }
    release_square(num,m2);
    release_square(num,s2);
    return 0;
}

/// @brief // create a square
/// @param num 
/// @param normal 
/// @return 
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

/// @brief release_square
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