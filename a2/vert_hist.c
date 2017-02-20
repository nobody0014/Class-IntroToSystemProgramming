#include <stdio.h>
#include <ctype.h>

//return the maximum value
int findMax(int arr[]){
	int  max = -1;
	for (int i = 0; i < 26; ++i){
		if (max < arr[i]){
			max = arr[i];
		}
	}
	return max;
}

int main(){
	int alphabets[26];
	for (int i = 0; i < 26; ++i){
		alphabets[i] = 0;
	}

	char c = 'a';
	while(c != EOF){
		c = getchar();
		c = tolower(c);
		alphabets[c-'a'] =  alphabets[c-'a']+1;
	}

	int count = findMax(alphabets);
	for (int i = 0; i < count; ++i){
		int toFind = findMax(alphabets);
		for (int j = 0; j < 26; ++j){
			if (alphabets[j] == toFind){
				printf("%c", '*');
				alphabets[j] -= 1;
			}else{
				printf(" ");
			}
		}
		printf("\n");
	}
	printf("abcdefghijklmnopqrstuvwxyz\n");

	return 0;
}


