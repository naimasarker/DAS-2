#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node {
    char data;
    unsigned frequency;
    int left;
    int right;
};
struct node* createNode(char data, unsigned frequency) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->frequency = frequency;
    newNode->left = -1;
    newNode->right = -1;
    return newNode;
}

void swapnode(struct node *a, struct node *b){
    struct node temp = *a;
    *a = *b;
    *b = temp;
}
void sortnode(struct node *nodes, int size){
    for(int i=0; i<size-1; ++i){
        for(int j=0; j<size-i-1; ++j){
            if(nodes[j].frequency>nodes[j+1].frequency){
                swapnode(&nodes[j], &nodes[j+1]);
            }
        }
    }
}
struct node *huffmantree(char data[], unsigned frequency[], int size){
    struct node *nodes = (struct node*)malloc(size *sizeof(struct node));
    for(int i=0; i<size; ++i){
        //nodes[i] = *createNode(data[i], frequency[i]);
        nodes[i].data = data[i];
        nodes[i].frequency = frequency[i];
        nodes[i].left = -1;
        nodes[i].right = -1;
    }
    sortnode(nodes, size);
    int nextindex = size;
    while(nextindex<2*size-1){
        int firstIndex = 0;
        int secondIndex = 1;
        if(nodes[firstIndex].frequency > nodes[secondIndex].frequency){
            swapnode(&nodes[firstIndex], &nodes[secondIndex]);
        }
        for(int i=2; i<nextindex; ++i){
            if(nodes[i].frequency < nodes[firstIndex].frequency){
                secondIndex = firstIndex;
                firstIndex=i;
            }
            else if(nodes[i].frequency < nodes[secondIndex].frequency){
                secondIndex = i;
            }
        }
        nodes[nextindex].data = '$';
        nodes[nextindex].frequency=nodes[firstIndex].frequency+nodes[secondIndex].frequency;
        nodes[nextindex].left = firstIndex;
        nodes[nextindex].right= secondIndex;
        nodes[firstIndex].frequency = -1;
        nodes[secondIndex].frequency = -1;
        ++nextindex;
    }
    return nodes;
}
void printa(struct node *root, int rootindex, char *code, int top){
    if(root[rootindex].left !=-1){
        code[top]='0';
        printa(root, root[rootindex].left, code, top+1);
    }
    if(root[rootindex].right != -1){
        code[top]='1';
        printa(root, root[rootindex].right, code, top+1);
    }
    if(root[rootindex].left == -1 && root[rootindex].right == -1){
        code[top]='\0';
        printf("%c:%s\n",root[rootindex].data, code);
    }
}
void huffmancode(char data[],  int frequency[], int size){
    struct node *root = huffmantree(data, frequency, size);
    char code[size];
    printa(root, 2*size-2, code, 0);
}
int main(void){
    char data[]={'a','b','c','d','e','f'};
    unsigned frequency[]={5,9,12,13,16,45};
    int size = sizeof(data)/sizeof(data[0]);
    printf("Huffman code:\n");
    huffmancode(data, frequency, size);
    return 0;
}