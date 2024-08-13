#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_SIZE 100                      // Maximum number of elements
#define INPUT_FILE_NAME "input.txt"         // Input file containing input data to sort (+ the number of elements)

typedef struct AVLNode
    {
        int key;
        AVLNode *parent;
        AVLNode *lChild;
        AVLNode *rChild;
    }AVLNode, *AVL;

typedef struct{
    AVLNode nodes[MAX_TREE_SIZE];
    int r; //position of the root
    int n; 
}AVL;

//Read input data from a file and write the data into buffer
int readInput(int *buffer){
    FILE* fd;
    int dataTotal;
    int i;

    if((fd = fopen(INPUT_FILE_NAME, "r")) == NULL){
        printf("Error: Failure to open '%s'!\n", INPUT_FILE_NAME);
        exit(0);
        return -1; 
    }
    /* read input file to get task parameters */
	fscanf(fd, "%d \n", &dataTotal);
    if (dataTotal > MAX_TREE_SIZE) {
        printf("The number of elements exceeds the limit %d.\n", MAX_TREE_SIZE);
        return -1;
    }

	for (i = 0; i < dataTotal; i++) {
		fscanf(fd, "%d ", &buffer[i]);
    }
   
    return dataTotal;
}

// Node Insertion
AVLNode nodeInsertion(AVLNode *avl_node){

}

// Node Deletion


int main(){
     int inputTotal;                         // Number of elements to sort
    int inputData[MAX_TREE_SIZE];               // Elements to sort
    int i;

    // Read input data from a file
    if ((inputTotal = readInput(inputData)) < 1)
        printf("Error: Invalid input data in "INPUT_FILE_NAME".\n");

    // Node Insertion
    //bubbleSort(inputTotal, inputData);

    // Print the result
    

    printf("\n");
    
    return 0;
}

