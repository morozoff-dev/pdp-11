#include "pdp.h"
#include <stdio.h>
#include <stdlib.h>


extern word w;



void do_halt(){
	printf("THE END!!!\n");
	reg_print();
	exit(0);
}

void do_mov(){
	reg[dd.adr] = ss.val;
}
 
void do_add(){
	if((w >> 3) & 7 == 0){
		reg[dd.adr] = dd.val + ss.val;
	}
	else {
	w_write(dd.adr, dd.val + ss.val);
	}
}

void do_nothing(){
	
}


void reg_print(){
	int i;
	printf("Registers: \n");
	for(i = 0; i < 8; i++){
		printf("%o \n", reg[i]);
	}
	
}

