#include "pdp.h"
#include <stdio.h>
#include <stdlib.h>


extern Command cmd[];

Arg ss, dd;
int NN, R, XX;
int BW = W;     // байт или слово

Arg get_mr(word w){
	Arg res;
	int r = w & 7;
	int mode = (w >> 3) & 7;
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
			printf("R%o ", r);
			break;
		case 1:   // (R3)
			res.adr = reg[r];
			
			if(BW == B){
				res.val = b_read(res.adr, res.where);
			}
			else {
			res.val = w_read(res.adr, res.where);
			}
			
			printf("(R%o) ", r);
			
			break;
			
		case 2:   // (R3)+     #3
			res.adr = reg[r];
			
			if(BW == B){
				res.val = b_read(res.adr, res.where);
				if(r < 6) reg[r] += 1;
				else reg[r] += 2;
			}
			else {
			res.val = w_read(res.adr, res.where);
			reg[r] += 2;
			}
			
			if(r == 7){
				printf("#%o ", res.val);
			}
			else {
				printf("(R%o)+ ", r);
			}
			break;
		case 3:
			res.adr = w_read(reg[r], res.where);
			
			if(BW == B) res.val = b_read(res.adr, res.where);
			else res.val = w_read(res.adr, res.where);
			
			reg[r] += 2;
			if(r == 7) {
				printf("@#%o ", res.adr);
			}
			else {
				printf("@(R%o)+ ", r);
			}

			break;
		default: 
			fprintf(stderr, "Mode %o NOT IMPLEMENTED YET!\n", mode);
			exit(1);
		
	}
	
	return res;
}



int get_R(word w){
	int res;
    res = (w >> 6) & 7;
	printf("R%d ", res);
	return res;
	
}

int get_NN(word w){
	int res;
	res = w & 0000077;
	printf("%06o ", pc - res * 2);
	return res;
}


int get_XX(word w){
	int res;
	res = (byte)(w & 0377);
	if((res >> 7) & 1){
		res = res - 000400;
	}
	printf("%06o ", pc + res * 2);
	
	return res;
}


void run(){
	pc = 01000;
	int i;
	while(1){
		word w = w_read(pc, MEM);
		printf("%06o %06o: ", pc, w);
		pc += 2;
		 
		for(i = 0; ; i++) {
			
			if((w & cmd[i].mask) == cmd[i].opcode){
				printf("%s ", cmd[i].name);
				if(cmd[i].params & HAS_BW){
				BW = w >> 15;
				}
				if(cmd[i].params & HAS_SS){
					ss = get_mr(w >> 6);
				}
				if(cmd[i].params & HAS_DD){
					dd = get_mr(w);
				}
				if(cmd[i].params & HAS_R){
					R = get_R(w);
				}
				if(cmd[i].params & HAS_NN){
					NN = get_NN(w);
				}
				if(cmd[i].params & HAS_XX){
					XX = get_XX(w);
				}
				
				cmd[i].do_func();
				printf("\n");
				break;
			}
		
		
		}
		
	}
	
}
