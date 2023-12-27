/*#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int c[100][100];
int arrow[100][100];
// dia=1; up=2; left =3

int max(int a, int b){
    return a>b?a:b;
}

void printLCS(int arr[][100], char n[], int i, int j){
    if(i == 0 || j==0){
        return;
    }
    if(arr[i][j] == 1){
        printLCS(arr, n, i-1,j-1);
        printf("%c ", n[i-1]);
    }
    else if(arr[i][j] == 2){
        printLCS(arr, n, i-1, j);
    }
    else {
         printLCS(arr, n, i, j-1);
    }
}

int main(void){
    int i, j;
    int m,n;
    char x[]="ABCBDAB";
    char y[]="BDCABA";
    m = strlen(x);
    n = strlen(y);
    for(i=1; i<=m; i++){
        c[i][0]=0;
    }

    for(j=0; j<=n; j++){
        c[0][j]=0;
    }

    for(i=1; i<=m; i++){
        for(j=1; j<=n; j++){
            if(x[i-1]==y[j-1]){
                c[i][j] = c[i-1][j-1]+1;
                arrow[i][j] = 1;
            }
            if(x[i-1] != y[j-1]){
                c[i][j] = max(c[i][j-1], c[i-1][j]);
                if(c[i][j]==c[i-1][j]){
                    arrow[i][j] = 2;
                }
                else{
                    arrow[i][j] = 3;
                }
            }
        }
    }

    printf("%d\n", c[m][n]);

    for(i=1; i<=m; i++){
        for(j=1; j<=n; j++){
            printf("%d ",c[i][j]);
        }
        printf("\n");
    }
    printf("Arrows:\n");
    for(i=1; i<=m; i++){
        for(j=1; j<=n; j++){
            printf("%d ", arrow[i][j]);
        }
        printf("\n");
    }

    printLCS(arrow, x, m,n);

    return 0;
}*/

///LCS with memorization
#include<stdio.h>
#include<string.h>
#include<limits.h>


int c[100][100];
int arrow[100][100];
// dia=1; up=2; left =3

int max(int a, int b){
    return a>b?a:b;
}

void printLCS(int arr[][100], char n[], int i, int j){
    if(i == 0 || j==0){
        return;
    }
    if(arr[i][j] == 1){
        printLCS(arr, n, i-1,j-1);
        printf("%c ", n[i-1]);
    }
    else if(arr[i][j] == 2){
        printLCS(arr, n, i-1, j);
    }
    else {
         printLCS(arr, n, i, j-1);
    }
}

int lcs(char x[], char y[], int m, int n){

    if(c[m][n]>0) return c[m][n];

    if(m==0 || n==0){
        return c[m][n] = 0;
    }

    if(x[m-1] == y[n-1]){
        arrow[m][n] = 1;
        return c[m][n] = 1 + lcs(x, y, m-1, n-1);
    }
    else{
        c[m][n] = max(lcs(x, y, m, n-1), lcs(x,y,m-1,n));
        if(c[m][n] == lcs(x,y,m,n-1)){
            arrow[m][n] = 3;
        }
        else{
            arrow[m][n] = 2;
        }
        return c[m][n];
    }

    //printLCS(arrow, x, m,n);

}

int main(void){
    int i, j;
    int m,n;
    //char x[]="ABCBDAB";
    //char y[]="BDCABA";
    char x[] = "ageogoyde";
    char y[] = "gtohovd";
    m = strlen(x);
    n = strlen(y);
    for(i=0; i<=m; i++){
        for(j=0; j<=n; j++){
            c[i][j] = INT_MIN;
        }
    }
    int length = lcs(x, y, m, n);
    printf("Length:%d\n",length);
    printf("SubString: ");
    printLCS(arrow, x, m,n);
    return 0;
}