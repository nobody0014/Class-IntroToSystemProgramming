/* Do not modify */
#ifndef BTREE_H
#define BTREE_H

struct node_struct {
    int data;
    struct node_struct *right, *left;
};

typedef struct node_struct Node;

/* Inserts a value into the tree rooted at a given node
 * If the given root node is NULL, it is allocated in here
 */
void insert(Node **tree, int val);

/* Deallocates nodes under a give node */
void delete(Node *tree);

/* Returns the pointer to the node containing val
 * or, NULL is the number is not found.
 */
Node *lookup(Node **tree, int val);

/* Prints out the tree in ascii format */
void print(Node *tree);

#endif
