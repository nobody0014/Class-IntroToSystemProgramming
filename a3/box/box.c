/* Name:
 * ID:
 */
#include <stdio.h>
#include <stdlib.h>
#include "box.h"

void createBox(Box **b, int init_cap) {
    // IMPLEMENT
    if(!*b){
        *b = (Box *) malloc(sizeof(Box));
        (*b)->data = malloc(sizeof(int)*init_cap);
        (*b)->size = 0;
        (*b)->cap = init_cap;
    }
    return;
}

void insert(Box *b, int elem) {
    if (b->size >= b->cap){
        b->cap *= 2;
        b->data = realloc(b->data, sizeof(int)*b->cap);
    }
    int i = 0;
    while(i < b->size){
        b->data++;
        i++;
    }
    *(b->data) = elem;
    while(i > 0){
        b->data--;
        i--;
    }
    b->size++;
    if (b->size >= b->cap){
        b->cap *= 2;
        b->data = realloc(b->data, sizeof(int)*b->cap);
    }
}

void removeAll(Box *b, int elem) {
    int i = 0;
    int condense_size = 0;
    int *newData = malloc(sizeof(int)*(b->cap));
    while(i < (b->size)){
        int currentElem = *(b->data);
        if(currentElem != elem){
            *newData = currentElem;
            newData++;
            condense_size++;
        }
        b->data++;
        i++;
    }
    b->size = condense_size;

    while(condense_size > 0){
        newData--;
        condense_size--;
    }
    while(i > 0){
        b->data--;
        i--;
    }

    free(b->data);
    b->data = newData;
    newData = NULL;
}

void printBox(Box *b) {
    // IMPLEMENT
    int i = 0;
    while(i < b->size){
        printf("%d\n", *(b->data));
        b->data++;
        i++;
    }
    while(i > 0){
        b->data--;
        i--;
    }
}

double getMean(Box *b) {
    int i = 0;
    int total = 0;
    while(i < b->size){
        total += *(b->data);
        b->data++;
        i++;
    }
    while(i > 0){
        b->data--;
        i--;
    }
    return total/((double) b->size);
}

void dealloc(Box **b) {
    // IMPLEMENT
    free((*b)->data);
    (*b)->data = NULL;
    free(*b);
    b = NULL;
}

/*
TEST: ./box < test.in
OUTPUT:
AVG = 4.00
box1 size = 10
box2 size = 1
box1 cap = 16
box2 cap = 2
-- b1
11
2
3
4
5
2
3
2
2
6
-- b2
2
--
-- b1 (after remove)
11
3
4
5
3
6
--
-- b2 (after remove)
--
*/
int main(int argc, char **argv)
{
    Box *b1 = NULL;
    Box *b2 = NULL;

    createBox(&b1, 1);
    createBox(&b2, 2);


    int n;
    scanf("%d", &n);
    for (int i=0; i<n; i++) {
        int tmp;
        scanf("%d",&tmp);
        insert(b1, tmp);
    }

    insert(b2, 2);
    // printf("Elements:\n");
    // printBox(b2);
    // printf("%p %p %d\n", b2,b2->data,*(b2->data));
    // insert(b2, 4);
    // printf("Elements:\n");
    // printBox(b2);
    // printf("%p %p %d\n", b2,b2->data,*(b2->data));
    // insert(b2, 6);
    // printf("Elements:\n");
    // printBox(b2);
    // printf("%p %p %d\n", b2,b2->data,*(b2->data));
    // insert(b2, 20);
    // printf("Elements:\n");
    // printBox(b2);
    // printf("%p %p %d\n", b2,b2->data,*(b2->data));
    // insert(b2, 6);
    // printf("Elements:\n");
    // printBox(b2);
    // printf("%p %p %d\n", b2,b2->data,*(b2->data));
    // removeAll(b2,6);
    // printf("Elements:\n");
    // printBox(b2);
    // printf("%p %p %d\n", b2,b2->data,*(b2->data));

    printf("AVG = %0.2f\n",getMean(b1));
    printf("box1 size = %d\n",b1->size);
    printf("box2 size = %d\n",b2->size);
    printf("box1 cap = %d\n",b1->cap);
    printf("box2 cap = %d\n",b2->cap);

    printf("-- b1\n");
    printBox(b1);
    printf("-- b2\n");
    printBox(b2);
    printf("--\n");

    removeAll(b1, 2);
    printf("-- b1 (after remove)\n");
    printBox(b1);
    printf("--\n");
    removeAll(b2, 2);
    printf("-- b2 (after remove)\n");
    printBox(b2);
    printf("--\n");

    dealloc(&b1);
    dealloc(&b2);
}
