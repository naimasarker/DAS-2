#include<stdio.h>
#include<stdbool.h>
#include<limits.h>

#define V 5

int extractMin(int key[V], int inMST[V]){
    int min = INT_MAX;
    int minIndex;

    for(int v=0; v<V; v++){
        if(!inMST[v] && min>key[v]){
            min = key[v];
            minIndex = v;
        }
    }

    return minIndex;
}

void printMST(int parent[V], int graph[V][V]){
    int mincost=0;
    printf("Edge    Weight\n");
    for(int i=1; i<V; i++){
        printf("%d-%d   %d\n", parent[i], i, graph[i][parent[i]]);
        mincost = mincost + graph[i][parent[i]];
    }
    printf("Minimum Cost: %d\n", mincost);
}

void primMST(int graph[V][V], int r){
    int parent[V];
    int key[V];
    int inMST[V];

    for(int i=0; i<V; i++){
        key[i] = INT_MAX;
        inMST[i] = false;
    }
    
    key[r] = 0;
    parent[r] = -1;

    for(int i=0; i<V-1; i++){
        int u = extractMin(key, inMST);
        inMST[u] = true;

        for(int v=0; v<V; v++){
            if(graph[u][v] && !inMST[v] && graph[u][v]<key[v]){
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph);
}

int main(void){
    int graph[V][V] = {
        {0, 9, 75, 0, 0},
        {9, 0, 95, 19, 42},
        {75, 95, 0, 51, 66},
        {0, 19, 51, 0, 31},
        {0, 42, 66, 31, 0}
    };
    int r = 0;
    primMST(graph, r);
    return 0;
}