#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+10;

int parent[N];
int size[N];

int makeSet(int v){
    parent[v] = v;
    size[v] = 1;
}

int findSet(int v){
    if(v == parent[v]) return v;
    return parent[v] = findSet(parent[v]);
}

void unionSet(int a, int b){
    a = findSet(a);
    b = findSet(b);
    if(a != b) {
        if(size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
}

int main (void){
    int n, k;
    cin >> n >> k;
    for(int i=1; i<=n; i++){
        makeSet(i);
    }
    int a, b;
    for(int i=0; i<k; i++){
        cin >> a >> b;
        unionSet(a, b);
    }
    int connected_ct = 0;
    for(int i=1; i<=n; i++){
        if(findSet(i) == i) connected_ct++;
    }

    cout << connected_ct;

    return 0;
}