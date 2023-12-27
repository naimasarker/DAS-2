#include<stdio.h>
    int w[4] = {2,1,3,2};
    int v[4] = {12,10,20,15};
    int p[5][6];
    int arrow[5][6];
    //dia =1, up =3;
int max(int a, int b){
    return a>b?a:b;
}

void items(int i, int j){
    if(i ==0 || j==0){
        return;
    }
    if(arrow[i][j] != 3){
        items(i-1, j-w[i-1]);
        printf("%d ", i);  
    }
    else {
        items(i-1, j);
    }
}

int main(void){
    int W = 5;
    for(int i=0; i<=4; i++){
        for(int j=0; j<=5; j++){
            if(i==0 || j==0){
                p[i][j] = 0;
            }
            else if(w[i-1]>j){
                p[i][j] = p[i-1][j];
                arrow[i][j] = 3;
            }
            else{
                p[i][j] = max(v[i-1]+p[i-1][j-w[i-1]], p[i-1][j]);
                if(p[i][j] == p[i-1][j]){
                    arrow[i][j] = 3;
                }
                else{
                    arrow[i][j] = 1;
                }
            }
        }
    }
    for(int i=0; i<=4; i++){
        for(int j=0; j<=5; j++){
            printf("%d ",p[i][j]);
        }
        printf("\n");
    }
    for(int i=1; i<=4; i++){
        for(int j=1; j<=5; j++){
            printf("%d ",arrow[i][j]);
        }
        printf("\n");
    }
    printf("Selected items:");
    items(4,5);
    return 0;
}