#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//comparator used to sort items
int cmpc(const void * c , const void * d){
	return (*(char *)c - *(char *)d);
}

void sortString(char *w){
	int s = 0;
	while(*w != '\0'){
		w++;
		s++;
	}
	for (int i = 0; i < s; ++i){
		w--;
	}
	qsort(w,s,sizeof(char),cmpc);
}

int getStrLen(char *cptr){
	int size = 0;
	while(*cptr != '\n' && *cptr != '\0'){
		cptr++;
		size++;
	}
	return size;
}

int checkSameWord(char *w1, char *w2){
	while(*w1 != '\0'){
		if (*w1 != *w2){
			return 0;
		}
		w1++;
		w2++;
	}
	return 1;
}

void cleanWord(char *w){
	int w_size = getStrLen(w);
	for (int i = 0; i < w_size; ++i){
		w++;
	}
	*w = '\0';
}

void searchThrough(FILE *dptr, char *word){
	int word_size = getStrLen(word);
	char line[40];
	char linecpy[40];
	int found = 0;
	fseek(dptr, 0, SEEK_SET);
	while (!feof(dptr)){
		fgets(line, sizeof(line), dptr);
		int dword_size = getStrLen(line);
		if (word_size == dword_size) {
			strcpy(linecpy, line);
			cleanWord(linecpy);
			sortString(linecpy);
			if (checkSameWord(linecpy, word) == 1) {
				cleanWord(line);
				printf("%s ", line);
				found = 1;
			}
		}
	}
	if (found == 0){
		printf("%s", "NO MATCHES");
	}
	printf("\n");
}

int main(int argc, char *argv[]){
	if (argc == 3){

		FILE *dp;
		dp = fopen(argv[1],"r");

		FILE *fp;
		char buffer[20];
		fp = fopen(argv[2], "r");
		while (fgets(buffer, sizeof(buffer), fp) != NULL){
			cleanWord(buffer);
			printf("%s: ", buffer);
			sortString(buffer);
			searchThrough(dp,buffer);
    }
    fclose(fp);
    fclose(dp);
	}else{
		printf("%s\n", "incorrect input");
		return 1;
	}
	return 0;
}

//idea to do this
//1) check if the same length --> otherwise skip
//2) sort the character for both side then check one by one --> easy to implement but may take awhile
//2.alternative) do 2 array to keep the item and then do minus and + or some shit, 2 sounds better tho
