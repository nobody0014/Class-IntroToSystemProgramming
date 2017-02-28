#include <stdio.h>
int get_bit(unsigned char *integer, int bit_position);

char make_mask_char(int bit_position){
	char mask;
	mask = 1 << bit_position;
	return mask;
}

//Both set and clear depending on val
void set_bit(unsigned char *integer, int index, int val){
	int mask;
	int i;
	i = *integer;
	if (val == 1){
		*integer = i | (1 << index);
	}else{
		mask = 1 << index;
		mask = ~mask;
		*integer = i & mask;
	}
}

void toggle_bit(unsigned int *integer, int index){
	int mask;
	int i = *integer;
	mask = make_mask_char(index);
	*integer = mask^i;
}

int get_bit(unsigned char *integer, int bit_position){
	return !!(*integer & make_mask_char(bit_position));
}

int main(){	
	// unsigned char tester = 0xff;
	// unsigned int result = get_bit(&tester,3);
	// set_bit(&tester,0,0);
	// printf("%x\n", result);
	// printf("%d\n", tester);

	unsigned int i;
	i = 5;
	toggle_bit(&i, 1);
	printf("%u\n", i);
	toggle_bit(&i, 1);
	printf("%u\n", i);

	return 0;
}






























