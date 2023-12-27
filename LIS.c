#include<stdio.h>
int maxLength =0;

void printLIS(int a[],  int prev[], int i){
    
    if(i == -1){
        return;
    }
    if(i != -1){
        maxLength++;
    }
    printLIS(a,prev,prev[i]);
    printf("%d ",a[i]);
}

void LISFDP(int a[], int n){
    int L[n], LP[n], prev[n];
    L[0] = -112998873;
    LP[0] = -1;
    prev[0] = -1;
    int length =1;
    for(int i=1; i<=n; i++){
        if(L[length-1] <a[i]){
            L[length] = a[i];
            LP[length] = i;
            prev[i] = LP[length-1];
            length++;
        }
        else{
            int s, h, m;
            s =0, h=length;
            while(s<h){
                m = (s+h)/2;
                if(L[m]<a[i]){
                    s = m+1;
                }
                else{
                    h = m;
                }
            }
            L[s] = a[i];
            LP[s] = i;
            prev[i] = LP[s-1];
        }
    }
    printf("Element of prev: ");
    for(int i=0; i<n; i++){
        printf("%d ",prev[i]);
    }
    printf("\n");
    printf("Sequence:");
    printLIS(a,prev,10);
}
int main(void){
    //int a[] = {0,2,5,3,6,1,2,10,7,9};
    int a[] = {0, 9, 2, 5,3,7,11,8,10,13, 6};
    int n = sizeof(a) / sizeof(a[0]);
    LISFDP(a, n);
    printf("\nMax length:%d\n",maxLength);
    return 0;
}