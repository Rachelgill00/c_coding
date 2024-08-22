#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

#define MAX_TREE_SIZE 100                   // Maximum number of elements
#define INPUT_FILE1_NAME "input2.txt"         // Input file containing input data 
#define INPUT_FILE2_NAME "input3.txt"         // Input file containing input data 

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

int readInput(const char *filename, int *buffer);
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
double calculate(const struct rusage *b, const struct rusage *a);

//Read input data from a file and write the data into buffer
int readInput(const char *filename, int *buffer){
    FILE* fd;
    int i = 0;

    if((fd = fopen(filename, "r")) == NULL){
        printf("Error: Failure to open '%s'!\n", filename);
        exit(0);
        return -1; 
    }

    /* read input file to get task parameters */
    while(i < MAX_TREE_SIZE && fscanf(fd, "%d", &buffer[i]) != EOF) {
        i++;
    }

    if (i > MAX_TREE_SIZE){
        printf("Error: Invalid input data in '%s'.\n", filename);
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
        printf("remove -> key = %d\n", remove -> key);
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
    is_remove_black = (remove -> color == 1)? 1 : 2; 
    printf("is_remove_black ?  %d\n", is_remove_black);
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
    if (is_remove_black == 1){
        printf("remove is BLACK!\n");
        rbtree_erase_fixup(T, remove_parent, is_remove_left);
    }
    return ;
}

void rbtree_erase_fixup(RBTree *T, RBNode *parent, int is_left){
    printf("fixup------------\n");
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

    RBNode *bro_left = bro -> left;
    RBNode *bro_right = bro -> right;

    printf("bro -> key : %d\n", bro -> key);
    printf("bro -> right -> key : %d\n", bro -> right -> key);
    printf("bro -> right -> color : %d\n", bro -> right -> color);
    
    // case: When broNode is BLACK, and at least has one RED child
    //RL
    if((is_left) && (bro_left -> color == 2) && (bro_right -> color == 1)){
        printf("RL!\n");

        exchange_color(parent, bro_left);
        parent -> color = 1;
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
    if((bro_right -> color == 2) && (bro_left -> color == 1)){
        printf("LR!\n");

        exchange_color(parent, bro_right);
        parent -> color = 1;
        rbtree_left_rotate(T, bro_right);
        rbtree_right_rotate(T, bro_right);

        return ;
    }

    //LL
    if(bro_left -> color == 2){
        printf("LL!\n");
        exchange_color(bro, bro_right);
        exchange_color(parent, bro_right);
        parent -> color = 1;
        rbtree_right_rotate(T, bro);

        return ; 
    }
    
    //case: when bro is BLACK, and bros' children are all BLACK
    printf("all balck!!!!!!!!!!!!!!!!\n");
    bro -> color = 2;
    // Print the Red Black Tree
    printf("Red Black Tree:\n");
    printTree(T, T -> root, 0, 0);
    
    

    if(parent != T-> root){
        rbtree_erase_fixup(T, parent -> parent, parent -> parent -> left == parent);
    }
}

// Returns number of seconds between b and a 
double calculate(const struct rusage *b, const struct rusage *a)
{
    if( b == NULL || a == NULL){
        return 0.0;
    }else{
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
    }
}

int main()
{
    int inputTotal;                         // Number of tree size
    int deleteTotal;                        // Number of delete size
    int inputData[MAX_TREE_SIZE];           // Tree's value
    int inputDeleteData[MAX_TREE_SIZE];     // The values and order of deleted nodes 
    
    // Read input data from a file
    inputTotal = readInput(INPUT_FILE1_NAME, inputData);
    deleteTotal = readInput(INPUT_FILE2_NAME, inputDeleteData);

    // Print the result
    printFile(inputTotal, inputData);
    printf("\n");

    printFile(deleteTotal, inputDeleteData);
    printf("\n");

    // Structures for timing data
    struct rusage before, after;


    // Benchmarks
    double time_insert = 0.0, time_delete = 0.0; 

    //---------------------------------------------------------------

    //Init a Red Black Tree
    RBTree *T = new_rbtree();    //Insert the nodes to the Red Black Tree

    getrusage(RUSAGE_SELF, &before);
    //for(int repeat = 0; repeat < 1000; repeat++) {
        for(int i =0; i< inputTotal; i++)
        {
            printf("-----------------------------node:%d\n", inputData[i]);
            rbtree_insert(T, inputData[i]);   
            // Print the Red Black Tree
            printf("Red Black Tree:\n");
            printTree(T, T -> root, 0, 0);         
        }
       
        printf("----------------Delete node!------------------\n");
        for(int d = 0; d < deleteTotal; d++)
        {
            printf("-----------------------------node:%d\n", inputDeleteData[d]);
            rbtree_erase(T, inputDeleteData[d]);
            
            // Print the Red Black Tree
            printf("Red Black Tree:\n");
            printTree(T, T -> root, 0, 0);
            
        }
    //}
    
    getrusage(RUSAGE_SELF, &after);
    time_insert = calculate(&before, &after);

    
    // getrusage(RUSAGE_SELF, &before);
    // for(int repeat = 0; repeat < 100; repeat++) {
        
    // }
    // getrusage(RUSAGE_SELF, &after);
    // time_delete = calculate(&before, &after);

    // Report benchmarks
    printf("TIME IN INSERT:      %.6f\n", time_insert);
    //printf("TIME IN DELETE:      %.2f\n", time_delete);
    //printf("TIME IN TOTAL:       %.2f\n\n",time_insert + time_delete);
    
    return 0;

}