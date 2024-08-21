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
RBNode * rbnode_find(RBTree *T, int key);
//void rbtree_erase_fixup(RBTree *T, RBNode *rmNode, RBNode *parent);
void rbtree_erase_fixup(RBTree *T, RBNode *parent, int is_left);
void rbtree_erase(RBTree *T, int key);
void printTree(RBTree *T, RBNode *node, int type, int level);

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

RBNode * rbnode_find(RBTree *T, int key){
    RBNode *current = T -> root;
    while(current != T ->nil){
        if(key == current -> key){
            printf("Node [%d] is found!\n", key);
    
            return current;
        }
        // According to key to chose the LEft Tree or RIGHT Tree.
        current = (key < current->key) ? current->left : current->right;
        
        if (current != T->nil) {  //Avoid printing the empty nodes.
            printf("Visiting Node %d\n", current->key);
        }
    }
    printf("Can not fine the node[%d]!\n", key);

    return NULL;
}


/*
Erase Case:
	1) 
        (1) The node which will be remove only has LeftChild or RightChild:
            (Only BLACK -> RED)
            THe remoeve node's Child Node will be replace it, 
            Child Node's color will turns RED.

        (2) The node which will be remove has no Child Node:
                a. RED node: 
                    Don't need fix up afer deleting.
                b. BLACK node: 
                    --When the brother node is BLACK:
                        1.brother node at least has one 'RED Node':
                            delete node's color:BLACK --> extra_black;
                            (LL, RR, LR, RL)change the color + rotation
                            extra_black --> BLACK
                        2.The child nodes of brother node are all black:
                            delete node's color:BLACK --> extra_black;
                            The brother node turns RED, 
                            extra_BLACK move up.
                            (until it meets the 'RED Node' or 'root');

                    --When the brother node is RED
                        delete node's color:BLACK --> extra_black;
                        'brother node' and 'parent node' change the colors with each other
                        Rotation;
                        Keep the extra_black and fix up.(See the brother node's color to fixup)
	
	2) The node which will be remove has both of LeftChild and  RightChild 
		
*/

void rbtree_erase(RBTree *T, int key){
    RBNode *delete = rbnode_find(T, key);
    RBNode *remove, *remove_parent, *replace_node;
    int is_remove_black, is_remove_left;

    // Step 1) delete 삭제 후 대체할 replace_node 찾기
    if((delete -> left != T->nil) && (delete -> right != T -> nil)){
        remove = delete -> right;
        while(remove -> left != T -> nil){
        remove = remove -> left;   
        }
        replace_node = remove -> right;
        delete -> key = remove -> key;
    }else{
        remove = delete;
        replace_node = (remove -> right != T -> nil) ? remove -> right : remove -> left;
    }
    remove_parent = remove -> parent;
    
    // Step 2) remove 노드 제거하기
    /* [CASE D1]: remove 노드가 루트인 경우 */
    if(remove == T -> root){
        T -> root = replace_node;
        T -> root -> color = 1;
        free(remove);

        return ; 
    }

    // Step 2-1) 'remove의 부모'와 'remove의 자식' 이어주기
    is_remove_black = remove -> color; 
    is_remove_left = remove_parent->left == remove;

    // Step 2-1-1) 자식 연결
    if (is_remove_left){
        remove_parent->left = replace_node;     
    }
    else
    remove_parent->right = replace_node;

    // Step 2-1-2) 부모도 연결
    replace_node->parent = remove_parent;
    free(remove);

    /* [CASE D2~D6]: remove 노드가 검정 노드인 경우 */
    // Step 3) 불균형 복구 함수 호출
    if (is_remove_black == 1)
    rbtree_erase_fixup(T, remove_parent, is_remove_left);
    return ;
}

void rbtree_erase_fixup(RBTree *T, RBNode *parent, int is_left){
    printf("parent -> key = %d\n", parent -> key);
    RBNode *extra_black = is_left? parent -> left : parent -> right;
    if(extra_black == parent -> left){
        printf("isleft!\n");
    }

    // If rmNode is RED, it can be deleted directly.
    if (extra_black -> color == 2){
        printf("extra_black is RED!\n");
        extra_black -> color = 1;
        return ;
    }

    RBNode *bro = is_left ? parent -> right : parent -> left;
    if(bro == parent -> right){
        printf("bro is right!\n");
        printf("bro -> key = %d\n", bro -> key);
    }
    
    //case: When broNode is RED
    if(bro -> color == 2){
        printf("bro - > color is RED!\n");
        exchange_color(bro, parent);
        if(is_left){
            rbtree_left_rotate(T, bro);
        }else{
            rbtree_right_rotate(T, bro);
        }
        
        rbtree_erase_fixup(T, parent, is_left);

        return ;
    }

    RBNode *bro_left = is_left ? bro -> left : bro -> right;
    RBNode *bro_right = is_left ? bro -> right : bro -> left;
    
    // case: When broNode is BLACK, and at least has one RED child
    //RL
    if((is_left) && (bro_left -> color == 2) && (bro_right -> color == 1)){
        exchange_color(bro, parent);
        rbtree_right_rotate(T, bro_left);
        rbtree_left_rotate(T, bro_left);

        return ;
    }
    //RR
    if((is_left) && (bro_right -> color == 2)){
        printf("RR!\n");
        exchange_color(bro, bro_right);
        exchange_color(parent, bro);
        parent -> color = 1;
        rbtree_left_rotate(T, bro);

        return ;
    }
    //LR
    if((bro_left -> color == 2) && (bro_right -> color == 1)){
        exchange_color(parent, bro_right);
        rbtree_left_rotate(T, bro_right);
        rbtree_right_rotate(T, bro_right);

        return ;
    }

    //LL
    if(bro_right -> color == 2){
        exchange_color(bro, bro_right);
        exchange_color(parent, bro_right);
        parent -> color = 1;
        rbtree_right_rotate(T, bro);

        return ; 
    }
    
    //case: when bro is BLACK, and bros' children are all BLACK
    bro -> color = 2;
    

    if(parent != T-> root){
        rbtree_erase_fixup(T, parent -> parent, parent -> parent -> left == parent);
    }
    
}

/*
void rbtree_erase(RBTree *T, int key){
    RBNode *rmNode = rbnode_find(T, key);
    RBNode *root = T -> root;

    RBNode *temp, *child, *parent;
    int color;

    // When the RemoveNode has 2 kids:
    if((rmNode -> left != T ->nil) && (rmNode -> right != T -> nil)){
        printf("This rmNode has two tries!\n");
        // Find the successor node of the node to be deleted, 
        // which is the leftmost leaf node of the right subtree 
        temp = rmNode -> right;
        while(temp -> left != T -> nil){
            temp = temp -> left;
        }
        printf("temp = %d\n", temp -> key);

        parent = rmNode -> parent;
        // Determine 'whether' the rmNode is not 'the root node'
        if(rmNode -> parent != T -> nil){
            if(rmNode == rmNode -> parent -> left){
                // if rmNode is the leftChild
                rmNode -> parent -> left = temp;
            }else{//if rmNode is the rightChild
                rmNode -> parent -> right =temp;
            }
        }else{
            // if rmNode is the root
            root = temp;
        }
        //------------------------------------------------------------
        // The problem shifted to deleting the original temp
        parent = temp -> parent;

        // child is the right child of temp. and temp must not have a left child
        // So just let the child replace it directly~ 
        child = temp -> right;

        //
        if(parent == rmNode){
            parent = temp;
        }else{
            
            // If child exist, and make it be the parent's left child
            // Deal the relationship bewween 
            //[temp's parent and temp's child]
            if(child != NULL){
                child -> parent = parent;
                child -> color = 1;
            }
            parent -> left = child;
            
            // Deal with the relationship between 
            //[temp and rmNode];
            temp -> right = rmNode -> right;
            rmNode -> right -> parent = temp;
            
        }

        // Fixup the temp(rmNode)
        // Fixup temp(rmNode)'s parent, color, child
        temp -> parent = rmNode -> parent;
        temp -> color = rmNode -> color;

        temp -> left = rmNode -> left;
        rmNode -> left -> parent = temp;
    
    //----------------------------------------------------
    }else{  
        if(rmNode -> left != T -> nil){
             child = rmNode -> left;
             printf("This rmNode has left CHild!\n");
        }else{
            child = rmNode -> right;
            printf("This rmNode has right CHild\n or This rmNode has no child!\n");
        }
        parent = rmNode -> parent;
        color = rmNode -> color;
        printf("color: %s\n", (color == RED) ? "R" : "B");

        // When the RemoveNode has one kid:
        if(child != T -> nil){
            child -> parent = parent;
        }

        // When the RemoveNode is not the root
        // And Init the parent Pointer
        if(parent != T -> nil){
            // If the rmNode is the leftChild
            if(parent -> left == rmNode){
                parent -> left = child;
                printf("rmNode is the leftChild!\n");
            // If the rmNode is the rightChild
            }else{
                parent -> right = child;
                printf("rmNode is the rightChild!\n");
            }
        }
    }
    if(color == BLACK){
        printf("rmNode's color is BLACK!\n");
        rbtree_erase_fixup(T, child, parent);
        free(rmNode);
        return;
    }

}
*/

/*
void rbtree_erase_fixup(RBTree *T, RBNode *parent, int is_left){
    RBNode *root = T -> root;
    RBNode *bro;
    RBNode *bro_child;
    //int color;

    while(((rmNode != root)) && ((rmNode -> color != 1 || rmNode == T -> nil))){
        // When rmNode is left child 
        // and broNode is right child
        if(parent -> left == rmNode){
            bro = parent -> right; // (RR) + (RL) (bro is right child)
            //--------------------------------------------------


            // When bro Node is 'RED'
            if(bro -> color == 2){
                //change the color (parent, bro)
                exchange_color(parent, bro);
                rbtree_left_rotate(T, parent);
            }

            // When bro Node is 'BLACK', 
            if(bro -> color == 1){
                //RR
                if(bro -> right -> color == 2){
                    bro_child = bro -> right;

                    // change the color
                    exchange_color(bro, bro_child);
                    exchange_color(parent, bro);
                    parent -> color = 1;

                    //rotation
                    rbtree_left_rotate(T, bro);

                    break;
                }
                //RL
                if((bro -> left -> color == 2) && (bro -> right -> color == 1)){
                    bro_child = bro -> left;

                    // change the color
                    exchange_color(parent, bro -> left);
                    //parent -> color = 1;

                    // rotation
                    rbtree_right_rotate(T, bro);
                    rbtree_left_rotate(T, bro_child);
                }
                // When bros' children are all 'BLACK'
                if((bro -> left -> color == 1)  && (bro -> right -> color == 1)){
                    bro -> color = 2;
                    rmNode = parent;
                    parent = rmNode -> parent;
                }
                

            }
        }else{
            // When rmNode is right child 
            // and broNode is left child
            bro = parent -> left;

            // When bro Node is 'RED'
            if(bro -> color == 2){
                exchange_color(bro, parent);
                rbtree_right_rotate(T, bro);
            }

            // When bro Node is 'BLACK'
            if(bro -> color == 1){
                //LL
                if(bro -> left -> color == 2){
                    exchange_color(bro, bro -> left);
                    exchange_color(parent, bro);
                    parent -> color = 1;
                    rbtree_right_rotate(T, bro);

                    break;
                }
                //LR
                if((bro -> right -> color == 2) && (bro -> left -> color == 1)){
                    exchange_color(parent, bro -> right);
                    rbtree_left_rotate(T, bro -> right);
                    rbtree_right_rotate(T, bro -> right);
                }
                // When bros' children are all 'BLACK'
                if((bro -> left -> color == 1)  && (bro -> right -> color == 1)){
                    bro -> color == 2;
                    rmNode = parent;
                    parent = rmNode -> parent;
                }

            }
        }
    }
    rmNode -> color = 1;
    
}

*/

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
    }

    // Print the Red Black Tree
    printf("Red Black Tree:\n");
    printTree(T, T -> root, 0, 0);
    
    //Erase
    printf("---------------------------------------\n");
    rbtree_erase(T, 18);

    // Print the Red Black Tree
    printf("Red Black Tree:\n");
    printTree(T, T -> root, 0, 0);
    
    //Erase
    printf("---------------------------------------\n");
    rbtree_erase(T, 25);

    // Print the Red Black Tree
    printf("Red Black Tree:\n");
    printTree(T, T -> root, 0, 0);

    //Erase
    printf("---------------------------------------\n");
    rbtree_erase(T, 15);

    // Print the Red Black Tree
    printf("Red Black Tree:\n");
    printTree(T, T -> root, 0, 0);

    //Erase
    printf("---------------------------------------\n");
    rbtree_erase(T, 6);

    // Print the Red Black Tree
    printf("Red Black Tree:\n");
    printTree(T, T -> root, 0, 0);

    //Erase
    printf("---------------------------------------\n");
    rbtree_erase(T, 13);

    // Print the Red Black Tree
    printf("Red Black Tree:\n");
    printTree(T, T -> root, 0, 0);

    //Erase
    printf("---------------------------------------\n");
    rbtree_erase(T, 37);

    // Print the Red Black Tree
    printf("Red Black Tree:\n");
    printTree(T, T -> root, 0, 0);
    

    //------------------------------------------
    // Free the Red Black Tree
    //delete_rbtree(T);


    return 0;
}

