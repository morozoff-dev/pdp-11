#include "pdp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 65536

void do_halt(){
	printf("THE END!!!\n");
	reg_print();
	exit(0);
}

void do_mov(){
	if(strcmp(dd.where, "reg") == 0){
	reg[dd.adr] = ss.val;
	} 
	else {
		w_write(dd.adr, ss.val);
	}
}
 
void do_add(){
	if(strcmp(dd.where, "reg") == 0){
		reg[dd.adr] = (dd.val + ss.val) % MOD;
	}
	else {
	w_write(dd.adr, (dd.val + ss.val)% MOD);
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

