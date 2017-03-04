#include <stdio.h>
// typedef void printbytes(int n, unsigned char *b);
// typedef void printregister(unsigned char r);

void printbytes(int n, const unsigned char *b){
	for (int i = 0; i < n; ++i){
		printf("%.2x ", b[i]);
	}
	printf("\t");
}

void printregister(unsigned char r){
	if (r == 0x0){
		printf("%%rax");
	}else if(r == 0x1){
		printf("%%rcx");
	}else if(r == 0x2){
		printf("%%rdx");
	}else if(r == 0x3){
		printf("%%rbx");
	}else if(r == 0x4){
		printf("%%rsp");
	}else if(r == 0x5){
		printf("%%rbp");
	}else if(r == 0x6){
		printf("%%rsi");
	}else if(r == 0x7){
		printf("%%rdi");
	}
}

void printscale(unsigned char s){
	if (s == 0x0){
		printf("1");
	}else if(s == 0x01){
		printf("2");
	}else if(s == 0x2){
		printf("4");
	}else if(s == 0x3){
		printf("8");
	}
}

void disassemble(const unsigned char *raw_instr){
	
	// printf("%x\n", (raw_instr[0] >> 3));
	if (raw_instr[0] == 0x68){//1
		printbytes(5, raw_instr);
		printf("pushq $0x");
		for (int i = 4; i > 0; --i){
			if (raw_instr[i] > 0){
				printf("%x", raw_instr[i]);
			}
		}
		printf("\n");
	}
	else if(raw_instr[0] == 0xff){ //3 4 5
		// printf("%x\n", raw_instr[1] >> 6);
		if (raw_instr[1] >> 3 == 0x06){ //3
			unsigned char regis = raw_instr[1] & 0x03;
			printbytes(2,raw_instr);
			printf("pushq ");
			printf("(");
			printregister(regis);
			printf(")\n");
		}else if((raw_instr[1] >> 3 == 0x0e) && ((raw_instr[1]&0x07) >= 0x00) 
		&& ((raw_instr[1]&0x07) < 0x08) && ((raw_instr[1]&0x07) != 0x04)){ //4
			unsigned char regis = (raw_instr[1] & 0x03);
			printbytes(3,raw_instr);
			printf("pushq $0x");
			printf("%x", (int) (raw_instr[2]));
			printf("(");
			printregister(regis);
			printf(")\n");
		}else if(raw_instr[1] == 0x74){ //5
			unsigned char right_regis = (raw_instr[2] & 0x38) >> 3;
			unsigned char left_regis = raw_instr[2] & 0x07;
			unsigned char scale = (raw_instr[2] >> 6) & 0x03;
			// printf("%x %x %x\n", left_regis, right_regis, scale);
			printbytes(4,raw_instr);
			printf("pushq $0x");
			printf("%x", raw_instr[3]);
			printf("(");
			printregister(left_regis);
			printf(",");
			printregister(right_regis);
			printf(",");
			printscale(scale);
			printf(")\n");
		}
	}else if(((raw_instr[0] >> 3)&0x1f) == 0xa){ //2
		unsigned char regis = (raw_instr[0]) & 0x07;
		// printf("%x\n", raw_instr[1]);
		printbytes(1,raw_instr);
		printf("pushq ");
		printregister(regis);
		printf("\n");
	}


}
