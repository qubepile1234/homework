#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

const int test_times = 1000;

typedef struct
{
    int a;
    int b;
    int weight; // 添加权重字段，用于图算法
    int choose;//0表示未被选择,默认应为0
} edge;

// 函数声明
int maxSubArrayDP(int arr[], int n);
void printArray(edge* arr, int n);
edge* scanf_num(int num, int point_num);
void dijkstra(int** graph, int point_num, int start_vertex);


int compare_w(const void* a, const void* b){
    edge* edge1 = (edge*)a;
    edge* edge2 = (edge*)b;
    return edge1->weight - edge2->weight;
}

/// @brief dijkstra 或其它图算法,没有0号端点
/// @param array 边数组
/// @param num 边数量
void f1(edge * array, int num, int point_num){
    int *have=(int *)malloc(sizeof(int )*num);
    
    printf("执行图算法，边数: %d\n", num);
    
    // 示例：按权重排序边
    qsort(array, num, sizeof(edge), compare_w);
    
    printf("按权重排序后的边:\n");
    for(int i = 0; i < num; i++){
        printf("边 %d-%d, 权重: %d\n", array[i].a, array[i].b, array[i].weight);
    }

    for(int i=0;i<num;i++){
    	have[i]=0;
	}
	int have_point_num=2;
	have[array[0].a]=1;
	have[array[0].b]=1;
	printf("result\n");
	printf("边 %d-%d, 权重: %d\n", array[0].a, array[0].b, array[0].weight);
	while(have_point_num<point_num){
    for(int i=1;i<num;i++){
    	if(have[array[i].a]==1&&have[array[i].b]==0)
    	{have[array[i].b]=1;
    	have_point_num++;
    	printf("边 %d-%d, 权重: %d\n", array[i].a, array[i].b, array[i].weight);
    	break;
		}
		if(have[array[i].a]==0&&have[array[i].b]==1)
    	{have[array[i].a]=1;
    	have_point_num++;
    	printf("边 %d-%d, 权重: %d\n", array[i].a, array[i].b, array[i].weight);
    	break;
		}
	}
	} 
	free(have);
}

/// @brief 有向图Dijkstra算法实现
/// @param array 边数组
/// @param num 边数量
/// @param point_num 顶点数量
void f2(edge * array, int num, int point_num){
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


// 打印数组
void printArray(edge* arr, int n) {
    printf("[\n");
    for (int i = 0; i < n; i++) {
        printf("  边 %d: 端点 %d - %d, 权重: %d", 
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
    
    printf("请输入 %d 个边，每个边输入格式为: 端点1 端点2 权重\n", num);
    for (int i = 0; i < num; i++) {
        printf("边 %d: ", i + 1);
        int temp = scanf("%d %d %d", &arr[i].a, &arr[i].b, &arr[i].weight);
         arr[i].choose=0;
        if(temp != 3 || arr[i].a <= 0 || arr[i].a > point_num || 
           arr[i].b <= 0 || arr[i].b > point_num || arr[i].weight < 0){
            printf("输入错误。端点应在 1-%d 范围内，权重应为非负数。\n", point_num);
            free(arr);
            return NULL;
        }
    }
    return arr;
}

void f3(edge* array,int num,int point_num,int first_point){
    int* dist = (int*)malloc(point_num * sizeof(int));  // 最短距离数组
    int* visited = (int*)malloc(point_num * sizeof(int)); // 访问标记数组
    int* prev = (int*)malloc(point_num * sizeof(int));  // 前驱节点数组
    //初始化    
        for(int i=0;i<point_num;i++){
            dist[i]=INT_MAX;
            visited[i]=0;
            prev[i]=first_point;
            
        }
        dist[first_point-1]=0;//到自己距离为0
        prev[first_point-1]=-1;//自己前节点为-1
        visited[first_point-1]=1;//自己加入
        //先把直接连的填一下
                for(int k=0;k<num;k++){
                    if(first_point==array[k].a){
                        dist[array[k].b-1]=array[k].weight;
                }}
        int temp;
            while(1){
        // 选择未访问顶点中距离最小的顶点
        int u = -1;
        int min_dist = INT_MAX;
        for (int i = 0; i < point_num; i++) {
            if (!visited[i] && dist[i] < min_dist) {
                min_dist = dist[i];
                u = i;
            }
        }
        // 如果找不到，说明剩下的顶点不可达
        if (u == -1) break;
            visited[u] = 1;
                    {
                            for(int k=0;k<num;k++)
                            {
                                if(u==array[k].a-1){
                                    temp=array[k].weight+dist[array[k].a-1];//到这条边的前加上这条边
                                    if((temp)<dist[array[k].b-1])//到这条边的前加上这条边小于到这条边的后
                                    dist[array[k].b-1]=temp;//更新
                                    prev[array[k].b-1]=array[k].a;//到这条边的前节点更新
                                }
                            }
            }
        
    }
    // 打印最终结果
     printf("===============================\n");
    for(int i=0;i<point_num;i++){
        printf("[%d],dist=%d,visited=%d,prev=%d\n",i+1,dist[i],visited[i],prev[i]);
    }
    free(dist);
    free(visited);
    free(prev);
}




int main() {
    srand((unsigned int)time(NULL));
    while(1){
    
    printf("=== 图算法测试 ===\n");
    
    printf("请输入顶点个数: ");
    int point_num;
    scanf("%d", &point_num);
    if(point_num <= 0){
        printf("输入错误，顶点数应 > 0。\n");
        system("pause");
        return -1;
    }
    
    printf("请输入边的数目: ");
    int num;
    scanf("%d", &num);
    if(num <= 0){
        printf("输入错误，边数应 > 0。\n");
        system("pause");
        return -1;
    }
    
    edge* userArray = scanf_num(num, point_num);
    if(userArray == NULL){
        system("pause");
        return -1;
    }
    
    printf("您输入的边数组是: ");
    printArray(userArray, num);

    f1(userArray, num, point_num);
    f2(userArray, num, point_num);
    f3(userArray, num, point_num,1);


    
    free(userArray);
    
    printf("\n程序执行完毕。\n");
}
    return 0;
}

