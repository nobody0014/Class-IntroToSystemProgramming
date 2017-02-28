#include <stdio.h>

int check_most(int *i){
	int msb;
	int status;
	msb = 1 << (sizeof(int) -1);

	//At this line, we are able to get the status but in my laptop
	//they give 1 at the most sig bit if it is but i dont want 
	status = (((*i)&(1 << msb)) >> msb );

	return status & 1;
}

int main(){
	int i = 11;
	printf("%d's least bit check: %d\n", i,check_most(&i));

	i = 12;
	printf("%d's least bit check: %d\n", i,check_most(&i));

	i = 16;
	printf("%d's least bit check: %d\n", i,check_most(&i));

	i = 21;
	printf("%d's least bit check: %d\n", i,check_most(&i));

	i = -1;
	printf("%d's least bit check: %d\n", i,check_most(&i));

	i = 2147483647;
	printf("%d's least bit check: %d\n", i,check_most(&i));

	i = -50;
	printf("%d's least bit check: %d\n", i,check_most(&i));
}
