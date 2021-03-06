/* Name:
 * ID:
 */
#include <stdio.h>
#include <stdlib.h>
// #include <string.h>
#include "mergesort.h"

void merge(Entry *output, Entry *L, int nL, Entry *R, int nR) {
    int i = 0, j = 0, k = 0;
    while(k < nL+nR){

    	//Get the slot of the those entry
    	Entry *cL = L+i;
    	Entry *cR = R+j;
    	Entry *cO = output+k;

    	//Check and assign (sorting)
    	//Checking Null doesnt really work so we look at the size
        // printf("Before pushing == i: %d, j: %d,total: %d\n", i, j, nL+nR);
    	if ((nL > i && j < nR && cL->data <  cR->data) || nR <= j){
            // printf("Push in left\n");
    		cO->data = cL->data;
    		cO->name = cL->name;
    		i++;
    	}else{
            // printf("Push in right\n");
    		cO->data = cR->data;
    		cO->name = cR->name;
    		j++;
    	}
    	k++;
        // printf("After pushing == i: %d, j: %d,total: %d\n", i, j, nL+nR);
    }
}

//Printing the content of the entries, for debugging cus seriously you need it
void print_entries(Entry *entries, int n){
	printf("entries content:\n");
	for (int i = 0; i < n; ++i){
		printf("%d %s\n", ((entries+i)->data),(entries+i)->name);
	}
}


void merge_sort(Entry *entries, int n) {

    if (n > 1){
    	//Set up variables
    	Entry *temp = (Entry *) malloc(sizeof(Entry)*n);
    	int rSize = n/2;
    	int lSize = n-rSize;
    	Entry *R = (Entry *) malloc(sizeof(Entry)*rSize);
    	Entry *L  = (Entry *) malloc(sizeof(Entry)*lSize);
    
    	//Copy content over from entries to L and R.	
    	for (int i = 0; i < n; ++i){
    		if (i < lSize){
    			(L+i)->data = (entries+i)->data;
    			(L+i)->name = (entries+i)->name;
    		}else{
    			(R+i-lSize)->data = (entries+i)->data;
    			(R+i-lSize)->name =  (entries+i)->name;
    		}
    	}

    	//merg time
        if(lSize > 1){
            merge_sort(L,lSize);
        }
        if (rSize > 1){
            merge_sort(R,rSize);
        }
    	merge(temp,L,lSize,R,rSize);

    	//Copy content from temp to entries
    	for (int i = 0; i < n; ++i){
    		(entries+i)->data = (temp+i)->data;
    		(entries+i)->name = (temp+i)->name;
    	}

    	//Free everything that you malloc in this instance
    	free(R);
    	free(L);
    	free(temp);
    	temp = NULL;
    	R = NULL;
    	L = NULL;
    }
}

int myStrlen(char *word){
    int count = 0;
    while(word && count <= MAX_NAME_LENGTH){
        word++;
        count++;
    }
    return count;
}

void myStrcpy(char *dest, char *src){
    int i;
    for (i = 0; i < myStrlen(src); ++i){
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

/*
TEST: ./mergesort < test.in
OUTPUT:
1 lsdfjl
2 ghijk
3 ksdljf
5 abc
6 def
*/
int main(void) {
    // IMPLEMENT
    int n;
    scanf("%d", &n);
    Entry *entries = (Entry *) malloc(sizeof(Entry)*n);

    //Take input, have to copy the string inside
    for (int i = 0; i < n; ++i){
    	int tmp;
    	char name[MAX_NAME_LENGTH];
    	scanf("%d %s", &tmp,name);
        entries[i].data = tmp;
        entries[i].name = (char *) malloc(sizeof(char) * (MAX_NAME_LENGTH+1));
    	myStrcpy(entries[i].name,name);
    }

    merge_sort(entries,n);

    //print out entries
    for (int i = 0; i < n; ++i){
    	printf("%d %s\n", ((entries+i)->data),(entries+i)->name);
    }

    //Free the name first then free the entries
    for (int i = 0; i < n; ++i){
    	free((entries[i]).name);
    	(entries[i]).name = NULL;
    }
    free(entries);
    entries = NULL;
}

















