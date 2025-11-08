#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>

const int test_times = 1000;
// 函数声明
int maxSubArrayDP(int arr[], int n);
void printArray(int arr[], int n);
int* scanf_num(int num);


int compare_w(const void* a,const void* b){
    int* xx=(int*)a;
    int* yy=(int*)b;
    // int x=*xx;
    // int y=*yy;
    // return x<=y?x:y;
    // int r= (x<=y?x:y);
    return *xx-*yy;
}

/// @brief 解决一个问题，重量限度为max_w，共num个物品，i个物品重量为array[i]，将最多物品装载
/// @param array 
/// @param num 
/// @param max_w 
void f1(int * array,int num,int max_w){
    //从小到大快速排顺序
    printf("决定装：");
        qsort(array,num, sizeof(int), compare_w);
        printf("排序完后是：");
        printArray(array,num);
        int have_w=0;
    for(int i=0;i<num;i++){
        if((have_w+array[i])<=max_w){
            printf("%4d",array[i]);
            have_w += array[i];
        }
        else break;
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

    printf("please input the max_weight");
    int max_w;
    scanf("%d",&max_w);
    f1(userArray,num,max_w);
    
    free(userArray);
    printf("\n");
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

