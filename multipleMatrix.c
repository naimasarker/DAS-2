#include<stdio.h>
#include<limits.h>

int RMC(int p[], int i, int j, int m[][6], int s[][6]){
    if(m[i][j]<INT_MAX){
        return m[i][j];
    }
    int q;
    if(i == j){
        m[i][j] = 0;
    }
    
    else{
        for(int k=i; k<j; k++){
            q = RMC(p, i, k, m, s)+RMC(p,k+1,j,m,s)+p[i-1]*p[k]*p[j];
            if(q<m[i][j]){
                m[i][j] = q;
                s[i][j] = k;
            }
        }
    }
    
    return m[i][j];
}

void POP(int s[][6], int i, int j){
    if(i == j){
        printf("A%d", i);
    }
    else{
        printf("(");
        POP(s, i, s[i][j]);
        POP(s, s[i][j]+1, j);
        printf(")");
    }
}

int main(void){
    int n = 5;
    int p[6] = {10,5,1,10,2,10};
    int m[n+1][n+1];
    int s[n+1][n+1];
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            m[i][j] = INT_MAX;
        }  
    }
    int optimalcost = RMC(p, 1, n, m, s);
    printf("Optimal cost:%d\n", optimalcost);
    printf("Optimal Parenthesis: ");
    POP(s, 1, n);
}
