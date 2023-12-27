#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 100
#define INFINITY 1000000

int w[SIZE][SIZE], d[SIZE], prev[SIZE];
int n = 0;
bool flag[SIZE];
char name[SIZE][SIZE];

void initialize_single_source(int s)
{
    for (int v = 0; v < n; v++)
    {
        d[v] = INFINITY;
        prev[v] = -1;
    }
    d[s] = 0;
}

void relax(int u, int v)
{
    if (d[v] > d[u] + w[u][v])
    {
        d[v] = d[u] + w[u][v];
        prev[v] = u;
    }
}

int extract_min()
{
    int m = INFINITY, index = -1;

    for (int i = 0; i < n; i++)
    {
        if (flag[i] && m > d[i])
        {
            m = d[i];
            index = i;
        }
    }
    return index;
}

void dijkstra(int s)
{
    initialize_single_source(s);

    for (int i = 0; i < n; i++)
    {
        flag[i] = true;
    }
    int queueSize = n;
    while (queueSize)
    {
        int u = extract_min();
        for (int v = 0; v < n; v++)
        {
            if (w[u][v] > 0)
            {
                relax(u, v);
            }
        }
        queueSize--;
    }
}

void readInput()
{
    int u, v, weight;
    char s[SIZE];
    while (scanf("%s", s) != EOF)
    {
        if (strcmp(s, "END") == 0)
            break;

        for (u = 0; u < n; u++)
        {
            if (strcmp(name[u], s) == 0)
                break;
        }
        if (u == n)
        {
            strcpy(name[n], s);
            n++;
        }

        scanf("%s", s);
        for (v = 0; v < n; v++)
        {
            if (strcmp(name[v], s) == 0)
                break;
        }
        if (v == n)
        {
            strcpy(name[n], s);
            n++;
        }

        scanf("%d", &weight);
        w[u][v] = weight;
    }
}

void printGraph()
{
    int u, v;
    for (u = 0; u < n; u++)
    {
        for (v = 0; v < n; v++)
        {
            printf("%d ", w[u][v]);
        }
        printf("\n");
    }
}

void printPath(int v){
    if(v == -1){
        return;
    }
    printPath(prev[v]);
    printf("%s ", name[v]);
}

int main()
{
    freopen("input.txt", "r", stdin);
    readInput();
    //printGraph();
    dijkstra(0);
    printf("Sortest path: ");
    printPath(2);
    return 0;
}
