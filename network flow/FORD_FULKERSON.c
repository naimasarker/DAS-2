/*#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#define V 6  // Number of vertices, adjust as needed
#define INF INT_MAX

// Function to perform Depth First Search (DFS) in the residual graph
bool dfs(int rGraph[V][V], int s, int t, int parent[]) {
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    // Create a stack for DFS
    int stack[V];
    int top = -1;
    stack[++top] = s;
    visited[s] = true;
    parent[s] = -1;

    while (top >= 0) {
        int u = stack[top--];
        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                stack[++top] = v;
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return visited[t];  // Return true if we reached the sink (t)
}


int fordFulkerson(int graph[V][V], int s, int t) {
    int rGraph[V][V]; // Residual graph
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
             rGraph[i][j] = graph[i][j];

    int parent[V];  // This array is filled by DFS and will store the augmenting path

    int max_flow = 0;  // There is no flow initially

    // Augment the flow while a path from source to sink exists
    while (dfs(rGraph, s, t, parent)) {
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

    for(int i=0; i<V; i++){
        printf("%d\n", parent[i]);
    }

    for(int i=0; i<V; i++){
        for(int j=0; j<V; j++){
            printf("%d ", rGraph[i][j]);
        }
        printf("\n");
    }

    return max_flow;
}

int main() {
    int graph[V][V] = { {0, 16, 13, 0, 0, 0},
                        {0, 0, 10, 12, 0, 0},
                        {0, 4, 0, 0, 14, 0},
                        {0, 0, 9, 0, 0, 20},
                        {0, 0, 0, 7, 0, 4},
                        {0, 0, 0, 0, 0, 0}
    };

    int source = 0, sink = 5;
    int maxFlow = fordFulkerson(graph, source, sink);

    printf("The maximum possible flow is %d\n", maxFlow);

    return 0;
}*/

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#define V 6  // Number of vertices, adjust as needed
#define INF INT_MAX

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

void fordFulkerson(int graph[V][V], int s, int t) {
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

        // Print augmenting path
        printf("Augmenting Path: ");
        for (int v = t; v != s; v = parent[v]) {
            printf("%d <- ", v);
            int u = parent[v];
        }
        printf("%d\n", s);
    }

    printf("The maximum possible flow is %d\n", max_flow);
}

int main() {
    int graph[V][V] = { {0, 16, 13, 0, 0, 0},
                        {0, 0, 10, 12, 0, 0},
                        {0, 4, 0, 0, 14, 0},
                        {0, 0, 9, 0, 0, 20},
                        {0, 0, 0, 7, 0, 4},
                        {0, 0, 0, 0, 0, 0}
    };

    int source = 0, sink = 5;
    fordFulkerson(graph, source, sink);

    return 0;
}
/*#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define V 100

int calculateCapacity (int numVertices, int graph[][V], int vertex) {
    int capacity = 0;
    for(int v=0; v<numVertices; v++) {
        if(graph[vertex][v]) {
            capacity += graph[vertex][v];
        }

        if(graph[v][vertex]) {
            capacity += graph[v][vertex];
        }
    }

    return capacity;
}

int bfs (int numVertices, int rGraph[][V], int s, int t, int parent[V]) {
    int visited[numVertices];
    for(int i=0; i<numVertices; i++) {
        visited[i] = 0;
    }

    visited[s] = 1;
    parent[s] = -1;

    int queue[numVertices];
    int front = 0;
    int rear = 0;
    queue[rear++] = s;

    while(front < rear) {
        int u = queue[front++];
        for(int v=0; v<numVertices; v++) {
            if(!visited[v] && rGraph[u][v] > 0) {
                visited[v] = 1;
                parent[v] = u;
                queue[rear++] = v;
            }
        }
    }

    return visited[t];
}

int fordFulkerson (int numVertices, int graph[][V], int s, int t) {
    int rGraph[numVertices][V];

    for(int i=0; i<numVertices; i++) {
        for(int j=0; j<numVertices; j++) {
            rGraph[i][j] = graph[i][j];
        }
    }

    

    int parent[numVertices];
    int maxFlow = 0;

    while(bfs(numVertices, rGraph, s, t, parent)) {
        int pathFlow = INT_MAX;
        for(int v=t; v!=s; v=parent[v]) {
            int u = parent[v];
            pathFlow = (rGraph[u][v] < pathFlow) ? rGraph[u][v]:pathFlow;
        }

        for(int v=t; v!=s; v=parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main (void) {

    int u,v,w;
    int numVertices, numEdges;
    int graph[V][V];

    FILE *fp = fopen("nfMultipleSrcSink.txt", "r");
    fscanf(fp, "%d %d", &numVertices, &numEdges);

    for(int i=0; i<V; i++) {
        for(int j=0; j<V; j++) {
            graph[i][j] = 0;
        }
    }

    for(int i=0; i<numVertices; i++) {
        for(int j=0; j<numVertices; j++) {
            fscanf(fp, "%d %d %d", &u, &v, &w);
            graph[u][v] = w;
        }
    }

    for(int i=0; i<numVertices; i++) {
        for(int j=0; j<numVertices; j++) {
            printf("%d ",graph[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    int source[3] = {0,1,2};
    int sink[2] = {5,6};

    int s = 7, t = 8;
    for(int i=0; i<3; i++) {
        graph[s][source[i]] = calculateCapacity(numVertices, graph, source[i]);
    }

    for(int i=0; i<2; i++) {
        graph[sink[i]][t] = calculateCapacity(numVertices, graph, sink[i]);
    }

    int n = numVertices + 2;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    int maxFlow = fordFulkerson(n, graph, s, t);
    printf("Maximum possible flow is: %d", maxFlow);

    return 0;
}
*/