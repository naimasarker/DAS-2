#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void computePrefixFunction(char* p, int m, int* Pi) {
    int k = 0;
    Pi[0] = 0;
    
    for (int q = 1; q < m; q++) {
        while (k > 0 && p[k] != p[q])
            k = Pi[k-1];
        if (p[k] == p[q])
            k++;
        Pi[q] = k;
    }
}

void KMPMatcher(char* S, char* p) {
    int n = strlen(S);
    int m = strlen(p);
    
    int* Pi = (int*)malloc(m * sizeof(int));
    computePrefixFunction(p, m, Pi);
    
    int q = 0;
    for (int i = 0; i < n; i++) {
        while (q > 0 && p[q] != S[i])
            q = Pi[q-1];
        if (p[q] == S[i])
            q++;
        if (q == m) {
            printf("Pattern occurs with shift %d\n", i - m + 1);
            q = Pi[q-1];
        }
    }
    free(Pi);
}

int main() {
    char S[] = "ababcababcabcabc";
    char p[] = "ababc";
    
    KMPMatcher(S, p);
    
    return 0;
}
