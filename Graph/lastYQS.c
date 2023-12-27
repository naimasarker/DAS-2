#include<stdio.h>
#include<stdbool.h>
#include<limits.h>
#include<string.h>

#define m 100

char name[m][40];
int graph[100][100]={0};
int totalCost =0;


int extractMin(int key[], int inMST[], int V){
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

void printMST(int parent[], int graph[100][100], int V){
    int mincost=0;
    printf("Edge    Weight\n");
    for(int i=1; i<V; i++){
        printf("%d-%d   %d\n", parent[i], i, graph[i][parent[i]]);
        mincost = mincost + graph[i][parent[i]];
    }
    printf("Maximum %d rupe can be saved\n", totalCost-mincost);
}

void primMST(int graph[100][100], int r, int V){
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
        int u = extractMin(key, inMST, V);
        inMST[u] = true;

        for(int v=0; v<V; v++){
            if(graph[u][v] && !inMST[v] && graph[u][v]<key[v]){
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph, V);
}

void readinput(FILE *file, int graph[100][100], int V){
    int u, v, weight;
    char s[20];
    int n =0;

    while (fscanf(file, "%s", s) != EOF) {
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

        fscanf(file, "%s", s);
        for (v = 0; v < n; v++) {
            if (strcmp(name[v], s) == 0)
                break;
        }
        if (v == n) {
            strcpy(name[n], s);
            n++;
        }

        fscanf(file, "%d", &weight);
        //printf("%d %d\n", u, v);
        graph[u][v] = weight;
        graph[v][u] = weight;
        totalCost += weight; 
    }
    /*for(int i=0; i<7; i++){
        printf("%s ", name[i]);
    }*/
     for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            printf("%d   ",graph[i][j]);
        }
        printf("\n");
    }
    
}



int main(void){
    FILE *file = fopen("last.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    int num_vertex, num_edge;
    fscanf(file, "%d %d", &num_vertex, &num_edge);
    int V = num_vertex;
    
    readinput(file, graph, V);
    fclose(file);
    int r = 0;
    primMST(graph, r, V);
    return 0;
}