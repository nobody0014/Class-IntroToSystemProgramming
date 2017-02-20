#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


void tabToSpaces(int spaces){
	char c = getchar();
	while(c != EOF){
		if (c != '\t'){
			printf("%c", c);
		}else{
			for (int i = 0; i < spaces; ++i){
				printf(" ");
			}
		}
		if (c == EOF){
			break;
		}
		c = getchar();
	}
	printf("\n");
}

void spacesToTab(int spaces){
	char c = getchar();
	while(c != EOF){
		if (c == ' '){
			char str[spaces];
			str[0] = c;
			int until = 1;
			int turnToTab = 1;
			for (int i = 1; i < spaces; i++){
				c = getchar();
				until++;
				if (c != ' '){
					str[i] = c;
					turnToTab = 0;
					break;
				}else{
					str[i] = c;
				}
				if (c == EOF){
					break;
				}
			}
			if (turnToTab == 0){
				for (int i = 0; i < until; i++){
					printf("%c", str[i]);
				}
			}else{
				printf("\t");
			}
		}else{
			printf("%c", c);
		}
		if (c == EOF){
			break;
		}
		c = getchar();
	}
	printf("\n");
}


int main(int argc, char *argv[] ){
	if (argc == 3){
		int converted = atoi(argv[2]);
		if (converted != 0 && strncmp(argv[1],"-d",2) == 0){
			tabToSpaces(converted);
		}else if ( converted != 0 && strncmp(argv[1],"-e",2) == 0){
			spacesToTab(converted);
		}else{
			printf("%s\n", "Invalid input");
		}
	}else{
		printf("%s\n", "Invalid Input");
	}
	return 0;
}
