#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <time.h>
#include <sysinfoapi.h>
#define testtime1  	    long long int begin2 = GetTickCount64();		for(int i=0;i<test_iterations;i++)
#define testtime2       long long int end2 = GetTickCount64();	    double elapsed2 = (end2 - begin2)*1e-3;		printf("Time measured: %.7f seconds.\n", elapsed2/1000);
#define testcount1      clock_t start_testcount = clock(); for(int i = 0; i < test_iterations; i++)
#define testcount2      clock_t end_testcount = clock();    double total_time = ((double)(end_testcount - start_testcount)) / CLOCKS_PER_SEC;    printf("总操作数: %d\n",test_iterations);    printf("总时间: %f 秒\n", total_time);    printf("操作速度: %.0f 次操作/秒\n", test_iterations / total_time);    
const int test_iterations = 10000;

// 点结构体
typedef struct {
    double x;
    double y;
} Point;

/// @brief 计算两点间距离
/// @param p1 
/// @param p2 
/// @return 
double distance(Point p1, Point p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

/// @brief 比较函数，用于按x坐标排序
/// @param a 
/// @param b 
/// @return 
int compareX(const void* a, const void* b) {
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    return (p1->x > p2->x) - (p1->x < p2->x);
}

/// @brief 比较函数，用于按y坐标排序
/// @param a 
/// @param b 
/// @return 
int compareY(const void* a, const void* b) {
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    return (p1->y > p2->y) - (p1->y < p2->y);
}

/// @brief 暴力法求解最近点对（用于小规模数据）
/// @param points 
/// @param n 
/// @param min1 
/// @param min2 
/// @param minDist 
void bruteForce(Point points[], int n, Point* min1, Point* min2, double* minDist) {
    *minDist = DBL_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = distance(points[i], points[j]);
            if (dist < *minDist) {
                *minDist = dist;
                *min1 = points[i];
                *min2 = points[j];
            }
        }
    }
}

/// @brief 在带状区域中寻找最近点对，某种意义上的暴力破解，不过应该比完全暴力快
/// @param strip 
/// @param size 因为有点不在带状区域，所以需要这个，size一般小于strip的长度
/// @param d 
/// @param min1 
/// @param min2 
/// @return 
double stripClosest(Point strip[], int size, double d, Point* min1, Point* min2) {
    double min = d;
    
    // 按y坐标排序
    qsort(strip, size, sizeof(Point), compareY);
    
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; j++) {
            double dist = distance(strip[i], strip[j]);
            if (dist < min) {
                min = dist;
                *min1 = strip[i];
                *min2 = strip[j];
            }
        }
    }
    return min;
}

/// @brief 分治法递归函数
/// @param points 点组
/// @param n 数量
/// @param min1 
/// @param min2 
/// @return 
double closestUtil(Point points[], int n, Point* min1, Point* min2) {
    // 如果点数很少，使用暴力法，同时也是递归基础
    if (n <= 3) {
        double min;
        bruteForce(points, n, min1, min2, &min);
        return min;
    }
    
    int mid = n / 2;
    Point midPoint = points[mid];
    
    // 递归求解左右子集
    Point leftMin1, leftMin2, rightMin1, rightMin2;
    double dl = closestUtil(points, mid, &leftMin1, &leftMin2);
    double dr = closestUtil(points + mid, n - mid, &rightMin1, &rightMin2);
    
    // 取左右子集的最小距离
    double d;
    Point *currentMin1, *currentMin2;
    if (dl < dr) {
        d = dl;
        currentMin1 = &leftMin1;
        currentMin2 = &leftMin2;
    } else {
        d = dr;
        currentMin1 = &rightMin1;
        currentMin2 = &rightMin2;
    }
    
    // 构建带状区域,由勾股定理的最近点对要么是之前找出来的，要么在中线两侧d距离内
    Point* strip = (Point*)malloc(n * sizeof(Point));
    int stripSize = 0;
    for (int i = 0; i < n; i++) {
        //fabs是取绝对值函数,double
        if (fabs(points[i].x - midPoint.x) < d) {
            strip[stripSize] = points[i];
            stripSize++;
        }
    }
    
    // 在带状区域中寻找更小的距离
    Point stripMin1, stripMin2;
    double stripMin = stripClosest(strip, stripSize, d, &stripMin1, &stripMin2);
    
    double finalMin;
    //不是小于就是等于，没有大于：：断言www
    if (stripMin < d) {
        finalMin = stripMin;
        *min1 = stripMin1;
        *min2 = stripMin2;
    } else {
        finalMin = d;
        *min1 = *currentMin1;
        *min2 = *currentMin2;
    }
    
    free(strip);
    return finalMin;
}

/// @brief 主函数：寻找最近点对
/// @param points 
/// @param n 
/// @param min1 
/// @param min2 
/// @param minDist 
void findClosestPair(Point points[], int n, Point* min1, Point* min2, double* minDist) {
    if (n < 2) {
        printf("至少需要2个点\n");
        return;
    }
    
    // 按x坐标排序
    qsort(points, n, sizeof(Point), compareX);
    
    *minDist = closestUtil(points, n, min1, min2);
}

// 生成随机测试点
void generateRandomPoints(Point points[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        points[i].x = (double)rand() / RAND_MAX * 100.0;
        points[i].y = (double)rand() / RAND_MAX * 100.0;
    }
}
// 打印点集
void printPoints(Point points[], int n) {
    printf("点集:\n");
    for (int i = 0; i < n; i++) {
        printf("点%d: (%.2f, %.2f)\n", i + 1, points[i].x, points[i].y);
    }
    printf("\n");
}

int main() {
    int n;
    while (1){
    
    printf("请输入点的数量: ");
    scanf("%d", &n);
    // n=4;
    
    if (n <= 0) {
        printf("点的数量必须为正数\n");
        return 1;
    }
    
    Point* points = (Point*)malloc(n * sizeof(Point));
    
    int choice;
    printf("选择输入方式:\n");
    printf("1. 手动输入\n");
    printf("2. 随机生成\n");
    printf("请选择(1/2): ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("请输入%d个点的坐标(x y):\n", n);
        for (int i = 0; i < n; i++) {
            printf("点%d: ", i + 1);
            scanf("%lf %lf", &points[i].x, &points[i].y);
        }
    } else {
        generateRandomPoints(points, n);
    }
    
    // 打印输入的点集
    printPoints(points, n);
    
    // 计算最近点对
    Point min1, min2;
    double minDist;// 最短距离
    
    findClosestPair(points, n, &min1, &min2, &minDist);
    
    // 输出结果
    printf("最近点对:\n");
    printf("点1: (%.2f, %.2f)\n", min1.x, min1.y);
    printf("点2: (%.2f, %.2f)\n", min2.x, min2.y);
    printf("最短距离: %.6f\n", minDist);
    
    testtime1{
        findClosestPair(points, n, &min1, &min2, &minDist);
    }testtime2
    testcount1{
        findClosestPair(points, n, &min1, &min2, &minDist);
    }testcount2    
    
    // 验证：使用暴力法验证结果
    if (n <= 1000) { // 对于大数据集，暴力法太慢
        Point bruteMin1, bruteMin2;
        double bruteMinDist;
        
        
        bruteForce(points, n, &bruteMin1, &bruteMin2, &bruteMinDist);
        
        printf("\n暴力法验证:\n");
        printf("点1: (%.2f, %.2f)\n", bruteMin1.x, bruteMin1.y);
        printf("点2: (%.2f, %.2f)\n", bruteMin2.x, bruteMin2.y);
        printf("最短距离: %.6f\n", bruteMinDist);
        
        testtime1{
            bruteForce(points, n, &bruteMin1, &bruteMin2, &bruteMinDist);
        }testtime2
        testcount1{
            bruteForce(points, n, &bruteMin1, &bruteMin2, &bruteMinDist);
        }testcount2        
        
        // 检查结果是否一致
        if (fabs(minDist - bruteMinDist) < 1e-9) {
            printf("✓ 分治法结果正确\n");
        } else {
            printf("✗ 分治法结果错误\n");
        }
    }
    
    free(points);
    system("pause");
}
    return 0;
}