#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

const int test_times = 1000;
// 函数声明
int max3(int a, int b, int c);
int maxSubArrayDivide(int arr[], int left, int right);
int maxSubArrayDivideWrapper(int arr[], int n);
int maxSubArrayDP(int arr[], int n);
void generateRandomArray(int arr[], int n, int minVal, int maxVal);
void printArray(int arr[], int n);
int* scanf_num(int num);

// 返回三个整数中的最大值
int max3(int a, int b, int c) {
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    return c;
}

////////////////////////////////////////

// 分治法求解最大子段和
int maxSubArrayDivide(int arr[], int left, int right) {
    if (left == right) {
        //不可分割时返回单个元素，但要保证不为负数
        return arr[left] > 0 ? arr[left] : 0;
    }
    
    int mid = (left + right) / 2;
    int leftMax = maxSubArrayDivide(arr, left, mid);
    int rightMax = maxSubArrayDivide(arr, mid + 1, right);
    // 计算跨越中点的最大子段和
    int leftBorderMax = 0, leftBorderSum = 0;
    for (int i = mid; i >= left; i--) {
        //left为左边界
        leftBorderSum += arr[i];
        if (leftBorderSum > leftBorderMax) {
            //向左边数时，累计和大于最大值则刷新
            leftBorderMax = leftBorderSum;
        }
    }
    
    int rightBorderMax = 0, rightBorderSum = 0;
    for (int i = mid + 1; i <= right; i++) {
        rightBorderSum += arr[i];
        if (rightBorderSum > rightBorderMax) {
            rightBorderMax = rightBorderSum;
        }
    }
    
    int crossMax = leftBorderMax + rightBorderMax;
    
    return max3(leftMax, rightMax, crossMax);
}

// 分治法包装函数

/// @param arr 输入数组
/// @param n 数组长度
int maxSubArrayDivideWrapper(int arr[], int n) {
    if (n <= 0) return 0;
    int result = maxSubArrayDivide(arr, 0, n - 1);
    return result > 0 ? result : 0;
}

////////////////////////////////////////
/// @brief 动态规划法求解最大子段和
/// @param arr 输入数组
/// @param n 数组长度
/// @return 最大子段和
int maxSubArrayDP(int arr[], int n) {

    //如果现在累计加上下一个大于0，下一个小于0，最高值仍是最高值，但是我们无法预测下下一个，所以不能舍弃
    //如果现在累计加上下一个大于0，下一个大于0，最高值会正确更新
    //如果现在累计加上下一个小于0，累计应该被置0，且不会影响最高值

    if (n <= 0) return 0;
    
    int maxSoFar = 0;
    //如果当前结束时的最终结果
    int maxEndingHere = 0;
    //中途temp,累计与重新累计
    for (int i = 0; i < n; i++) {
        maxEndingHere = maxEndingHere + arr[i];
        
        if (maxEndingHere < 0) {
        // 如果当前和为负，则舍弃，因为不产生收益
            maxEndingHere = 0;
        }
        
        if (maxEndingHere > maxSoFar) {
            //刷新
            maxSoFar = maxEndingHere;
        }
    }
    
    return maxSoFar;
}

/// @brief 生成随机数组
/// @param arr 数组指针
/// @param n 数组长度 
/// @param minVal 随机数最小值
/// @param maxVal 随机数最大值
void generateRandomArray(int arr[], int n, int minVal, int maxVal) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % (maxVal - minVal + 1) + minVal;
    }
}

/// @brief 性能测试   调用generateRandomArray生成随机数组，然后分别测试分治法和动态规划法的运行时间
/// @param testSizes 测试数据规模（长度）数组 eg。{100, 500, 1000, 5000, 10000}
/// @param numTests 测试组数
void performanceTest(int testSizes[], int numTests) {
    printf("数据规模\t分治法时间(ms)\t动态规划时间(ms)\n");
    printf("------------------------------------------------\n");
    
    for (int i = 0; i < numTests; i++) {
        int n = testSizes[i];
        int *arr = (int *)malloc(n * sizeof(int));
        
        // 生成测试数据
        generateRandomArray(arr, n, -100, 100);
        
        // 测试分治法
        int result1 = maxSubArrayDivideWrapper(arr, n);
        clock_t start = clock();
        for(int j=0;j<test_times;j++) {
            maxSubArrayDivideWrapper(arr, n);
        }
        clock_t end = clock();
        double time1 = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;
        
        // 测试动态规划法
        int result2 = maxSubArrayDP(arr, n);
        start = clock();
        for(int j=0;j<test_times;j++) {
            maxSubArrayDP(arr, n);
        }
        end = clock();
        double time2 = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;
        
        printf("%d\t\t%.6f\t\t%.6f\n", n, time1/test_times, time2/test_times);
        
        // 验证结果一致性
        if (result1 != result2) {
            printf("错误：两种方法结果不一致！\n");
            printf("分治法结果: %-7d, 动态规划结果: %-7d\n", result1/1000, result2/1000);
        }
        
        free(arr);
    }
}

// 打印数组
void printArray(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

int main() {
    srand((unsigned int)time(NULL));
    
    int result1, result2;
    
    printf("=== 用户输入测试 ===\n");
    printf("请输入数组元素个数:\n");
    int num;
    scanf("%d", &num);
    if(num <= 0){
        printf("输入错误。\n");
        system("pause");
        return -1;
    }
    int* userArray =scanf_num(num);
    if(userArray==NULL){
        system("pause");
        return -1;
    }
    printf("您输入的数组是: ");
    printArray(userArray, num);
    result1 = maxSubArrayDivideWrapper(userArray, num);
    result2 = maxSubArrayDP(userArray, num);
    printf("分治法结果: %d\n", result1);
    printf("动态规划法结果: %d\n", result2);
    free(userArray);
    printf("\n");


    // 性能测试
    printf("=== 性能测试 ===\n");
    int testSizes[] = {100, 500, 1000, 5000, 10000};
    int numTests = sizeof(testSizes) / sizeof(testSizes[0]);
    performanceTest(testSizes, numTests);
    
    return 0;
}

/// @brief 输入num个整数，返回动态分配的数组指针
/// @param num 
/// @return 分配失败返回NULL
int* scanf_num(int num) {
    int* arr = (int*)malloc(sizeof(int) * num);
    if (arr == NULL) {
        printf("内存分配失败。\n");
        exit(-1);
    }
    int temp;
    printf("请输入 %d 个整数:\n", num);
    for (int i = 0; i < num; i++) {
        temp=scanf("%d", &arr[i]);
         if(temp!=1||arr[i]<INT_MIN||arr[i]>INT_MAX){
            printf("输入错误。\n");
            free(arr);
            arr = NULL;
            break;
        }
    }
    return arr;
}