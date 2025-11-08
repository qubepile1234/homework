#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

const int test_times = 1000;

typedef struct
{
    int a;
    int b;
    int weight;
} edge;

// 函数声明
void printArray(edge* arr, int n);
edge* scanf_num(int num, int point_num);
void dijkstra(int** graph, int point_num, int start_vertex);

/// @brief 有向图Dijkstra算法实现
/// @param array 边数组
/// @param num 边数量
/// @param point_num 顶点数量
void f1(edge * array, int num, int point_num){
    printf("执行有向图Dijkstra算法，顶点数: %d, 边数: %d\n", point_num, num);
    
    // 分配邻接矩阵
    int** graph = (int **)malloc(sizeof(int *) * point_num);
    if(graph == NULL){
        printf("内存分配失败\n");
        return;
    }
    
    for(int i = 0; i < point_num; i++){
        graph[i] = (int *)malloc(sizeof(int) * point_num);
        if(graph[i] == NULL){
            printf("内存分配失败\n");
            // 释放之前分配的内存
            for(int j = 0; j < i; j++){
                free(graph[j]);
            }
            free(graph);
            return;
        }
    }
    
    // 初始化邻接矩阵
    for(int i = 0; i < point_num; i++){
        for(int j = 0; j < point_num; j++){
            if(i == j) 
                graph[i][j] = 0;
            else
                graph[i][j] = INT_MAX;
        }
    }
    
    // 填充邻接矩阵（有向图，只设置单向）
    for(int k = 0; k < num; k++){
        int i = array[k].a - 1; // 转换为0-based索引
        int j = array[k].b - 1;
        if(i >= 0 && i < point_num && j >= 0 && j < point_num){
            if(array[k].weight < graph[i][j]){
                graph[i][j] = array[k].weight;
                // 注意：有向图不设置反向边 graph[j][i]
            }
        }
    }
    
    // 打印邻接矩阵
    printf("\n有向图邻接矩阵:\n");
    printf("    ");
    for(int i = 0; i < point_num; i++){
        printf("%3d ", i+1);
    }
    printf("\n");
    
    for(int i = 0; i < point_num; i++){
        printf("%3d ", i+1);
        for(int j = 0; j < point_num; j++){
            if(graph[i][j] == INT_MAX)
                printf(" INF");
            else
                printf("%4d", graph[i][j]);
        }
        printf("\n");
    }
    
    // 选择起点进行Dijkstra计算
    printf("\n请输入起点顶点编号(1-%d): ", point_num);
    int start_vertex;
    scanf("%d", &start_vertex);
    
    if(start_vertex < 1 || start_vertex > point_num){
        printf("输入错误，顶点编号应在1-%d范围内\n", point_num);
    } else {
        dijkstra(graph, point_num, start_vertex - 1);
    }
    
    // 释放内存
    for(int i = 0; i < point_num; i++){
        free(graph[i]);
    }
    free(graph);
}

/// @brief Dijkstra算法实现
/// @param graph 邻接矩阵
/// @param point_num 顶点数量
/// @param start_vertex 起点（0-based索引）
void dijkstra(int** graph, int point_num, int start_vertex) {
    int* dist = (int*)malloc(point_num * sizeof(int));  // 最短距离数组
    int* visited = (int*)malloc(point_num * sizeof(int)); // 访问标记数组
    int* prev = (int*)malloc(point_num * sizeof(int));  // 前驱节点数组
    
    if(dist == NULL || visited == NULL || prev == NULL){
        printf("内存分配失败\n");
        free(dist);
        free(visited);
        free(prev);
        return;
    }
    
    // 初始化
    for(int i = 0; i < point_num; i++) {
        dist[i] = INT_MAX;//代表当前距离
        visited[i] = 0;//0代表未经过
        prev[i] = -1;//前节点
    }
    dist[start_vertex] = 0;//到自己为0，到自己前去节点为-1
    
    printf("\nDijkstra算法执行过程:\n");
    
    // 主循环
    for(int count = 0; count < point_num - 1; count++) {
        // 找到未访问顶点中距离最小的
        int min_dist = INT_MAX;
        int u = -1;
        
        for(int v = 0; v < point_num; v++) {
            if(!visited[v] && dist[v] < min_dist) {//每次从未访问的顶点中选取距离最小的顶点u，标记为已访问
                min_dist = dist[v];
                u = v;
            }
        }
        
        if(u == -1) break; // 所有可达顶点都已处理
        
        visited[u] = 1;//每次从未访问的顶点中选取距离最小的顶点u，标记为已访问
        printf("选择顶点 %d, 距离 = %d\n", u+1, dist[u]);
        
        // 更新相邻顶点的距离
        for(int v = 0; v < point_num; v++) {
            if(!visited[v] && graph[u][v] != INT_MAX) {
                int new_dist = dist[u] + graph[u][v];
                if(new_dist < dist[v]) {
                    dist[v] = new_dist;
                    prev[v] = u;
                    printf("  更新顶点 %d: 新距离 = %d (经过顶点 %d)\n", v+1, new_dist, u+1);
                }
            }
        }
    }//对于u的每一个邻居v，如果通过u到v的距离比当前已知的距离小，则更新v的距离。
    
    // 打印最终结果
    printf("\n从顶点 %d 到各顶点的最短距离:\n", start_vertex + 1);
    for(int i = 0; i < point_num; i++) {
        if(dist[i] == INT_MAX) {
            printf("顶点 %d: 不可达\n", i + 1);
        } else {
            printf("顶点 %d: 距离 = %d, 路径: ", i + 1, dist[i]);
            
            // 打印路径
            int path[point_num];
            int path_len = 0;
            int current = i;
            
            while(current != -1) {
                path[path_len++] = current;
                current = prev[current];
            }
            
            for(int j = path_len - 1; j >= 0; j--) {
                printf("%d", path[j] + 1);
                if(j > 0) printf(" -> ");
            }
            printf("\n");
        }
    }
    
    free(dist);
    free(visited);
    free(prev);
}

// 打印边数组
void printArray(edge* arr, int n) {
    printf("[\n");
    for (int i = 0; i < n; i++) {
        printf("  边 %d: %d -> %d, 权重: %d", 
               i+1, arr[i].a, arr[i].b, arr[i].weight);
        if (i < n - 1) printf(",\n");
    }
    printf("\n]\n");
}

edge* scanf_num(int num, int point_num) {
    edge* arr = (edge*)malloc(sizeof(edge) * num);
    if (arr == NULL) {
        printf("内存分配失败。\n");
        return NULL;
    }
    
    printf("请输入 %d 个有向边，每个边输入格式为: 起点 终点 权重\n", num);
    for (int i = 0; i < num; i++) {
        printf("边 %d: ", i + 1);
        int temp = scanf("%d %d %d", &arr[i].a, &arr[i].b, &arr[i].weight);
        
        if(temp != 3 || arr[i].a <= 0 || arr[i].a > point_num || 
           arr[i].b <= 0 || arr[i].b > point_num || arr[i].weight < 0){
            printf("输入错误。顶点编号应在 1-%d 范围内，权重应为非负数。\n", point_num);
            free(arr);
            return NULL;
        }
    }
    return arr;
}

int main() {
    srand((unsigned int)time(NULL));
    
    while(1){
        printf("=== 有向图Dijkstra算法测试 ===\n");
        
        printf("请输入顶点个数 (输入0退出): ");
        int point_num;
        if(scanf("%d", &point_num) != 1){
            printf("输入错误。\n");
            break;
        }
        
        if(point_num == 0){
            printf("程序退出。\n");
            break;
        }
        
        if(point_num < 0){
            printf("输入错误，顶点数应 > 0。\n");
            continue;
        }
        
        printf("请输入边的数目: ");
        int num;
        if(scanf("%d", &num) != 1 || num <= 0){
            printf("输入错误，边数应 > 0。\n");
            continue;
        }
        
        edge* userArray = scanf_num(num, point_num);
        if(userArray == NULL){
            continue;
        }
        
        printf("您输入的边数组是: ");
        printArray(userArray, num);
        
        f1(userArray, num, point_num);
        
        free(userArray);
        
        printf("\n是否继续测试? (1-继续, 0-退出): ");
        int continue_test;
        scanf("%d", &continue_test);
        if(continue_test == 0){
            break;
        }
    }
    
    printf("程序执行完毕。\n");
    system("pause");
    return 0;
}