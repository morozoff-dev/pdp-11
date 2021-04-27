#include "pdp.h"
#include <stdio.h>
#include <stdlib.h>


extern Command cmd[];

Arg ss, dd;
int nn, r, xx;   // params
int bw;      // работаем с байтом или словом

Arg get_mr(word w){
	Arg res;
	int r = w & 7;
	int mode = (w >> 3) & 7;
	word sdv;   // для 6й моды
	
	if(mode == 0) {
		res.where = REG;
	}
	else {
		res.where = MEM;
	}
	
	switch(mode) {
		case 0:   // R3
			res.adr = r;
			res.val = reg[r];
			logg(Trace, "R%o ", r);
			break;
			
		case 1:   // (R3)
			res.adr = reg[r];
			
			if(bw == B)
				res.val = b_read(res.adr, res.where);
			
			else 
				res.val = w_read(res.adr, res.where);
			
			
			logg(Trace, "(R%o) ", r);
			break;
			
		case 2:   // (R3)+     #3
			res.adr = reg[r];
			
			if(bw == B){
				res.val = b_read(res.adr, res.where);
				reg[r] += r < 6 ? 1 : 2;
			}
			else {
				res.val = w_read(res.adr, res.where);
				reg[r] += 2;
			}
			
			if(r == 7){
				logg(Trace, "#%o ", res.val);
			}
			else {
				logg(Trace, "(R%o)+ ", r);
			}
			break;
			
		case 3:
			res.adr = w_read(reg[r], res.where);
			
			if(bw == B) 
				res.val = b_read(res.adr, res.where);
			else
				res.val = w_read(res.adr, res.where);
			
			reg[r] += 2;
			if(r == 7) {
				logg(Trace, "@#%o ", res.adr);
			}
			else {
				logg(Trace, "@(R%o)+ ", r);
			}
			break;
			
		case 4: 
			if(bw == B) {
				reg[r] -= r < 6 ? 1 : 2;
				res.adr = reg[r];
				res.val = b_read(res.adr, res.where);
			}
			else {
				reg[r] -= 2;
				res.adr = reg[r];
				res.val = w_read(res.adr, res.where);
			}
			logg(Trace, "-(R%d) ", r);
			break;
			
		case 6: 
			sdv = w_read(pc, res.where);
			pc += 2;
			res.adr = reg[r] + sdv;
			if(bw == B)
				res.val = b_read(res.adr, res.where);
			else 
				res.val = w_read(res.adr, res.where);
			
			if(r == 7)
				logg(Trace, "%o ", res.adr);
			else 
				logg(Trace, "%o(R%o)", sdv, r);
				
			break;
			
		default: 
			fprintf(stderr, "Mode %o NOT IMPLEMENTED YET!\n", mode);
			exit(1);
		
	}
	
	return res;
}



int get_r(word w){
	int res;
    res = (w >> 6) & 7;
	logg(Trace, "R%d ", res);
	return res;
	
}

int get_nn(word w){
	int res;
	res = w & 0000077;
	logg(Trace, "%06o ", pc - res * 2);
	return res;
}


int get_xx(word w){
	int res;
	res = (byte)(w & 0377);
	if((res >> 7) & 1){
		res = res - 000400;
	}
	logg(Trace, "%06o ", pc + res * 2);
	
	return res;
}


void run(){
	mem[ostat] = mem[ostat] | 128;    // устройство всегда готово 
	pc = 01000;
	int i;
	while(1){
		word w = w_read(pc, MEM);
		logg(Trace, "%06o %06o: ", pc, w);
		pc += 2;
		 
		for(i = 0; ; i++) {
			
			if((w & cmd[i].mask) == cmd[i].opcode){
				logg(Trace, "%s ", cmd[i].name);
				if(cmd[i].params & HAS_BW){
				bw = w >> 15;
				}
				if(cmd[i].params & HAS_R){
					r = get_r(w);
				}
				if(cmd[i].params & HAS_SS){
					ss = get_mr(w >> 6);
				}
				if(cmd[i].params & HAS_DD){
					dd = get_mr(w);
				}
				if(cmd[i].params & HAS_NN){
					nn = get_nn(w);
				}
				if(cmd[i].params & HAS_XX){
					xx = get_xx(w);
				}
				
				cmd[i].do_func();
				logg(Trace, "\n");
				break;
			}
		
		
		}
		
		if(pc < 8) {
			logg(Error, "Error: system memory has changed \n");
			exit(1);
		}
		
	}
	
}
