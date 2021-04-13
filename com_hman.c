#include "pdp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



Command cmd[] = {
	{0170000, 0010000, "mov", do_mov, HAS_DD | HAS_SS},
	{0170000, 0060000, "add", do_add, HAS_DD | HAS_SS},
	{0177777, 0000000, "halt", do_halt, NO_PARAMS},
	{0177000, 0077000, "sob", do_sob,  HAS_R | HAS_NN},
	{0077700, 0005000, "clr", do_clr, HAS_DD},
	{0000000, 0000000, "unknown", do_nothing, NO_PARAMS}
	
};


void do_halt(){
	printf("THE END!!!\n");
	reg_print();
	exit(0);
}


void do_mov(){
	w_write(dd.adr, ss.val, dd.where);

}
 
 
void do_add(){
	w_write(dd.adr, (dd.val + ss.val) & 0xFFFF, dd.where);

}


void do_nothing(){
	
}


void do_sob(){
	reg[R] = reg[R] - 1;
	if (reg[R] != 0){
		pc = pc - NN * 2;
	}
	
}

void do_clr(){
		w_write(dd.adr, 0, dd.where);
		
}




void reg_print(){
	int i;
	printf("Registers: \n");
	for(i = 0; i < 8; i++){
		printf("%o \n", reg[i]);
	}
	
}

