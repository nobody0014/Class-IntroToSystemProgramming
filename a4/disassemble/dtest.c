#include <stdio.h>
#include "disas.h"

int main(){
	unsigned char imc[5] = {0x68, 0x10, 0x3f, 0x00, 0x00};
	disassemble(imc);
	unsigned char reg[1] = {0x53};
	disassemble(reg);
	unsigned char idr[2] = {0xff, 0x32};
	disassemble(idr);
	unsigned char dsp[3] = {0xff, 0x70, 0x08};
	disassemble(dsp);
	unsigned char dsi[4] = {0xff, 0x74, 0x8d, 0xff};
	disassemble(dsi);
 

	return 0;
}

