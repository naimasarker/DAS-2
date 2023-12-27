#include <stdio.h>
#include <stdlib.h>

#define MAX 10005
#define V 6

int id[MAX];
int nodes, edges;

typedef struct {
    int u, v;
    long long weight;
} Edge;

Edge graph[MAX];

void MAKE_SET(int v) {
    id[v] = v;
}

int FIND_SET(int v) {
    if (v == id[v])
        return v;
    return id[v] = FIND_SET(id[v]);
}

void UNION(int u, int v) {
    int p = FIND_SET(u);
    int q = FIND_SET(v);
    id[p] = id[q];
}

int compare(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

long long MST_KRUSKAL() {
    long long minimumCost = 0;
    int i;
    
    for (i = 0; i < nodes; ++i)
        MAKE_SET(i);

    qsort(graph, edges, sizeof(Edge), compare);

    for (i = 0; i < edges; ++i) {
        int u = graph[i].u;
        int v = graph[i].v;
        if (FIND_SET(u) != FIND_SET(v)) {
            minimumCost += graph[i].weight;
            UNION(u, v);
        }
    }

    return minimumCost;
}

int main() {
    int i;
    
    printf("Enter Nodes and edges: ");
    scanf("%d %d", &nodes, &edges);
    
    for (i = 0; i < edges; ++i) {
        printf("Enter edge (u, v) and weight: ");
        scanf("%d %d %lld", &graph[i].u, &graph[i].v, &graph[i].weight);
    }
    long long minimumCost = MST_KRUSKAL();
    printf("Minimum cost is %lld\n", minimumCost);

    return 0;
}


/*#include <stdio.h>
#include <stdlib.h>

#define MAX 10005

int id[MAX];
int nodes, edges;

typedef struct {
    int u, v;
    long long weight;
} Edge;

Edge graph[MAX];
Edge spanningTree[MAX]; // Array to store the edges of the spanning tree

void MAKE_SET(int v) {
    id[v] = v;
}

int FIND_SET(int v) {
    if (v == id[v])
        return v;
    return id[v] = FIND_SET(id[v]);
}

void UNION(int u, int v) {
    int p = FIND_SET(u);
    int q = FIND_SET(v);
    id[p] = id[q];
}

int compare(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

void MST_KRUSKAL() {
    int numEdges = 0; // Counter for edges in the spanning tree
    int i;
    int visited[MAX] = {0}; // Array to keep track of visited vertices
    
    for (i = 0; i < nodes; ++i)
        MAKE_SET(i);

    qsort(graph, edges, sizeof(Edge), compare);

    for (i = 0; i < edges; ++i) {
        int u = graph[i].u;
        int v = graph[i].v;
        if (FIND_SET(u) != FIND_SET(v)) {
            spanningTree[numEdges++] = graph[i]; // Add edge to spanning tree
            UNION(u, v);
        }
    }

    printf("Minimum Spanning Tree: ");
    for (i = 0; i < numEdges; ++i) {
        int u = spanningTree[i].u;
        int v = spanningTree[i].v;
        
        if (!visited[u]) {
            printf("%d", u);
            visited[u] = 1;
        }
        printf("->%d", v);
        visited[v] = 1;
    }
    printf("\n");
}

int main() {
    int i;
    
    printf("Enter Nodes and edges: ");
    scanf("%d %d", &nodes, &edges);
    
    for (i = 0; i < edges; ++i) {
        printf("Enter edge (u, v) and weight: ");
        scanf("%d %d %lld", &graph[i].u, &graph[i].v, &graph[i].weight);
    }

    MST_KRUSKAL();

    return 0;
}
*/