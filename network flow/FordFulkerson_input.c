#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#define V 6  // Number of vertices, adjust as needed
#define INF INT_MAX

int graph[V][V];

bool bfs(int rGraph[V][V], int s, int t, int parent[]) {
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    int queue[V];
    int front = 0, rear = 0;
    queue[rear++] = s;
    visited[s] = true;
    parent[s] = -1;

    while (front < rear) {
        int u = queue[front++];
        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = true;
                if (v == t)
                    return true;
            }
        }
    }
    return false;
}

int fordFulkerson(int graph[V][V], int s, int t) {
    int rGraph[V][V];
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            rGraph[i][j] = graph[i][j];

    int parent[V];
    int max_flow = 0;

    while (bfs(rGraph, s, t, parent)) {
        int path_flow = INF;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = (rGraph[u][v] < path_flow) ? rGraph[u][v] : path_flow;
        }

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}


int main() {
    FILE *file;
    file = fopen("ford.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1; 
    }

    int num_vertex, num_edge, from, to, dis;
    fscanf(file, "%d %d", &num_vertex, &num_edge);

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0;
        }
    }

    for (int i = 0; i < num_edge; i++) {
        fscanf(file, "%d %d %d", &from, &to, &dis);
        graph[from][to] = dis;
    }

    for (int i = 0; i <V; i++) {
        for (int j = 0; j <V; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    int source = 0, sink = 5;
    int maxFlow = fordFulkerson(graph, source, sink);

    printf("The maximum possible flow is %d\n", maxFlow);

    fclose(file);

    return 0;
}
