#include "pdp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int BW;

int flag_N;
int flag_Z;
int flag_C;



Command cmd[] = {
	{0070000, 0010000, "mov", do_mov, HAS_DD | HAS_SS | HAS_BW},
	{0170000, 0060000, "add", do_add, HAS_DD | HAS_SS},
	{0177777, 0000000, "halt", do_halt, NO_PARAMS},
	{0177000, 0077000, "sob", do_sob,  HAS_R | HAS_NN},
	{0077700, 0005000, "clr", do_clr, HAS_DD | HAS_BW},
	{0000000, 0000000, "unknown", do_nothing, NO_PARAMS}
	
};


void do_halt(){
	printf("THE END!!!\n");
	reg_print();
	exit(0);
}


void do_mov(){
	if(BW == B){
		int zn = (ss.val >> 7);
		if((dd.where == REG) && (zn == 1)) w_write(dd.adr, ss.val | 0xFF00, dd.where);
		else b_write(dd.adr, ss.val, dd.where);
	}
	else {
	w_write(dd.adr, ss.val, dd.where);
	}

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
		if(BW == B) {
			b_write(dd.adr, 0, dd.where);
		}
		else {
		w_write(dd.adr, 0, dd.where);
		
		}
		
}


void reg_print(){
	int i;
	printf("Registers: \n");
	for(i = 0; i < 8; i++){
		printf("%o \n", reg[i]);
	}
	
}



void set_NZ(word w){
	if(w == 0) {
		flag_Z = 1;
	}
	else {
		flag_Z = 0;
	}
	
	if(BW == B) {
		flag_N = (w >> 7) & 1;
	}
	else {
		flag_N = (w >> 15) & 1;
	}
	
}

