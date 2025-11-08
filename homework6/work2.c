#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define END_CHAR '\0'
//必须有\0结尾，否则字符串无法正确处理
#define THE_NUM "Aa"

const int test_times = 100000;


//设计依据    归纳法
// LCS(x,y) =?
// (1) LCS(x - 1,y - 1) + 1? ? ? （Ax ＝ By）
// (2) max(LCS(x – 1, y) , LCS(x, y – 1))? ? （Ax ≠ By）

// 返回两个整数中的较大值
int max(int a, int b) {
    return (a > b) ? a : b;
}

/// @brief 计算两个字符串的最长公共子序列
/// @param X 是第一个字符串
/// @param Y 是第二个字符串
/// @param m 是X的长度
/// @param n 是Y的长度
void longestCommonSubsequence(char *X, char *Y, int m, int n,int print_yes) {
    // 创建二维数组L来存储子问题的解，L[i][j]表示X[0..i-1]和Y[0..j-1]的LCS长度
    //LCS是Longest Common Subsequence的缩写  最长公共子序列
    int **L = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++) {
        L[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    // 构建L[m+1][n+1]表
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                L[i][j] = 0;
                // 初始化第一行和第一列为0
            } else if (X[i - 1] == Y[j - 1]) {
                //如果字符相等，则在对角线方向的下一位上加1
                L[i][j] = L[i - 1][j - 1] + 1;
            } else {
                //如果不相等，则取上方或左方的最大值
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
            }
        }
    }

    // LCS的长度存储在L[m][n]中
    int length = L[m][n];
    
    // 回溯找出LCS
    char *lcs = (char *)malloc((length + 1) * sizeof(char));
    lcs[length] = END_CHAR; // 设置字符串结束符

    int i = m, j = n;
    int index = length - 1;
// 从L[m][n]开始回溯
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            // 如果字符相等，则该字符是LCS的一部分
            lcs[index] = X[i - 1];
            i--;
            j--;
            index--;
        } else if (L[i - 1][j] > L[i][j - 1]) {
            // 向上移动
            i--;
        } else {
            // 向左移动
            j--;
        }
    }
//END_CHAR是字符串结束符，很正确
if(print_yes==1)
{    printf("最长公共子序列的长度: %d\n", length);
    printf("最长公共子序列: %s\n", lcs);
}

    // 释放内存
    for (int i = 0; i <= m; i++) {
        free(L[i]);
    }
    free(L);
    free(lcs);
}


/// @brief 生成随机序列
/// @param length 长度为length的随机序列
/// @return 
char* generateRandomSequence(int length) {
    char *sequence = (char *)malloc((length + 1) * sizeof(char));
    const char charset[] = THE_NUM;
    
    for (int i = 0; i < length; i++) {
        //因为从0开始，所以要减1
        int key = rand() % (sizeof(charset) - 1);
        sequence[i] = charset[key];
    }
    // 设置字符串结束符
    sequence[length] = END_CHAR;
    
    return sequence;
}

int main() {
    // 设置随机种子
    srand((unsigned int)time(NULL));

    // 生成两个不同长度的随机序列
    int len1 = 10 + rand() % 11; // 长度10-20
    int len2 = 15 + rand() % 11; // 长度15-25

    // 生成随机序列
    char *sequence1 = generateRandomSequence(len1);
    char *sequence2 = generateRandomSequence(len2);

    // 输出生成的序列
    printf("序列1 (长度%d): %s\n", len1, sequence1);
    printf("序列2 (长度%d): %s\n", len2, sequence2);
    printf("\n");
    // 计算并输出最长公共子序列
    longestCommonSubsequence(sequence1, sequence2, len1, len2,1);
       clock_t start = clock();
        for(int j=0;j<test_times;j++) {
              longestCommonSubsequence(sequence1, sequence2, len1, len2,0);
        }
        clock_t end = clock();
        double time1 = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;
        printf("%.6fms\n",time1/test_times);

    // 释放内存
    free(sequence1);
    free(sequence2);

    return 0;
}
