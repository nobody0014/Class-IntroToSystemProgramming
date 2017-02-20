/* Name: Phornphawit manasut
 * ID: 5780995
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "queue.h"


//Keep tab of malloc: 
//You have to malloc the queue
//You have to malloc the node
//You have to malloc the data within the node

void push(Queue **q, char *word) {
    //Initialize node
    Node *node = malloc(sizeof(node));
    node->next = NULL;

    //Check the tail node, do reallocation of pointers for tail
    if(!(*q)){
        *q = malloc(sizeof(Queue));
        (*q)->head = node;
        (*q)->tail = node;
    }else if(!((*q)->head) && !((*q)->tail)){
        (*q)->head = node;
        (*q)->tail = node;
    }else{
        Node *tailNode = (*q)->tail;
        tailNode->next = node;
        (*q)->tail = node;
    }

    //Copy word into node
    int word_size = strlen(word);
    node->data = malloc(sizeof(char)*word_size);
    strcpy(node->data, word);
}

char *pop(Queue *q) {
    // destroy a head node and move on
    // take free(data) within a node and also free that node
    if (!q->head){
        return NULL;
    }
    Node *toFreeNode = q->head;
    Node *nextNode  = toFreeNode->next;
    char *word = toFreeNode->data;

    if (nextNode != NULL){
        q->head = nextNode;
    }else{
        q->head = NULL;
        q->tail = NULL;
    }

    toFreeNode->next = NULL;
    toFreeNode->data = NULL;
    free(toFreeNode);
    toFreeNode = NULL;
    return word;
}

void print(Queue *q) {
    if(!q){
        printf("No items\n");
    }else if(q->head==NULL && q->tail==NULL ){
        printf("No items\n");
    }else{
        // printf("Words in the queue:\n");
        Node *tailNode = q->tail;
        Node *currentNode = q->head;

        //Printing out logic
        int i = 1;
        while(currentNode != tailNode){
            //Print out the word in the node
            char *word  = currentNode->data;
            printf("%s\n",word);
            //Move on to next node
            currentNode = currentNode->next;
            i++;
        }
        printf("%s\n",currentNode->data);
    }
}

int isEmpty(Queue *q) {
    if(!q){
        return 10;
    }else if(q->head == NULL || q->tail == NULL){
        return 20;
    }
    return 0;
}

void delete(Queue *q) {
    if (q){
        Node *tailNode = q->tail;
        Node *currentNode = q->head;
        
        while(currentNode != tailNode){
            Node *previousNode = currentNode;
            currentNode = currentNode->next;
            free(currentNode->data);
            currentNode->data = NULL;
            free(previousNode);
            previousNode = NULL;
        }

        free(currentNode);
        currentNode = NULL;
        tailNode = NULL;
        
        q->tail = NULL;
        q->head = NULL;
    }
}

/***** Expected output: *****
No items
a
b
c
a
b
c
d
e
f
No items
s = World
t = Hello
*****************************/
int main(int argc, char **argv)
{
    Queue *q = NULL;

    // print the queue
    print(q);

    // push items
    push(&q, "a");
    push(&q, "b");
    push(&q, "c");
    print(q);

    // pop items
    while (!isEmpty(q)) {
        char *item = pop(q);
        // printf("%s\n", item);
        free(item);
    }

    char *item = pop(q);
    assert(item == NULL);

    // push again
    push(&q, "d");
    push(&q, "e");
    push(&q, "f");
    print(q);

    // // destroy the queue
    delete(q);

    // // print again
    print(q);

    // // check copy
    char *s = (char *)malloc(10);
    strcpy(s, "Hello");
    push(&q, s);
    strcpy(s, "World");
    char *t = pop(q);
    printf("s = %s\n", s);
    printf("t = %s\n", t);
    free(t);
    free(s);

    // free the queue
    free(q);
}
