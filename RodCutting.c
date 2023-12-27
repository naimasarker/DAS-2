//*************************Rod cutting**********************
//length is larger and show all the cutting length
#include <stdio.h>
#include <limits.h>

int r[100];
int cutLengths[100];

int max(int a, int b) {
    return a > b ? a : b;
}

int rodCutting(int prices[], int len, int r[], int cutLengths[], int rodLength) {
    if (r[rodLength] >= 0) return r[rodLength];
    
    int maxRevenue;
    if (rodLength <= 0) maxRevenue = 0;
    else maxRevenue = INT_MIN;

    for (int len_to_cut = 1; len_to_cut <= rodLength; len_to_cut++) {
        if (rodLength - len_to_cut >= 0) {
            int currentPrice = (len_to_cut <= len) ? prices[len_to_cut - 1] : 0;
            int revenue = currentPrice + rodCutting(prices, len, r, cutLengths, rodLength - len_to_cut);
            if (revenue > maxRevenue) {
                maxRevenue = revenue;
                cutLengths[rodLength] = len_to_cut;
            }
        }
    }

    r[rodLength] = maxRevenue;
    return r[rodLength];
}

void printCuttingSolution(int cutLengths[], int rodLength) {
    while (rodLength > 0) {
        printf("%d ", cutLengths[rodLength]);
        rodLength -= cutLengths[rodLength];
    }
    printf("\n");
}

int main(void) {
    int prices[] = {1, 5, 8, 9, 10, 12, 17};
    int size = sizeof(prices) / sizeof(prices[0]);
    int rodLength = 50;

    for (int i = 0; i < 100; i++) {
        r[i] = INT_MIN;
        cutLengths[i] = 0;
    }

    int maxRevenue = rodCutting(prices, size, r, cutLengths, rodLength);
    printf("Maximum revenue: %d\n", maxRevenue);

    printf("Cutting lengths: ");
    printCuttingSolution(cutLengths, rodLength);

    return 0;
}