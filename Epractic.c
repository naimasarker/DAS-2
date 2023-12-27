//RodCutting
/*#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
int r[100];
int cutLengths[100];

int rodCutting(int price[], int n, int r[], int cutLengths[], int rodLength){
    if(r[rodLength]>=0){
        return r[rodLength];
    }
    int maxRevenue;
    if(rodLength<=0){
        maxRevenue = 0;
    }
    else{
        maxRevenue = INT_MIN;
    }
    for(int lenCut = 1; lenCut<=rodLength; lenCut++){
        if(rodLength-lenCut>=0){
            int currentPrice = (lenCut<=n) ? price[lenCut-1]:0;
            int revenue = currentPrice + rodCutting(price, n, r, cutLengths, rodLength-lenCut);
            if(revenue>maxRevenue){
                maxRevenue = revenue;
                cutLengths[rodLength] = lenCut;
            }
        }
    }
    r[rodLength] = maxRevenue;
    return r[rodLength];
}

void printCutting(int cutLengths[], int rodLength){
    while (rodLength > 0) {
        printf("%d ", cutLengths[rodLength]);
        rodLength -= cutLengths[rodLength];
    }
    printf("\n");
}

int main(void){
    int price[] = {1, 5, 8, 9, 10, 12, 17};
    int size = sizeof(price)/sizeof(price[0]);
    int rodLength = 50;

    for(int i=0; i<100; i++){
        r[i] = INT_MIN;
        cutLengths[i] = 0;
    }

    int maxRevenue = rodCutting(price, size, r, cutLengths, rodLength);
    printf("Maximum revenue: %d\n", maxRevenue);
    printf("Cutting length: ");
    printCutting(cutLengths, rodLength);
    return 0;
}*/

//LCS

/*#include<stdio.h>
#include<string.h>
#include<limits.h>

int c[100][100];
int arrow[100][100];

int max(int a, int b){
    return a>b?a:b;
}

void printLCS(int arr[100][100], char n[], int i, int j){
    if(i==0 || j==0){
        return;
    }
    if(arr[i][j] == 1){
        printLCS(arr, n, i-1, j-1);
        printf("%c ", n[i-1]);
    }
    else if(arr[i][j] == 2){
        printLCS(arr, n, i-1, j);
    }
    else{
        printLCS(arr, n, i, j-1);
    }
}

int LCS(char x[], char y[], int m, int n){
    if(c[m][n]>INT_MIN) return c[m][n];

    if(m==0 || n == 0){
        return c[m][n] = 0;
    }

    if(x[m-1] == y[n-1]){
        arrow[m][n] = 1;
        return c[m][n] = 1 + LCS(x, y, m-1, n-1);
    }
    else{
        c[m][n] = max(LCS(x, y, m, n-1), LCS(x, y, m-1, n));
        if(c[m][n] == LCS(x, y, m, n-1)){
            arrow[m][n] = 3;
        }
        else{
            arrow[m][n] = 2;
        }
        return c[m][n];
    }
}

int main(void){
    int i, j;
    int m,n;
    char x[] = "ABCBDAB";
    char y[] = "BDCABA";
    m = strlen(x);
    n = strlen(y);
    for(int i=0; i<=m; i++){
        for(int j=0; j<=n; j++){
            c[i][j] = INT_MIN;
        }
    }
    int length = LCS(x, y, m, n);
    printf("Length:%d\n", length);
    printf("Substring:");
    printLCS(arrow, x, m, n);
    return 0;
}*/

/*#include<stdio.h>
#include<limits.h>
#include<stdbool.h>
#include<string.h>
#define max 100
int graph[max][max] = {0};
char name[max][40];
int d[max], pre[max];

void INITIALIZE_SINGLE_SOURCE(int s, int d[max], int pre[max], int V){
    for(int v=0; v<V; v++){
        d[v] = INT_MAX;
        pre[v] = -1;
    }
    d[s] = 0;
}

int EXTRACT_MIN(int q[], int d[], int V){
    int u = -1;
    for(int v=0; v<V; v++){
        if(q[v] &&(u == -1 || d[v]<d[u])){
            u = v;
        }
    }
    return u;
}

void RELAX(int u, int v, int w, int d[], int pre[], int V){
    if(d[v] > d[u]+w){
        d[v] = d[u]+w;
        pre[v] = u;
    }
}

void dijkstra(int s, int d[max], int pre[max], int V){
    int q[V];
    for(int v=0; v<V; v++){
        q[v] = 1;
    }
    INITIALIZE_SINGLE_SOURCE(s, d, pre, V);

    while(1){
        int u = EXTRACT_MIN(q, d, V);
        if(u == -1){
            break;
        }
        q[u] = 0;
        for(int v=0; v<V; v++){
            if(graph[u][v] !=0){
                RELAX(u, v, graph[u][v], d, pre, V);
            }
        }
    }
}

void readInput(FILE *file, int graph[max][max], int V){
    int u, v, weight;
    char s[20];
    int n=0;
    while(fscanf(file, "%s", s) != EOF){
        for(u=0; u<n; u++){
            if(strcmp(name[u], s) == 0){
                break;
            }
        }
        if(u == n){
            strcpy(name[n], s);
            n++;
        }
        fscanf(file, "%s", s);
        for(v = 0; v<n; v++){
            if(strcmp(name[v], s)== 0)
                break;
        }
        if(v == n){
            strcpy(name[n], s);
            n++;
        }
        fscanf(file, "%d", &weight);
        graph[u][v] = weight;

    }
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

void printPath(int pre[], int des, int d[] , int V){
    if(des == -1) return ;
    printPath(pre, pre[des], d, V);
    printf("->%s ", name[des]);

}

int main(void){
    FILE *file = fopen("diaIn.txt", "r");
    if(file == NULL){
        perror("Error opening file");
        return 1;
    }
    int num_vertex, num_edge;
    fscanf(file,"%d %d", &num_vertex, &num_edge);
    int V =  num_vertex;
    int s =0;
    readInput(file, graph, V);
    dijkstra(s, d, pre, V);
    fclose(file);
    printPath(pre, 3, d, V);
    return 0;
}*/

//FloydWarshall******************
/*#include<stdio.h>
#include<string.h>
#include<limits.h>

#define m 100
#define inf 1000000

int w[m][m], d[m][m], p[m][m], graph[m][m];
int n =0, wei[m];
char name[m][40];

void initialize(int V){
    for(int i=1; i<=V; i++){
        for(int j=1; j<=V; j++){
            d[i][j] = w[i][j];
            if(i==j || w[i][j] == inf){
                p[i][j] = 0;
            }
            else if(i!=j && w[i][j]<inf){
                p[i][j] = i;
            }
        }
    }
}

void floydWarshall(int V){
    initialize(V);
    for(int k=1; k<=V; k++){
        for(int i=1; i<=V; i++){
            for(int j=1; j<=V; j++){
                if(d[i][k]+d[k][j]<d[i][j]){
                    d[i][j] = d[i][k]+d[k][j];
                    p[i][j] = p[k][j];
                } 
            }
        }
    }
    printf("\nMatrix d:\n");
    for(int i=1; i<=5; i++){
        for(int j=1; j<=5; j++){
            
            printf("%d ",d[i][j]);
        }
        printf("\n");
    }
    printf("\nMatrix p:\n");
    for(int i=1; i<=5; i++){
        for(int j=1; j<=5; j++){        
            printf("%d ",p[i][j]);
        }
        printf("\n");
    }
}

void readInput(FILE *file, int V){
    int u, v, weight;
    char s[20];
    int n=0;
    while(fscanf(file, "%s", s) != EOF){
        for(u=0; u<n; u++){
            if(strcmp(name[u], s) == 0){
                break;
            }
        }
        if(u == n){
            strcpy(name[n], s);
            n++;
        }
        fscanf(file, "%s", s);
        for(v = 0; v<n; v++){
            if(strcmp(name[v], s)== 0)
                break;
        }
        if(v == n){
            strcpy(name[n], s);
            n++;
        }
        fscanf(file, "%d", &weight);
        graph[u][v] = weight;

    }
    for(int i=1; i<=V; i++){
        for(int j=1; j<=V; j++){
            if(i==j){
                w[i][j] = 0;
            }
            else if(graph[i-1][j-1] != 0){
                w[i][j] = graph[i-1][j-1];
            }
            else{
                w[i][j] = inf;
            }
        }
    }
    for(int i=0; i<=V; i++){
        for(int j=0; j<=V; j++){
            printf("%d   ",w[i][j]);
        }
        printf("\n");
    }
}

int placeindex(char s[40], int V){
    for(int i=0; i<V; i++){
        if(strcmp(name[i], s) == 0){
            return i+1;
        }
    }
    return -1;
}

void printPath(int s, int d){
    if(p[s][d] == 0){
        printf("No path exist.\n");
        return ;
    }
    else if(p[s][d] == s){
        printf("%s ->", name[s-1]);
    }
    else{
        printPath(s, p[s][d]);
        printPath(p[s][d], d);
    }
}

int main(void){
    FILE *file = fopen("ASps.txt", "r");
    if(file == NULL){
        perror("Error opening file.");
        return 1;
    }
    int num_vertex, num_edge;
    fscanf(file, "%d %d", &num_vertex, &num_edge);
    int V = num_vertex;
    readInput(file, V);
    fclose(file);
    floydWarshall(V);
    char sos[40], des[40];
    printf("Enter the source and destination:");
    scanf("%s %s", sos, des);
    int u = placeindex(sos, V);
    int v = placeindex(des, V);
    printPath(u, v);
    printf("%s\n", des);
    printf("\nWeight:%d\n", d[u][v]);
    return 0;
}*/
