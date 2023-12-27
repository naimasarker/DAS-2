#include <stdio.h>
#include <string.h>

#define n 100
#define inf 100000

int w[n][n];
int d[n][n];
int p[n][n];
char graph[n][2][20];
int g_w[n]; // weight on each edge
char vertex[n][20];

int indexOf(char s[], int numVertex) {
    for (int i = 1; i <= numVertex; i++) {
        if (strcmp(vertex[i], s) == 0)
            return i;
    }
    return -1;
}

void initialize(int numVertex) {
    int infinity = inf;
    for (int i = 1; i <= numVertex; i++) {
        for (int j = 1; j <= numVertex; j++) {
            d[i][j] = w[i][j];
            if (i == j || w[i][j] == infinity) {
                p[i][j] = 0;
            } else if (i != j && w[i][j] < infinity) {
                p[i][j] = i;
            }
        }
    }
}

void fw(int numVertex) {
    initialize(numVertex);
    for (int k = 1; k <= numVertex; k++) {
        for (int i = 1; i <= numVertex; i++) {
            for (int j = 1; j <= numVertex; j++) {
                if (d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    p[i][j] = p[k][j];
                }
            }
        }
    }
}

void printMat(int numVertex) {
    printf("Matrix D:\n");
    for (int i = 1; i <= numVertex; i++) {
        for (int j = 1; j <= numVertex; j++) {
            printf("%d  ", d[i][j]);
        }
        printf("\n");
    }
    printf("Matrix P:\n");
    for (int i = 1; i <= numVertex; i++) {
        for (int j = 1; j <= numVertex; j++) {
            printf("%d  ", p[i][j]);
        }
        printf("\n");
    }
}

void printpath(int s, int t) {
    if (p[s][t] == 0) {
        printf("No path\n");
        return;
    } else if (p[s][t] == s) {
        printf("%s -> ", vertex[s]);
    } else {
        printpath(s, p[s][t]);
        printpath(p[s][t], t);
    }
}

void path(char s[], char t[], int num) {
    int u, v;
    u = indexOf(s, num);
    v = indexOf(t, num);

    printf("The shortest path from %s to %s is- ", s, t);
    printpath(u, v);
    printf("%s\nweight= %d\n", t, d[u][v]);
}

int main() {
    int numVertex, numEdge, u, v, index = 1;

    FILE *file = fopen("APSP_input_1.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    fscanf(file, "%d", &numEdge);
    for (int i = 1; i <= numEdge; i++) {
        fscanf(file, "%s %s %d", graph[i][0], graph[i][1], &g_w[i]);

        if (i == 1) {
            strcpy(vertex[index], graph[i][0]);
            index++;
            strcpy(vertex[index], graph[i][1]);
            index++;
        } else {
            int flag = 0;
            for (int j = 1; j < index; j++) {
                if (strcmp(graph[i][0], vertex[j]) == 0) {
                    flag = 1;
                    break;
                }
            }
            if (!flag) {
                strcpy(vertex[index], graph[i][0]);
                index++;
            }

            flag = 0;
            for (int j = 1; j < index; j++) {
                if (strcmp(graph[i][1], vertex[j]) == 0) {
                    flag = 1;
                    break;
                }
            }
            if (!flag) {
                strcpy(vertex[index], graph[i][1]);
                index++;
            }
        }
    }

    numVertex = index - 1;
    printf("Vertex number:%d\n",numVertex);

    for (int i = 1; i <= numVertex; i++) {
        for (int j = 1; j <= numVertex; j++) {
            if (i == j)
                w[i][j] = 0;
            else
                w[i][j] = inf;
        }
    }

    for (int i = 1; i <= numEdge; i++) {
        u = indexOf(graph[i][0], numVertex);
        v = indexOf(graph[i][1], numVertex);
        w[u][v] = g_w[i];
    }
    printf("Matrix w:\n");
    for(int i=0; i<=numVertex; i++){
        for(int j=0; j<=numVertex; j++){
            printf("%d ",w[i][j]);
        }
        printf("\n");
    }

    fw(numVertex);
    printMat(numVertex);
    char a[20], b[20];
    printf("Enter the edges: ");
    scanf("%s %s", a, b);
    path(a, b, numVertex);

    fclose(file);
    return 0;
}
