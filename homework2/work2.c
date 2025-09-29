#include <stdio.h>
#include <stdlib.h>
#include <sysinfoapi.h>

#define testtime1  	    long long int begin2 = GetTickCount64();		for(int i=0;i<1000;i++)
#define testtime2       long long int end2 = GetTickCount64();	    double elapsed2 = (end2 - begin2)*1e-3;		printf("Time measured: %.7f seconds.\n", elapsed2/1000);

/// @brief 合并两个已排序的子数组
/// @param arr 
/// @param left 
/// @param mid 
/// @param right 
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;  // 左子数组的大小
    int n2 = right - mid;     // 右子数组的大小
    
    // 创建临时数组
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));
    
    // 将数据复制到临时数组L和R中
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // 合并临时数组回原数组arr
    i = 0;  // 左子数组的初始索引
    j = 0;  // 右子数组的初始索引
    k = left;  // 合并后数组的初始索引
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // 复制L[]的剩余元素
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // 复制R[]的剩余元素
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    // 释放临时数组内存
    free(L);
    free(R);
}
/// @brief  合并排序主函数（分治法）
/// @param arr 
/// @param left 
/// @param right 
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // 找到中间点
        int mid = left + (right - left) / 2;
        
        // 分别对左右两部分进行排序
        mergeSort(arr, left, mid);      // 排序左半部分
        mergeSort(arr, mid + 1, right); // 排序右半部分
        
        // 合并已排序的两部分
        merge(arr, left, mid, right);
    }
}

// 打印数组
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// 主函数
int main() {
    int n;
    
    printf("请输入要排序的数字个数: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("请输入一个正整数！\n");
        return 1;
    }
    
    // 动态分配数组内存
    int *arr = (int*)malloc(n * sizeof(int));
    
    if (arr == NULL) {
        printf("内存分配失败！\n");
        return 1;
    }
    
    printf("请输入 %d 个整数:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("原始数组: ");
    printArray(arr, n);
    
    // 执行合并排序
    mergeSort(arr, 0, n - 1);
    
    printf("排序后的数组: ");
    printArray(arr, n);
            testtime1{
    mergeSort(arr, 0, n - 1);
             }testtime2
    // 释放内存
    free(arr);
    
    return 0;
}