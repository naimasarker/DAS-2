#include<stdio.h>
#include<limits.h>
#include<stdbool.h>
#include<string.h>

#define V 5
int graph[20][20];
char name[20][20];
int d[V], pre[V], n=0;

void INITIALIZE_SINGLE_SOURCE(int s){
    for(int v=0; v<V; v++){
        d[v] = INT_MAX;
        pre[v] = -1;
    }
    d[s] = 0;
}

void RELAX(int u, int v, int w){
    if(d[v] > d[u] + w){
        d[v] = d[u] + w;
        pre[v] = u;
    }
}

bool BELLMAN_FORD() {
    INITIALIZE_SINGLE_SOURCE(0);

    for (int i = 1; i <= V - 1; i++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (graph[u][v] != 0) {
                    RELAX(u, v, graph[u][v]);
                }
            }
        }
    }

    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (graph[u][v] != 0 && d[v] > d[u] + graph[u][v]) {
                return false;
            }
        }
    }

    return true;
}

void readInput(){
    int u, v, weight;
    char s[20];
    while (scanf("%s", s) != EOF) {
        if (strcmp(s, "END") == 0)
            break;

        for (u = 0; u < n; u++) {
            if (strcmp(name[u], s) == 0)
                break;
        }
        if (u == n) {
            strcpy(name[n], s);
            n++;
        }

        scanf("%s", s);
        for (v = 0; v < n; v++) {
            if (strcmp(name[v], s) == 0)
                break;
        }
        if (v == n) {
            strcpy(name[n], s);
            n++;
        }

        scanf("%d", &weight);
        graph[u][v] = weight;
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

int printPath(int pre[], int v, int d[]){
    if(v == -1) return 0;
    printPath(pre, pre[v], d);
    printf("->%s ", name[v]);
    return d[v];
}

int main(void){
    int s = 0;

    freopen("input.txt", "r", stdin);
    readInput();
    
    //bool result = BELLMAN_FORD(n, d, s);
    bool result = BELLMAN_FORD();
    if (result) {
        printf("No negative-weight cycles found\n");
        int dis1 = printPath(pre, 3, d);
        printf("\n");
    } else {
        printf("Negative-weight cycle detected\n");
    }

    return 0;
}

// For a negative cycle graph
/*#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define V 3 // Number of vertices


int graph[V][V];

int d[V], pre[V];

void INITIALIZE_SINGLE_SOURCE(int s, int d[V], int pre[V]){
    for(int v=0; v<V; v++){
        d[v] = INT_MAX;
        pre[v] = -1;
    }
    d[s] = 0;
}

void RELAX(int u, int v, int w, int d[], int pre[]){
    if(d[v] > d[u] + w){
        d[v] = d[u] + w;
        pre[v] = u;
    }
}

bool BELLMAN_FORD() {
    INITIALIZE_SINGLE_SOURCE(0, d, pre);

    for (int i = 1; i <= V - 1; i++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (graph[u][v] != 0) {
                    RELAX(u, v, graph[u][v], d, pre);
                }
            }
        }
    }

    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (graph[u][v] != 0 && d[v] > d[u] + graph[u][v]) {
                return false;
            }
        }
    }

    return true;
}

int printPath(int pre[], int v, int d[]){
    if(v == -1) return 0;
    printPath(pre, pre[v], d);
    //printf("->%s ",  vertices[v]);
    return d[v];
}

int main(void){
    
    graph[0][1] = 2;
    graph[1][2] = 3;
    graph[2][0] = -8;


    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
    bool result = BELLMAN_FORD();

    if (result) {
        printf("No negative-weight cycles found\n");
        //int dis1 = printPath(pre, 3, d);
    } else {
        printf("Negative-weight cycle detected\n");
    }

    return 0;
}*/