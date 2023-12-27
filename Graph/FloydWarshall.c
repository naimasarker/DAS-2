#include<stdio.h>
#include<string.h>

#define m 100
#define inf 1000000
#define V 5


int w[m][m], d[m][m], p[m][m], graph[m][m];
int  n=0, wei[m];
char name[m][40];

void initialize(){
    for(int i=1; i<=5; i++){
        for(int j=1; j<=5; j++){
            d[i][j] = w[i][j];
            if(i==j || w[i][j]==inf){
                p[i][j] = 0;
            }
            else if(i!=j && w[i][j]<inf){
                p[i][j] = i;
            }
        }
    }
    
}

void floydWarshall(){
    initialize();
    for(int k=1; k<=5; k++){
        for(int i=1; i<=5; i++){
            for(int j=1; j<=5; j++){
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

void printPath(int s, int t){
    if(p[s][t] == 0){
        printf("No path exist.\n");
        return;
    }
    else if(p[s][t] == s){
        printf("%s ->", name[s-1]);
    }
    else{
        printPath(s, p[s][t]);
        printPath(p[s][t], t);
    }
}

int placeindex(char s[]){
    for(int i=0; i<5; i++){
        if(strcmp(name[i], s) == 0){
            return i+1;
        }
        
    }
    return -1;
}

void readinput(FILE *file){
    int u, v, weight;
    char s[20];

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
        graph[u][v] = weight;
    }
    for(int i=1; i<=5; i++){
        for(int j=1; j<=5; j++){
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
    for(int i=0; i<=5; i++){
        for(int j=0; j<=5; j++){
            printf("%d   ",w[i][j]);
        }
        printf("\n");
    }
}


int main(void){

    FILE *file = fopen("APSPinput.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    readinput(file);
    fclose(file);
    
    floydWarshall();
    char source[20], des[20];
    printf("Enter your source and destination:");
    scanf("%s %s",source,des);
    int u = placeindex(source);
    int v = placeindex(des);
    printPath(u, v);
    printf("%s\n",des);
    printf("Weight:%d\n",d[u][v]);
    
    return 0;
}
