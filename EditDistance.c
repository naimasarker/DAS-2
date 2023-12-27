#include<stdio.h>
#include<string.h>

int c[100][100], arrow[100][100];

// same= 0, diagonal=1; left=2; up = 3;

int min(int a,int b, int c){
    int d = a<b?a:b ;
    return d<c?d:c;
}

void print(int arrow[][100], char x[], char y[],int i, int j){
    if(i==0  || j==0){
       return ;
    }
    if(arrow[i][j]==0){
        print(arrow, x, y ,i-1, j-1);
    }
    else if(arrow[i][j] == 1){
        print(arrow, x, y,i-1, j-1);
        printf("Replace:%c -> %c\n", x[i-1], y[j-1]); 
    }
    else if(arrow[i][j]==3){
        print(arrow, x, y, i-1, j);
        printf("Delet:%c\n", x[i-1]);
    }
    else if(arrow[i][j] == 2){
        print(arrow, x, y,i, j-1);
        printf("Insert:%c\n", y[j-1]);
    }
}


int main(void){
    int i,j;
    char y[ ]="saturday";
    char x[ ]="sunday";

    int m,n;
    m = strlen(x);
    n = strlen(y);

    arrow[0][0]=5;
    c[0][0] = 0;
    for(i=1; i<=m; i++){
        c[i][0]=i;
        arrow[i][0] = 3;
    }

    for(j=1; j<=n; j++){
        c[0][j]=j;
        arrow[0][j] = 2;
    }
    for(i=1; i<=m; i++){
        for(j=1; j<=n; j++){
            if(x[i-1]==y[j-1]){
                c[i][j] = c[i-1][j-1];
                arrow[i][j] = 0;
            }
            else if(x[i-1]!= y[j-1]){
                c[i][j] = min(c[i-1][j-1], c[i-1][j], c[i][j-1])+1;
                if(c[i][j] == c[i-1][j-1]+1){
                    arrow[i][j]=1;
                }
                else if(c[i][j] == c[i-1][j]+1){
                    arrow[i][j]= 3;
                }
                else if(c[i][j]==c[i][j-1]+1){
                    arrow[i][j]= 2;
                }
            }
        }
    }

    for( i=0; i<=m; i++){
        for( j=0; j<=n; j++){
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    printf("Arrow:\n");
    for( i=0; i<=m; i++){
        for( j=0; j<=n; j++){
            printf("%d ", arrow[i][j]);
        }
        printf("\n");
    }
    print(arrow, x, y, m,n);

    return 0;
}