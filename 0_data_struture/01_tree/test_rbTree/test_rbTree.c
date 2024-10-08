#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

#define MAX_TREE_SIZE 100                   // Maximum number of elements
#define INPUT_FILE1_NAME "input2.txt"         // Input file containing input data 
#define INPUT_FILE2_NAME "input3.txt"         // Input file containing input data 

//CLRS 
//Insertion and Deletion in a Red Black Tree
enum type {RED,BLACK};

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    enum type color;
};

struct Queue
{
    struct Node* data;
    struct Queue* next;
};

struct Queue* front = NULL;
struct Queue* rear = NULL;

struct Node* pfront()
{
    struct Node* data ;
    data = front->data;
    return data;
}

//Read input data from a file and write the data into buffer
int readInput(const char *filename, int *buffer)
{
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

void printFile(int inputTotal, int inputData[])
{
    // Print the result
    for(int i = 0; i < inputTotal; i++){
        printf("%d ", inputData[i]);
    }
}

int isempty()
{
    if(front==NULL)
        return 1;

    else
        return 0;
}

void dequeue()
{
    if(isempty())
        return ;

    struct Queue* temp = front;
    front = front->next;
    free(temp);
}


void enqueue(struct Node* data)
{
    struct Queue* temp  =(struct Queue*)malloc(sizeof(struct Queue));
    temp->data = data;
    temp->next = NULL;

    if(front==NULL && rear == NULL)
    {
        front = rear = temp;
        return;
    }

    rear->next = temp;
    rear = temp;
}

void levelorder(struct Node* root)
{
    if(root==NULL)
        return;

    enqueue(root);

    while(!isempty())
    {
        struct Node* current = pfront();
        printf("%d ",current->data);

        if(current->left!=NULL)
            enqueue(current->left);

        if(current->right!=NULL)
            enqueue(current->right);

        dequeue();
    }
}

void LeftRotate(struct Node** T,struct Node** x)
{
    struct Node* y = (*x)->right;
    (*x)->right = y->left;

    if(y->left!=NULL)
        y->left->parent = *x;

    y->parent = (*x)->parent;

    if((*x)->parent == NULL)
        *T = y;

    else if(*x == (*x)->parent->left)
        (*x)->parent->left = y;

    else
        (*x)->parent->right = y;

    y->left = *x;

    (*x)->parent = y;

}
void RightRotate(struct Node** T,struct Node** x)
{
    struct Node* y = (*x)->left;
    (*x)->left = y->right;

    if(y->right!=NULL)
        y->right->parent = *x;

    y->parent = (*x)->parent;

    if((*x)->parent==NULL)
        *T = y;

    else if((*x)== (*x)->parent->left)
        (*x)->parent->left = y;

    else
        (*x)->parent->right = y;

    y->right = *x;
    (*x)->parent = y;

}

void RB_insert_fixup(struct Node** T, struct Node** z)
{
    struct Node* grandparent = NULL;
    struct Node* parentpt = NULL;

    while(((*z)!=*T)&& ((*z)->color!= BLACK) && ((*z)->parent->color == RED))
    {
        parentpt = (*z)->parent;
        grandparent = (*z)->parent->parent;

        if(parentpt == grandparent->left)
        {
            struct Node* uncle = grandparent->right;

            if(uncle!=NULL && uncle->color == RED)
            {
                grandparent->color = RED;
                parentpt->color = BLACK;
                uncle->color = BLACK;
                *z = grandparent;
            }

            else
            {
                if((*z) == parentpt->right)
                {
                    LeftRotate(T,&parentpt);
                    (*z) = parentpt;
                    parentpt = (*z)->parent;
                }

                RightRotate(T,&grandparent);
                parentpt->color = BLACK;
                grandparent->color = RED;
                (*z) = parentpt;
            }
        }

        else
        {
            struct Node* uncle = grandparent->left;

            if(uncle!=NULL && uncle->color == RED)
            {
                grandparent->color = RED;
                parentpt->color = BLACK;
                uncle->color = BLACK;
                (*z) = grandparent;
            }

            else
            {
                if((*z) == parentpt->left)
                {
                    RightRotate(T,&parentpt);
                    (*z) = parentpt;
                    parentpt = (*z)->parent;
                }

                LeftRotate(T,&grandparent);
                parentpt->color = BLACK;
                grandparent->color = RED;
                (*z) = parentpt;
            }
        }
    }
    (*T)->color = BLACK;

}

struct Node* RB_insert(struct Node* T,int data)
{
    struct Node* z = (struct Node*)malloc(sizeof(struct Node));
    z->data = data;
    z->left = NULL;
    z->right = NULL;
    z->parent = NULL;
    z->color = RED;

    struct Node* y = NULL;
    struct Node* x = T;//root

    while(x!=NULL)
    {
        y = x;
        if(z->data < x->data)
            x = x->left;

        else
            x = x->right;
    }
    z->parent = y;

    if(y==NULL)
        T = z;

    else if(z->data < y->data)
        y->left = z;

    else
        y->right = z;

    RB_insert_fixup(&T,&z);

    return T;
}

void preorder(struct Node* root)
{
    if(root==NULL)
        return;

    printf("%d ",root->data);
    preorder(root->left);
    preorder(root->right);
}

struct Node* Tree_minimum(struct Node* node)
{
    while(node->left!=NULL)
        node = node->left;

    return node;
}

void RB_delete_fixup(struct Node** T, struct Node** x)
{
    while((*x)!=*T && (*x)->color == BLACK)
    {
        if((*x)==(*x)->parent->left)
        {
            struct Node* w = (*x)->parent->right;

            if(w->color==RED)
            {
                w->color = BLACK;
                (*x)->parent->color = BLACK;
                LeftRotate(T,&((*x)->parent));
                w = (*x)->parent->right;
            }

            if(w->left->color==BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                (*x) = (*x)->parent;
            }

            else
            {
                if(w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(T,&w);
                    w = (*x)->parent->right;
                }

                w->color = (*x)->parent->color;
                (*x)->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(T,&((*x)->parent));
                (*x) = *T;
            }
        }

        else
        {
            struct Node* w = (*x)->parent->left;

            if(w->color==RED)
            {
                w->color = BLACK;
                (*x)->parent->color = BLACK;
                RightRotate(T,&((*x)->parent));
                w = (*x)->parent->left;
            }

            if(w->right->color==BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                (*x) = (*x)->parent;
            }

            else
            {
                if(w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(T,&w);
                    w = (*x)->parent->left;
                }

                w->color = (*x)->parent->color;
                (*x)->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(T,&((*x)->parent));
                (*x) = *T;
            }
        }
    }
    (*x)->color = BLACK;

}

void RB_transplat(struct Node** T, struct Node** u,struct Node** v)
{
    if((*u)->parent == NULL)
        *T = *v;

    else if((*u)==(*u)->parent->left)
        (*u)->parent->left = *v;
    else
        (*u)->parent->right = *v;

    if((*v)!=NULL) 
        (*v)->parent = (*u)->parent;
}

struct Node* RB_delete(struct Node *T,struct Node* z)
{
    struct Node *y = z;
    enum type yoc;
    yoc = z->color; // y's original color

    struct Node* x;

    if(z->left==NULL )
    {
        x = z->right;
        RB_transplat(&T,&z,&(z->right));
    }

    else if(z->right==NULL )
    {
        x = z->left;
        RB_transplat(&T,&z,&(z->left));
    }

    else
    {
        y = Tree_minimum(z->right);
        yoc = y->color;
        x = y->right;

        if(y->parent==z)
            x->parent = y;

        else
        {
            RB_transplat(&T,&y,&(y->right));
            y->right = z->right;
            y->right->parent = y;
        }

        RB_transplat(&T,&z,&y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if(yoc==BLACK)
        RB_delete_fixup(&T,&x);

    return T;
}

struct Node* BST_search(struct Node* root, int x)
{
    if(root==NULL || root->data == x)
        return root;

    if(root->data > x)
       return  BST_search(root->left,x);
    else
        return BST_search(root->right,x);
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
    // Structures for timing data
    struct rusage before, after;


    // Benchmarks
    double time_insert = 0.0, time_delete = 0.0; 

    struct Node* RBT = NULL;

    // Insert Node:
    printf("----------------Insert node!------------------\n");
    getrusage(RUSAGE_SELF, &before);
    RBT = RB_insert(RBT,15);
    RBT = RB_insert(RBT,9);
    RBT = RB_insert(RBT,18);
    RBT = RB_insert(RBT,6);
    RBT = RB_insert(RBT,17);
    RBT = RB_insert(RBT,13);
    RBT = RB_insert(RBT,23);
    RBT = RB_insert(RBT,27);
    RBT = RB_insert(RBT,34);
    RBT = RB_insert(RBT,10);
    RBT = RB_insert(RBT,25);
    RBT = RB_insert(RBT,37);
    getrusage(RUSAGE_SELF, &after);
    time_insert =  calculate(&before, &after);


    printf("\nPreorder - ");
    preorder(RBT);

    printf("\nLevel order - ");
    levelorder(RBT);

    struct Node* a = BST_search(RBT,18);
    RBT = RB_delete(RBT,a);
    printf("\nLevel order - ");
    //printf("\nPreorder - ");
    //preorder(RBT);
    front = NULL; rear = NULL; // Delete old Queue
    levelorder(RBT);

    struct Node* b = BST_search(RBT,25);
    RBT = RB_delete(RBT,b);
    printf("\nLevel order - ");
    front = NULL; rear = NULL; // Delete old Queue
    levelorder(RBT);

    /*
     struct Node* c = BST_search(RBT,15);
    RBT = RB_delete(RBT,c);
    printf("\nLevel order - ");
    levelorder(RBT);

    struct Node* e = BST_search(RBT,6);
    RBT = RB_delete(RBT,e);
    printf("\nLevel order - ");
    levelorder(RBT);


    struct Node* f = BST_search(RBT,13);
    RBT = RB_delete(RBT,f);
    printf("\nLevel order - ");
    levelorder(RBT);


    struct Node* k = BST_search(RBT,37);
    RBT = RB_delete(RBT,k);
    printf("\nLevel order - ");
    levelorder(RBT);


    struct Node* g = BST_search(RBT,27);
    RBT = RB_delete(RBT,g);
    
    printf("\nLevel order - ");
    levelorder(RBT);


    struct Node* h = BST_search(RBT,17);
    RBT = RB_delete(RBT,h);
    printf("\nLevel order - ");
    levelorder(RBT);

    struct Node* i = BST_search(RBT,34);
    RBT = RB_delete(RBT,i);
    printf("\nLevel order - ");
    levelorder(RBT);
        
   

    struct Node* j = BST_search(RBT,9);
    RBT = RB_delete(RBT,j);
    printf("\nLevel order - ");
    levelorder(RBT);


    struct Node* l = BST_search(RBT,10);
    RBT = RB_delete(RBT,l);
    printf("\nLevel order - ");
    levelorder(RBT);


    struct Node* m = BST_search(RBT,23);
    RBT = RB_delete(RBT,m);
    printf("\nLevel order - ");
    levelorder(RBT);

    */

    

    

    return 0;
}