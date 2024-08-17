#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_SIZE 100                   // Maximum number of elements
#define INPUT_FILE_NAME "input2.txt"         // Input file containing input data to sort (+ the number of elements)

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

int readInput(int *buffer);
void printFile(int inputTotal, int inputData[]);
RBTree *new_rbtree(void);
void delete_rbtree(RBTree *T);
void traverse_and_delete_node(RBTree *T, RBNode *node);
void rbtree_insert(RBTree *T, int key);
void rebtree_insert_fixup(RBTree *T, RBNode *node);
void rbtree_left_rotate(RBTree *T, RBNode *node);
void rbtree_right_rotate(RBTree *T, RBNode *node);
void exchange_color(RBNode *left, RBNode *right);
RBNode *rbnode_find(RBTree *T, int key0);
void printTree(RBTree *T, RBNode *node, int type, int level);

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

 void rbtree_left_rotate(RBTree *T, RBNode *node){
    RBNode *parent = node -> parent;
    RBNode * grand_parent = parent -> parent;
    RBNode * node_left = node -> left;

    if (parent == T -> root){
        T -> root = node;
    }else{
        if(grand_parent -> left == parent){
            grand_parent -> left = node;
        }else{
            grand_parent -> right = node;
        }
    }
    node -> parent = grand_parent;

    parent -> parent = node;
    node -> left = parent;

    parent -> right = node_left;
    node_left -> parent = parent;
    
    return;
}

void rbtree_right_rotate(RBTree *T, RBNode *node){
    RBNode *parent = node -> parent;
    RBNode *grand_parent = parent -> parent;
    RBNode *node_right = node -> right;

    if(parent == T -> root){
        T -> root = node;
    }else{
        if(grand_parent -> left == parent){
            grand_parent -> left = node;
        }else{
            grand_parent -> right = node;
        }
    }
    node -> parent = grand_parent;
    parent -> parent = node;
    node -> right = parent;

    node_right -> parent = parent;
    parent -> left = node_right;
    
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

            rbtree_right_rotate(T, parent);

            exchange_color(parent, parent -> right);

            return;

        }else if((parent -> right == node) && ((grand_parent -> right) == parent)){
            //RR
            printf("RR!\n");
            

            rbtree_left_rotate(T, parent);

            exchange_color(parent, parent -> left);

            return;

        }else if((parent -> right == node) &&((grand_parent -> left) == parent)){
            //LR
            rbtree_left_rotate(T, node);
            rbtree_right_rotate(T, node);
            exchange_color(node, grand_parent);

            return; 

        }else if((parent -> left == node) &&((grand_parent -> right) == parent)){
            //RL
            rbtree_right_rotate(T, node);
            rbtree_left_rotate(T, node);
            exchange_color(node, grand_parent);

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

    //
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

RBNode *rbnode_find(RBTree *T, int key){
    RBNode *current = T -> root;
    while(current != T ->nil){
        if(key == current -> key){
            printf("Node %d is found!\n", key);

            return current;
        }else{
            current = (key < current -> key) ? current -> left : current -> right;
        }
    }

    return NULL;
}

/*
Erase Case:
	1) 
        (1) '?? ??(RED)'?  '??? ?'? ??:

        (2) '??? ??(delete)'? '?? ??? ?'? ??
                a. RED node: 
                    Don't need fix up afer deleting.
                b. BLACK node: 
                    --?? node? RED? ? :
                        ¢ÙBLACK??node at least has one 'RED??node':
                            delete node's color:BLACK --> extra_black;
                            (LL, RR, LR, RL)change the color + rotation
                            extra_black --> BLACK
                        ¢ÚBLACK??node's ??node are all black:
                            delete node's color:BLACK --> extra_black;
                            ?? ??? ?? RED? ??, 
                            extra_BLACK? ?? ????.
                            (until it meets the RED Node or root);

                    --?? node? RED? ? : 
                        delete node's color:BLACK --> extra_black;
                        ?? ??? ?? parent ??? ?? ?? ???.
                        Rotation;
                        Keep the extra_black and fix up.(See the ?? ??'s color to fixup)

            remove : ??? ?? delete? ????.
            replace_node : delete? ?? ??? remove( = delete )? ?? ??? ????. 
            (??? ???? ??? nil ??? ????.)
	
	2) ??? ?? delete? ?? ?? ??? ?? ???? ?? -> 1) / 2)
		remove : ??? ??? ??? ?????? 
	             ?? ?? ??? ???(successor) ??? ????.
	
        replace_node : ??? ??? ?? ??? remove? ?? ??? ????. 
                (??? ??? ?? ?? ??? ???? ??? ?? ?? ??? ????.)

*/
void rbtree_erase(RBTree *T, int key){
    
}

void rbtree_erase_fixup(RBTree *T, RBNode *z){

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
    
        // Print the Red Black Tree
        printf("Red Black Tree:\n");
        printTree(T, T -> root, 0, 0);
    }

    // Free the Red Black Tree
    delete_rbtree(T);

    return 0;
}

