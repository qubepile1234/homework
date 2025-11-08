#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sysinfoapi.h>  // 使用windows.h而不是sysinfoapi.h
#include <time.h>

#define MAX_SIZE 100
#define OP int //目标数据类型

// 函数声明
OP** f1(int num, OP normal); 
void release_square(int num, OP** op);
void matrixChainOrder(int p[], int n, OP** m, OP** s);
void printOptimalParens(OP** s, int i, int j);
void printMatrix(OP** mat, int n);

// 测试宏定义
#define testtime1  	    long long int begin2 = GetTickCount64();		for(int i=0;i<test_iterations;i++)
#define testtime2       long long int end2 = GetTickCount64();	    double elapsed2 = (end2 - begin2)*1e-3;		printf("Time measured: %.7f seconds.\n", elapsed2/1000);
#define testtime3  	    begin2 = GetTickCount64();		for(int i=0;i<test_iterations;i++)
#define testtime4       end2 = GetTickCount64();	    elapsed2 = (end2 - begin2)*1e-3;		printf("Time measured: %.7f seconds.\n", elapsed2/1000);
#define testcount1      clock_t start_testcount = clock(); for(int i = 0; i < test_iterations; i++)
#define testcount2      clock_t end_testcount = clock();    double total_time = ((double)(end_testcount - start_testcount)) / CLOCKS_PER_SEC;    printf("总操作数: %d\n",test_iterations);    printf("总时间: %f 秒\n", total_time);    printf("操作速度: %.0f 次操作/秒\n", test_iterations / total_time);    
#define testcount3      start_testcount = clock(); for(int i = 0; i < test_iterations; i++)
#define testcount4      end_testcount = clock();   total_time = ((double)(end_testcount - start_testcount)) / CLOCKS_PER_SEC;    printf("总操作数: %d\n",test_iterations);    printf("总时间: %f 秒\n", total_time);    printf("操作速度: %.0f 次操作/秒\n", test_iterations / total_time);    
const int test_iterations = 30000;

// 动态规划求解矩阵连乘问题
void matrixChainOrder(int p[], int n, OP** m, OP** s) {
    int i, j, k, l, q;

    // 对角线初始化为0（单个矩阵不需要乘法）
    for (i = 1; i <= n; i++) {
        m[i][i] = 0;
    }
    
    // l是链长度，i是链头，j是链尾    
    for (l = 2; l <= n; l++) {
        for (i = 1; i <= n - l + 1; i++) {
            j = i + l - 1;
            m[i][j] = INT_MAX;
            
            for (k = i; k <= j - 1; k++) {
                // 计算乘法次数
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}


  // 递归暴力解法
int brute_force_recursive(int p[], int i, int j, OP** s) {
    if (i == j) {
        return 0;
    }
    
    int min_cost = INT_MAX;
    int best_k = i;
    
    for (int k = i; k < j; k++) {
        int cost = brute_force_recursive(p, i, k, s) 
                 + brute_force_recursive(p, k + 1, j, s) 
                 + p[i - 1] * p[k] * p[j];
        
        if (cost < min_cost) {
            min_cost = cost;
            best_k = k;
        }
    }
    
    if (s != NULL) {
        s[i][j] = best_k;
    }
    
    return min_cost;
}

// 包装函数
void brute_force_matrixChainOrder(int p[], int n, OP** m, OP** s) {
    // 初始化
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if (i == j) {
                m[i][j] = 0;
            } else {
                m[i][j] = INT_MAX;
            }
        }
    }
    
    // 计算最优解
    m[1][n] = brute_force_recursive(p, 1, n, s);
}



// 打印最优括号化方案
void printOptimalParens(OP** s, int i, int j) {
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
void printMatrix(OP** mat, int n) {
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
    printf("scanf a num: ");
    int num; // 矩阵个数
    scanf("%d", &num);
    
    if(num <= 0 || num >= MAX_SIZE) {
        printf("输入错误：矩阵个数应该在1到%d之间\n", MAX_SIZE-1);
        return 1;
    }
    
    int *p2 = (int *)malloc((num + 1) * sizeof(int));
    if(p2 == NULL) return -1;
    
    printf("scanf %d nums: ", num + 1);
    for(int i = 0; i <= num; i++) {
        scanf("%d", &p2[i]);
    }
    
    // 分配动态矩阵，大小为 (num+1) x (num+1)
    OP** m2 = f1(num + 1, 0);
    if(m2 == NULL) return -1;
    OP** s2 = f1(num + 1, 0);
    if(s2 == NULL) return -1;

    printf("矩阵链信息:\n");
    for (int i = 0; i < num; i++) {
        printf("A%d: %d×%d\n", i + 1, p2[i], p2[i + 1]);
    }
    printf("\n");
    
    // 计算最优解
    //long long int begin2 = GetTickCount64();		for(int i=0;i<test_iterations;i++){
    printf("计数法\n");
    testcount1{
	matrixChainOrder(p2, num, m2, s2);
    }testcount2
    printf("计时法\n");
    testtime1{
        matrixChainOrder(p2,num,m2,s2);
    }testtime2
	//}long long int end2 = GetTickCount64();	    double elapsed2 = (end2 - begin2)*1e-3;		printf("Time measured: %.7f seconds.\n", elapsed2/1000);
    
    
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
                printf("%4d", s2[i][j]);
            } else {
                printf("    ");
            }
        }
        printf("\n");
    }
    /////////////////////

    printf("计数法\n");
    testcount3{
    brute_force_matrixChainOrder(p2, num, m2, s2);
    }testcount4
    printf("计时法\n");
    testtime3{
    brute_force_matrixChainOrder(p2, num, m2, s2);
    }testtime4
    // 输出结果
    printf("brute最少乘法次数: %d\n", m2[1][num]);
    printf("\n");
    
    printf("brute最优计算顺序: ");
    printOptimalParens(s2, 1, num);
    printf("\n\n");
    // 打印m矩阵和s矩阵
    printMatrix(m2, num);

    printf("\ns矩阵（分割点）:\n");
    for (int i = 1; i <= num; i++) {
        for (int j = 1; j <= num; j++) {
            if (j > i) {
                printf("%4d", s2[i][j]);
            } else {
                printf("    ");
            }
        }
        printf("\n");
    }
    
    
    // 释放内存
    release_square(num + 1, m2);
    release_square(num + 1, s2);
    free(p2);
    
    return 0;
}

// 生成一个num*num的方阵
OP** f1(int num, OP normal) {
    OP **square = (OP **)malloc(num * sizeof(OP *));
    if (square == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    
    for (int i = 0; i < num; i++) {
        square[i] = (OP *)malloc(num * sizeof(OP));
        if (square[i] == NULL) {
            printf("Memory allocation failed.\n");
            for (int j = 0; j < i; j++) {
                free(square[j]);
            }
            free(square);
            return NULL;
        }
        
        // 初始化
        for(int j = 0; j < num; j++) {
            square[i][j] = normal;
        }
    }
    return square;
}

// 释放方阵内存
void release_square(int num, OP** op) {
    if(op == NULL) return;
    
    for(int i = 0; i < num; i++) {
        free(op[i]);
    }
    free(op);
}

