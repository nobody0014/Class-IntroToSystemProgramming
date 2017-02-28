#include <stdio.h>

int check_least(int *i){
	return (*i)&1;
}

int main(){
	int i = 11;
	printf("%d's least bit check: %d\n", i,check_least(&i));

	i = 12;
	printf("%d's least bit check: %d\n", i,check_least(&i));

	i = 16;
	printf("%d's least bit check: %d\n", i,check_least(&i));

	i = 21;
	printf("%d's least bit check: %d\n", i,check_least(&i));
}
