#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TREE_SIZE 100                   // Maximum number of elements
#define INPUT_FILE_NAME "input.txt"         // Input file containing input data to sort (+ the number of elements)

// Structure of BTNode.
typedef struct btnode{
    char data;
    struct btnode *left, *right;
}BTNode;

// New a BNTree Node.
BTNode *newNode(int value){
    BTNode *newNode = (BTNode *)malloc(sizeof(BTNode));
    newNode -> data = value;
    newNode -> left = NULL;
    newNode -> right = NULL;

    return newNode;
}

void printTree(BTNode *node, int type, int level){
    int i;

    if(node == NULL){
        return;
    }

    printTree(node -> right, 2, level + 1);

    switch(type){
        case 0:
            printf("%3d\n", node -> data);
            break;
        case 1:
            for(i = 0; i < level; i++){
                printf("\t");
            }
            printf("\\ %3d\n", node -> data);
            break;
        case 2: 
            for(i = 0; i < level; i++){
                printf("\t");
            }
            printf("/ %3d\n", node -> data);
            break;
            
    }

    printTree(node -> left, 1, level + 1);
}

// Insertion
void insert(BTNode **root, int value){
    if(*root == NULL){
        *root = newNode(value);
        return;
    }
    if(value < ((*root) -> data)){
        if((*root) -> left == NULL){
            (*root) -> left = newNode(value);
        }else{
            insert(&((*root) -> left), value);
        }
    }else{
        if((*root) -> right == NULL){
            (*root) -> right = newNode(value);
        }else{
            insert(&((*root) -> right), value);
        }
    }
}

//Inorder the Binary Tree
void inorderTraversal(BTNode *root){
    if(root != NULL){
        inorderTraversal(root -> left);
        printf("%d  ", root -> data);
        inorderTraversal(root -> right);
    }
}


void preoderTraversal(BTNode *root){
    if(root != NULL){
        printf("%d  ", root -> data);
        printf("\n");
        preoderTraversal(root -> left);
        preoderTraversal(root -> right);
    }
}


int isEmpty(BTNode* root) 
{
    if (root == NULL) 
    {
        return 1; 
    } 
    else
    {
        return 0; 
    }
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
        printf("%d  ", inputData[i]);
    }
}

int main(){
    int inputTotal;                         // Number of tree size
    int inputData[MAX_TREE_SIZE];           // Trees' value
    int i;

    // Read input data from a file
    inputTotal = readInput(inputData);

    // Print the result
    printFile(inputTotal, inputData);
    printf("\n");

    BTNode *root = NULL;
    for(int i = 0; i < inputTotal; i++){
        insert(&root, inputData[i]);
    }

    //printf("Inorder traversal of the BTree:\n");
    //preoderTraversal(root);
    printTree(root, 0, 0);
    printf("\n");

    printf("Is the tree empty? %s\n", isEmpty(root) ? "Yes" : "No");

    return 0;
}

