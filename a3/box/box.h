/* Do not modify */
#ifndef BOX_H
#define BOX_H

typedef struct {
    int *data;
    int size;
    int cap;
} Box;

/* Creates a new box with 'init_cap' capacity */
void createBox(Box **b, int init_cap);

/* Inserts an element into a box. If the box
 * is full, double the capacity of the box
 */
void insert(Box *b, int elem);

/* Removes all occurances of an element from a box.
 * After removal, the elements in the box should be condensed i.e. no gap
 * between any two elements. The capacity of the box
 * remains unchanged after removal.
 */
void removeAll(Box *b, int elem);

/* Prints out elements in a box */
void printBox(Box *b);

/* Returns the mean of data in a box */
double getMean(Box *b);


#endif
