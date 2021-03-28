#include "pdp.h"
#include <stdio.h>
#include <stdlib.h>


void do_halt(){
	printf("THE END!!!\n");
	reg_print();
	exit(0);
}

void do_mov(){
	w_write(dd.adr, ss.val);
}

void do_add(){
	
}
void do_nothing(){
	
}

void reg_print(){
	int i;
	for(i = 0; i < 8; i++){
		printf("%o \n", reg[i]);
	}
	
}

