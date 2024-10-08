#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_SIZE 100                     // Maximum number of elements
#define INPUT_FILE_NAME "input.txt"         // Input file containing input data to sort (+ the number of elements)

typedef struct avlnode
    {
        int key;
        struct avlnode *parent;
        struct avlnode *lChild;
        struct avlnode *rChild;
    }AVLNode, *AVLTree;

typedef struct {
    AVLNode nodes[MAX_TREE_SIZE];
    int r; //position of the root
    int n; 
}AVL;

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
AVLNode nodeInsertion(AVLNode *avl_node){

}

// Node Deletion


int main(){
     int inputTotal;                         // Number of tree size
    int inputData[MAX_TREE_SIZE];            // Trees' value
    int i;

    // Read input data from a file
    inputTotal = readInput(inputData);

    // Print the result
    printFile(inputTotal, inputData);
    printf("\n");

    // Node Insertion
    
    return 0;
}

