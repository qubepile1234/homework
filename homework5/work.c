#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#include <sysinfoapi.h>
#define max(a, b) (((a) > (b)) ? (a) : (b))
int f1(int num,int *value,int* flag,int capacity);
void release(int *value,int* weight);
void printOptimalSolution(int W, int* wt, int* val, int n, int* selected, int max_value);
int knapsack(int W, int* wt, int* val, int n, int* selected);
int main() {
    while(1){
    printf("enter the number of items:(input 0 to exit)\n");
    int num;
    scanf("%d", &num);
    if(num==0){
        break;
    }
    int *v_list = (int *)malloc(sizeof(int)*num);
    if (v_list == NULL) {
        printf("内存分配失败。\n");
        return -1;
    }
    int *w_list = (int *)malloc(sizeof(int)*num);
    if (w_list == NULL) {
        printf("内存分配失败。\n");
        free(v_list);
        return -1;
    }
    int *selected = (int *)malloc(sizeof(int) * num);
    if (selected == NULL) {
        printf("内存分配失败。\n");
        free(v_list);
        free(w_list);
        return -1;
    }
    for (int i = 0; i < num; i++) {
        printf("请输入第%d个物品的value and weight：\n", i + 1);
        scanf("%d",v_list+i);
        scanf("%d",w_list+i);
        selected[i] = 0;
    }
    printf("请输入背包容量：\n");
    int capacity;
    scanf("%d", &capacity);
    f1(num,v_list,w_list,capacity);
    int count = 0;
    int sum=f1(num, v_list, w_list, capacity);
    printf("the sum is: %d\n", sum);
        // 使用标准解法（记录最优解）
    int max_value = knapsack(capacity, w_list, v_list, num, selected);
    
    // 打印最优解详情
    printOptimalSolution(capacity, w_list, v_list, num, selected, max_value);

     long times=300000;
	 long long int begin = GetTickCount64();
	 for(int i=0;i<times;i++){
	 	knapsack(capacity, w_list, v_list, num, selected);
	 } 
	 long long int end = GetTickCount64();
	 double elapsed = (end - begin)*1e-3;
    printf("Time1 measured: %.6f seconds.\n", elapsed);
    
	  begin = GetTickCount64();
	 for(int i=0;i<times;i++){
	 	f1(num,v_list,w_list,capacity);
		 } 
	  end = GetTickCount64();
	elapsed = (end - begin)*1e-3;
    printf("Time2 measured: %.6f seconds.\n", elapsed);
    
    release(v_list,w_list);
}
}
void release(int *value,int* weight) {
    if (value != NULL && weight != NULL) {
        free(value);
        free(weight);
    }
    else {
        printf("指针为空，无法释放内存。\n");
        system("pause");
    }
}
int f1(int num,int *value,int* weight,int capacity){
    int *capacity_1 = (int *)malloc( sizeof(int)* (capacity+ 1));
    if (capacity_1 == NULL) {
        printf("内存分配失败。\n");
        system("pause");
        return -1;
    }
    for(int w=0;w<=capacity;w++){
        capacity_1[w]=0;
    }
   for(int i=0;i<num;i++){
       for(int w=capacity;w>=weight[i];w--){
           capacity_1[w]=max(capacity_1[w],capacity_1[w-weight[i]]+value[i]);
       }
   }
int temp_capacity=capacity_1[capacity];
free(capacity_1);
return temp_capacity;
}


// 0/1背包问题的动态规划解法（返回最大价值并记录最优解）
int knapsack(int W, int* wt, int* val, int n, int* selected) {
    int i, w;
    
    // 创建动态规划表
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((W + 1) * sizeof(int));
    }
    
    // 构建动态规划表
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (wt[i - 1] <= w) {
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    
    // 回溯找出最优解（哪些物品被选中）
    int result = dp[n][W];
    int temp = result;
    int remaining_capacity = W;
    
    for (i = n; i > 0 && result > 0; i--) {
        if (result != dp[i - 1][remaining_capacity]) {
            // 这个物品被选中
            selected[i - 1] = 1;
            result -= val[i - 1];
            remaining_capacity -= wt[i - 1];
        }
    }
    
    // 释放内存
    for (i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return temp;
}
// 打印最优解详情
void printOptimalSolution(int W, int* wt, int* val, int n, int* selected, int max_value) {
    int i;
    int total_weight = 0;
    int selected_count = 0;
    
    printf("\n=== 0/1背包问题最优解 ===\n");
    printf("背包容量: %d\n", W);
    printf("最大价值: %d\n", max_value);
    
    printf("\n物品详情:\n");
    printf("%-8s %-8s %-8s %-8s\n", "物品", "价值", "重量", "是否选中");
    printf("--------------------------------\n");
    
    for (i = 0; i < n; i++) {
        printf("%-8d %-8d %-8d %-8s\n", 
               i + 1, val[i], wt[i], 
               selected[i] ? "是" : "否");
        
        if (selected[i]) {
            total_weight += wt[i];
            selected_count++;
        }
    }
    printf("\n最优解统计:\n");
    printf("选中的物品数量: %d\n", selected_count);
    printf("总重量: %d\n", total_weight);
    printf("背包剩余容量: %d\n", W - total_weight);
    printf("总价值: %d\n", max_value);
    printf("\n");
}

