#include<stdio.h>
#include<limits.h>
#include<stdbool.h>
#include<string.h>

#define V 4
int graph[20][20] ;

char name[20][20];
int d[V], pre[V], n=0;

void INITIALIZE_SINGLE_SOURCE(int s, int d[V], int pre[V]){
    for(int v=0; v<V; v++){
        d[v] = INT_MAX; 
        pre[v] = -1;
    }
    d[s] = 0;
}

int EXTRACT_MIN(int q[], int d[]){
    int u = -1; 
    for(int v=0; v<V; v++){
        if(q[v] && (u == -1 || d[v]<d[u])){
            u = v;
        }
    }
    //printf("%d ", u);
    return u;
}

void RELAX(int u, int v,int w ,int d[], int pre[]){
    if(d[v]>d[u]+w){
        d[v] = d[u]+w;
        pre[v] = u;
    }
    //printf("%d ", pre[v]);
}

void dijkstra(int s, int d[V], int pre[V]){
    int q[V];
    for(int v=0; v<V; v++){
        q[v] = 1;
    }
    INITIALIZE_SINGLE_SOURCE(s, d, pre);

    while(1){
        int u = EXTRACT_MIN(q, d);
        if(u == -1){
            break;
        } 
        q[u] = 0;
        for(int v=0; v<V; v++){
            if(graph[u][v] != 0){
                RELAX(u, v,graph[u][v] , d, pre);
            }
        }
    }
}

void readInput(){

    int u, v, weight;
    char s[20];
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
        graph[u][v] = weight;
    }
    for(int i=0; i<=3; i++){
        for(int j=0; j<=3; j++){
            printf("%d ",graph[i][j]);
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
    dijkstra(s,d,pre);
    /*for(int i=0; i<=3; i++){
         printf("%d ", pre[i]);
    }*/
   
    int dis1 = printPath(pre, 3, d);
    //printf("\n%d\n", dis1);
    printf("\n");
    return 0;
}