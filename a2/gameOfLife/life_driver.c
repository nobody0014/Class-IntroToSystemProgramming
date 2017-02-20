#include<stdio.h>
#include<stdlib.h>
#include"life_engine.h"

int main(int argc, char *argv[])
{
  life_board b0, b1;
  life_board *rb[2] = { &b0, &b1 };
  int count = 10;
	if (argc>1) {
		read_board_from_file(argv[1], &b0);
		if (argc==3) count=atoi(argv[2]);
		b1.num_cols = b0.num_cols;
		b1.num_rows = b0.num_rows;
		b1.cells = (unsigned char*) malloc(b0.num_cols*b0.num_rows*sizeof(unsigned char));
		int this=0;
		for (int round=0;round<count;++round,this=!this) {
			make_next_board(*rb[this], *rb[!this]);
		}
		print_board(*rb[this]);
	} else {
		printf("use: %s start.file [num_iterations]\n", argv[0]);
		return 1;
	}
	return 0;
}
