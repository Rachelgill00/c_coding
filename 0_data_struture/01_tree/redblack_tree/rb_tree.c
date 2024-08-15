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

// Init a Red Black Tree.
RBTree *new_rbtree(void){
    // New a RBTree 
    RBTree *T = (RBTree *)malloc(sizeof(RBTree));
    if(T == NULL){
        printf("malloc failed!\n");
        exit(-1);
    }

    // New a  nil(Node)
    RBNode *nil = (RBNode *)malloc(sizeof(RBNode));
    nil -> color = BLACK;
    T -> nil = T -> root = nil;
    
    return T;
}

void traverse_and_delete_node(RBTree *T, RBNode *node){
    if(node -> left != T -> nil){
        traverse_and_delete_node(T, node);
    }
    if(node -> right != T -> nil){
        traverse_and_delete_node(T, node);
    }

    free(node);
}

// Remember to free it aftering you have malloced something
 void delete_rbtree(RBTree *T){
    RBNode *node = T -> root;
    if (node != T -> nil){
        traverse_and_delete_node(T, node);
    }

    // Free the struct momory of nil(TBNode) and rbtree(RBTree)
    free(T -> nil);
    free(T);
 }



void rebtree_insert_fixup(RBTree *T, RBNode *node){
    // Init some pointers.
    RBNode *parent = node -> parent;
    RBNode *grand_parent = parent -> parent;
    RBNode *uncle;
    // Define some variable to measure something.
    int is_left = (node == parent->left);
    int is_parent_is_left;

    //If the newnode is the root, it's color must be Black.
    if(node = T -> root){
        node -> color = BLACK;
        return;
    }
    


    return;
}

void rbtree_insert(RBTree *T, int key){
    // Init the new node.
    RBNode *newnode = (RBNode *)calloc(1, sizeof(RBNode));
    newnode -> key = key;
    newnode -> color = RED;
    newnode -> left = newnode -> right = T -> nil;

    //The possition of the newnode for insertion
    RBNode *current = T -> root;
    // If the newnode is not the root: 
    while (current != T -> nil){
        if(key < current -> key){
            if(current -> left = T -> nil){
                current -> left = newnode;
                break;
            }
            current = current -> left;
        }else{
            if(current -> right = T ->nil){
                current -> right = newnode;
                break;
            }
            current = current -> right;
        }
    }

    newnode -> parent = current;

    // If the newnode is the root:
    if(current = T -> nil){
        T -> root = newnode;
    }

    // It needs to go to fixup after inserting.
    rebtree_insert_fixup(T, newnode);
}

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

void rbtree_delete_fixup(RBTree *T, RBNode *z){

}

//void rbtree_node *rbtree_search

//void rbtree_traversal
void rbtree_inoder_traversal(){

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


// Node Deletion



int main(){
    int inputTotal;                         // Number of tree size
    int inputData[MAX_TREE_SIZE];           // Trees' value

    // Read input data from a file
    inputTotal = readInput(inputData);

    // Print the result
    printFile(inputTotal, inputData);
    printf("\n");

    //Init a Red Black Tree
    RBTree *T = new_rbtree();    //Insert the nodes to the Red Black Tree

    //The pointer for Searching


    //free
    return 0;
}

