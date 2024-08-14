#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_SIZE 100                   // Maximum number of elements
#define INPUT_FILE_NAME "input.txt"         // Input file containing input data to sort (+ the number of elements)

#define BLACK 1
#define RED 2

typedef struct rbnode{
    int key;
    int color;
    struct rbnode *parent;
    struct rbnode *left;
    struct rbnode *right;
}RBNode;

typedef struct rbtree{
    RBNode *root;
    RBNode *nil; 
}RBTree;

void rbtree_left_rotate(RBTree *T, RBNode *x){
    RBNode *y = x -> right;

    x -> right = y -> left;
    if(y -> left != T -> nil){
        y -> left = x;
    }

    y -> parent = x -> parent;
    if(x -> parent == T -> nil){
        T -> root = y;
    }else if(x == x -> parent -> left){
        x -> parent -> left = y;
    }else{
        x -> parent -> right = y;
    }

    y -> left = x;
    x -> parent = y;
}

void rbtree_right_rotate(RBTree *T, RBNode *y){
    RBNode *x = y-> right;

    y -> left = x -> right;
    
    if(x -> right != T -> nil){
        x -> right = y;
    }

    if(y -> parent != T -> nil){
        T -> root = x;
    }else if(y == y -> parent -> left){
        y -> parent -> left = x;
    }else{
        y -> parent -> right = x;
    }

    x -> right = y;
	y -> parent = x;
}

void rbtree_insert(RBTree *T, RBNode *z){
    RBNode *y = T -> nil;

    z -> parent = y;

    if( y == T -> nil){
        T -> root = z;
    }
    
}

void rebtree_insert_fixup(RBTree *T, RBNode *z){
    
}

/*
void rbtree_node *rbtree_delete(RBTree *T, RBNode *z){

}

*/

void rbtree_delete_fixup(RBTree *T, RBNode *z){

}

//void rbtree_node *rbtree_search

//void rbtree_traversal



void rbtree_traversal(){

}

//Read input data from a file and write the data into buffer
int readInput(int *buffer){
    FILE* fd;
    int i;

    if((fd = fopen(INPUT_FILE_NAME, "r")) == NULL){
        printf("Error: Failure to open '%s'!\n", INPUT_FILE_NAME);
        exit(0);
        return -1; 
    }

    /* read input file to get task parameters */
    while(i < MAX_TREE_SIZE && fscanf(fd, "%d", &buffer[i]) != EOF) {
        i++;
    }

    if (i > MAX_TREE_SIZE){
        printf("Error: Invalid input data in "INPUT_FILE_NAME".\n");
    }
        
	fclose(fd);  

    return i;
}

void printFile(int inputTotal, int inputData[]){
    // Print the result
    for(int i = 0; i < inputTotal; i++){
        printf("%d ", inputData[i]);
    }
}

// Node Insertion
RBNode nodeInsertion(RBNode *rb_node){

}

// Node Deletion

// Creation



int main(){
    int inputTotal;                         // Number of tree size
    int inputData[MAX_TREE_SIZE];           // Trees' value

    // Read input data from a file
    inputTotal = readInput(inputData);

    // Print the result
    printFile(inputTotal, inputData);
    printf("\n");

    //Init a Rad Black Tree
    RBTree *T = (RBTree *)malloc(sizeof(RBTree));
    if(T == NULL){
        printf("malloc failed!\n");
        return -1;
    }
    T -> nil = (RBNode *)malloc(sizeof(RBNode));
    T -> nil -> color = BLACK;
    T -> root = T -> nil;

    //Insert the nodes to the Red Black Tree


    return 0;
}

