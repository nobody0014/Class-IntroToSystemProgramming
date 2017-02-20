/* Name:
 * ID:
 */
#include <stdlib.h>
#include <stdio.h>
#include "btree.h"
void printHelp(Node *tree, int level);
/* 
Malloc locations:
At the construction of the node.
*/
  

/*
Design (for my own sanity)
1)Initializing
    -If tree is null, malloc new node and set the data 
    to be the value
    -left and right to be null
2)Inserting
    -if value is more than the current value, do 
    insert recursively by throwing in the reference of
    right.
    -if the location has a value already (not null),
    throw it in normally, if it is NULL, malloc and put the 
    value and do nothing else
*/
void insert(Node **tree, int val) {
    if (!*tree){
        *tree = (Node *) malloc(sizeof(Node));
        (*tree)->data = val;
        (*tree)->left = NULL;
        (*tree)->right = NULL;
    }else{
        if ((*tree)->data > val){ //go left
            insert(&((*tree)->left),val); 
        }else{ //go right
            insert(&((*tree)->right),val); 
        }
    }

}

/*
Zero fucking clue on how to make the ascii format.
However, the in order can be done easily by going in
to the left node first after priting the root.
*/
/***** Expected output: *****
7
|-2
  |-1
  |-4
|-10
  |-15
    |-12
      |-11

*****************************/
void print(Node *tree) {
    printHelp(tree,-1);
}
void printHelp(Node *tree, int level){
    for (int i = 0; i < level; ++i){
        printf("  ");
    }
    if (level >= 0){
        printf("|-");
    }
    printf("%d\n", tree->data);
    if (tree->left){
        printHelp(tree->left,level+1);
    }
    if (tree->right){
        printHelp(tree->right,level+1); 
    }
}

/*
Steps
1) if the done is NULL, do nothing
2) assign the right and left node in temp var first
3) free the root node (dont forget to null the right and left)
4) call delete(node) for the left and right node
*/
void delete(Node *tree) {
    if (tree){
        Node *rn = tree->right;
        Node *ln = tree->left;
        tree->right = NULL;
        tree->left = NULL;
        free(tree);
        delete(rn);
        delete(ln);
        rn = NULL;
        ln = NULL;
    }  
}

/*
Steps
1)Check if the node is NULL, if it is then return NULL
2)if the val searching is more then go right node (reference)
    other wise go left node 
3)if the place we are going into is null then return null 
    also, (caring of sec fault although i doubt it will happen)
*/

Node *lookup(Node ** tree, int val) {
    if (!*tree){
        return NULL;
    }
    if ((*tree)->data == val){
        return *tree;
    }else if ((*tree)->data > val){
        return lookup(&((*tree)->left),val);
    }else{
        return lookup(&((*tree)->right),val);
    }
}


/***** Expected output: *****
7
|-2
  |-1
  |-4
|-10
  |-15
    |-12
      |-11
Found
Not Found
 *****************************/
int main(int argc, char **argv)
{
    Node *root = NULL;
    Node *target = NULL;

    // add nodes
    insert(&root, 7);
    insert(&root, 2);
    insert(&root, 4);
    insert(&root, 10);
    insert(&root, 1);
    insert(&root, 15);
    insert(&root, 12);
    insert(&root, 11);

    // Lets see how the tree looks
    printf("printing the tree\n");
    print(root);

    // Check if 4 in the tree
    target = lookup(&root, 4);
    if (target) {
        printf("Found\n");
    } else {
        printf("Not Found\n");
    }

    // Check if 44 in the tree
    target = lookup(&root, 44);
    if (target) {
        printf("Found\n");
    } else {
        printf("Not Found\n");
    }

    // Now let's free up the space
    delete(root);
}
