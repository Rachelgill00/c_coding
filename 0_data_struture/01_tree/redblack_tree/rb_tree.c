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

// Print the Red Black Tree.
void printTree(RBTree *T, RBNode *node, int type, int level){

    int i;

    if(node == T -> nil){
        return;
    }

    printTree(T, node -> right, 2, level + 1);

    switch(type){
        case 0:
            printf("%3d (%s)\n", node->key, (node->color == RED) ? "R" : "B");
            break;
        case 1:
            for(i = 0; i < level; i++){
                printf("\t");
            }
            printf("\\ %3d (%s)\n", node->key, (node->color == RED) ? "R" : "B");
            break;
        case 2: 
            for(i = 0; i < level; i++){
                printf("\t");
            }
            printf("/ %3d (%s)\n", node->key, (node->color == RED) ? "R" : "B");
            break;
            
    }

    printTree(T, node -> left, 1, level + 1);
}

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

 void rbtree_left_rotate(RBTree *T, RBNode *x){
    RBNode *y = x -> right;
    x -> right = y -> left;

    if(y -> left != T -> nil){
        y -> left -> parent = x;
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

    return;
}

void rbtree_right_rotate(RBTree *T, RBNode *y){
    RBNode *x = y-> left;
    y -> left = x -> right;

    printf("y = %d\n", y -> key);
    printf("x = %d\n", x -> key);
    printf("y - parent = %d\n", y -> parent -> key);
    
    if(x -> right != T -> nil){
        x -> right -> parent = y;
    }
    
    x -> parent = y -> parent;
    
    if((y -> key) != 20){
        printf("y-parent-right: %d\n", y -> parent -> right -> key);
        printf("y-parent-left: %d\n", y -> parent -> left -> key);
    }

    if(y -> parent == T -> nil){
        T -> root = x;
    }else if(y == y -> parent -> left){
        y -> parent -> left = x;
    }else{
        y -> parent -> right = x;
    }

    x -> right = y;
	y -> parent = x;

    return;
}

/*
    Fixup case:
    1. When Uncle Node's color is 'Black'
        1)LL or RR
            a. Rotation
            b. Change the color of the parent node and uncle node 
        2)LR or RL
            a. 2*Rotation
            b. Change the color of new node and child node
                (Child node is the node that afer rotating)
    2.  When Uncle Node's color is 'Red'
        a. Change the color of the 'parent node' and 'uncle node' to BLACK
        b. Change the color of the grandparent node to RED
        c. Set the grandparent node to 'newnode', 
           and maybe need to call the fixup function recursively
*/
void exchange_color(RBNode *left, RBNode *right){
        int temp = left -> color;
        left -> color = right -> color;
        right -> color = (temp == BLACK) ? BLACK : RED ;
}

void rebtree_insert_fixup(RBTree *T, RBNode *node){
    // Init some pointers.
    RBNode *parent = node -> parent;
    RBNode *grand_parent = parent -> parent;
    if ((node != T -> root) &&(node != T -> root -> left) && (node != T -> root -> right)){
        printf("node:%d\n", node -> key);
        printf("parent:%d\n", parent -> key);
        printf("grandparent:%d\n", grand_parent -> key);
        printf("grandparent -> parent :%d\n", grand_parent -> parent -> key);
    }
    
    RBNode *uncle;

    //If the newnode is the root, it's color must be Black.
    if(node == T -> root){
        node -> color = BLACK;
        return;
    }
    if(parent -> color == BLACK){
        return;
    }

    // Measure the color of the uncle node
    if(grand_parent -> left == parent){
        uncle = grand_parent -> right;
    }else{
        uncle = grand_parent -> left;
    }
    
    if(uncle -> color == BLACK){
        // When uncle node is Black
        if((parent -> left == node) && ((grand_parent -> left) == parent)){
            //LL
            printf("LL!\n");
            // Print the Red Black Tree
            printf("Red Black Tree:\n");
            printTree(T, T -> root, 0, 0);

            rbtree_right_rotate(T, grand_parent);

            // Print the Red Black Tree
            printf("Red Black Tree:\n");
            printTree(T, T -> root, 0, 0);

            exchange_color(parent, parent -> right);

            return;
        }else if((parent -> right == node) && ((grand_parent -> right) == parent)){
            //RR
            printf("RR!\n");
            rbtree_left_rotate(T, grand_parent);
            
            exchange_color(parent, parent -> left);

            return;
        }else if((parent -> left = node) &&((grand_parent -> right) = parent)){
            //LR
            rbtree_left_rotate(T, grand_parent);
            rbtree_right_rotate(T, grand_parent);
            exchange_color(node, node -> right);

            return; 
        }else if((parent -> left = node) &&((grand_parent -> right) = parent)){
            //RL
            rbtree_right_rotate(T, grand_parent);
            rbtree_left_rotate(T, grand_parent);
            exchange_color(node, node -> left);

            return;
        }
    }else{
        //When uncle node is Red
        parent -> color = uncle -> color = BLACK;
        grand_parent -> color = RED;
        rebtree_insert_fixup(T, grand_parent);
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
        if(key < (current -> key)){
            if(current -> left == T -> nil){
                current -> left = newnode;

                break;
            }
            current = current -> left;

        }else{
            if(current -> right == T ->nil){
                current -> right = newnode;
                
                break;
            }
            current = current -> right;

        }
    }

    newnode -> parent = current;
    printf("newnode -> parent:%d\n", newnode -> parent -> key);

    // If the newnode is the root:
    if(current == T -> nil){
        T -> root = newnode;
    }

    // It needs to go to fixup after inserting.
    rebtree_insert_fixup(T, newnode);
}

void rbtree_delete_fixup(RBTree *T, RBNode *z){

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

    for(int i =0; i< inputTotal; i++){
        printf("-----------------------------node:%d\n", inputData[i]);
        rbtree_insert(T, inputData[i]);
        if(inputData[i] == 2){
            // Print the Red Black Tree
            printf("Red Black Tree:\n");
            printTree(T, T -> root, 0, 0);
        }
    }
    // Free the Red Black Tree
    delete_rbtree(T);

    return 0;
}

