/* Do not modify */
#ifndef CQUEUE_H
#define CQUEUE_H

struct node_struct {
    char *data;
    struct node_struct *next;
};

typedef struct node_struct Node;

struct queue_struct {
    Node *head, *tail;
};

typedef struct queue_struct Queue;

/* Push a word to the back of this queue
 * You must keep a *COPY* of the word.
 * If q is NULL, allocate space for it here
 */
void push(Queue **q, char *word);

/* Returns the data at the front of the queue
 * and remove it from the queue as well.
 * If q is empty, return NULL
 */
char *pop(Queue *q);

/* Checks if the queue is empty */
int isEmpty(Queue *q);

/* Prints out the current queue, front to back.
 * If the queue is empty, prints out "No items"
 */
void print(Queue *q);

/* Deallocates all items in the queue */
void delete(Queue *q);

#endif
