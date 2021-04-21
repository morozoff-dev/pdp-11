#include "pdp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int flag_N;
int flag_Z;
int flag_C;
int flag_V;



Command cmd[] = {
	{0070000, 0010000, "MOV", do_mov, HAS_DD | HAS_SS | HAS_BW},
	{0170000, 0060000, "ADD", do_add, HAS_DD | HAS_SS},
	{0177777, 0000000, "HALT", do_halt, NO_PARAMS},
	{0177000, 0077000, "SOB", do_sob,  HAS_R | HAS_NN},
	{0077700, 0005000, "CLR", do_clr, HAS_DD | HAS_BW},
	
	{0177777, 0000277, "SCC", do_scc, NO_PARAMS},
	{0177777, 0000261, "SEC", do_sec, NO_PARAMS},
	{0177777, 0000270, "SEN", do_sen, NO_PARAMS},
	{0177777, 0000264, "SEZ", do_sez, NO_PARAMS},
	{0177777, 0000262, "SEV", do_sev, NO_PARAMS},
	
	{0177777, 0000257, "CCC", do_ccc, NO_PARAMS},
	{0177777, 0000241, "CLC", do_clc, NO_PARAMS},
	{0177777, 0000250, "CLN", do_cln, NO_PARAMS},
	{0177777, 0000244, "CLZ", do_clz, NO_PARAMS},
	{0177777, 0000242, "CLV", do_clv, NO_PARAMS},
	
	{0177777, 0000240, "NOP", do_nop, NO_PARAMS},
	
	{0177400, 0000400, "BR",  do_br,  HAS_XX},
	{0177400, 0001400, "BEQ", do_beq, HAS_XX},
	
	{0000000, 0000000, "UNKNOWN", do_nothing, NO_PARAMS}
	
};


void do_halt(){
	printf("THE END!!!\n");
	reg_print();
	exit(0);
}


void do_mov(){
	if(bw == B){
		int zn = (ss.val >> 7); 
		if((dd.where == REG) && (zn == 1)) w_write(dd.adr, ss.val | 0xFF00, dd.where);
		else b_write(dd.adr, ss.val, dd.where);
	}
	else {
	w_write(dd.adr, ss.val, dd.where);
	}
	
    set_NZ(ss.val);
	do_clv();
}
 
 
void do_add(){
	w_write(dd.adr, (dd.val + ss.val) & 0xFFFF, dd.where);
	
	set_NZ(dd.val + ss.val);
}


void do_nothing(){
	
}


void do_sob(){
	reg[r] = reg[r] - 1;
	if (reg[r] != 0){
		pc = pc - nn * 2;
	}
	
}

void do_clr(){
	if(bw == B) {
		b_write(dd.adr, 0, dd.where);
	}
	else {
		w_write(dd.adr, 0, dd.where);	
	}
	
	do_cln();	
	do_sez();
	do_clv();
	do_clc();
}

void do_br() {
	pc = pc + 2*xx;
	
}

void do_beq() {
	if(flag_Z){
		do_br();
	}
	
}



void do_scc() {
	flag_N = flag_Z = flag_C = flag_V = 1;
	
}

void do_sec() {
	flag_C = 1;
	
}

void do_sen() {
	flag_N = 1;
	
}

void do_sez() {
	flag_Z = 1;
	
}

void do_sev() {
	flag_V = 1;
	
}


void do_ccc() {
	flag_N = flag_Z = flag_C = flag_V = 0;
		
}

void do_clc() {
    flag_C = 0;
		
}

void do_cln() {
    flag_N = 0;
		
}

void do_clz() {
    flag_Z = 0;
		
}

void do_clv() {
    flag_V = 0;
		
}


void do_nop() {
	
}



void reg_print(){
	int i;
	printf("Registers: \n");
	for(i = 0; i < 8; i++){
		printf("%o \n", reg[i]);
	}
	
}



void set_NZ(word w){
	flag_Z = (w == 0);
	flag_N = (w >> (bw == B ? 7 : 15)) & 1;
	
}
