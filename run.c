#include "pdp.h"
#include <stdio.h>
#include <stdlib.h>


#define NO_PARAMS 0
#define HAS_DD 1
#define HAS_SS 2



Command cmd[] = {
	{0170000, 0010000, "mov", do_mov, HAS_DD | HAS_SS},
	{0170000, 0060000, "add", do_add, HAS_DD | HAS_SS},
	{0177777, 0000000, "halt", do_halt, NO_PARAMS},
	{0000000, 0000000, "unknown", do_nothing, NO_PARAMS}
	
};

Arg ss, dd;


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
			res.val = w_read(res.adr);
			printf("(R%o) ", r);
			
			break;
			
		case 2:   // (R3)+     #3
			res.adr = reg[r];
			res.val = w_read(res.adr);
			reg[r] += 2;
			if(r == 7){
				printf("#%o ", res.val);
			}
			else {
				printf("(R%o)+ ", r);
			}

			break;
		default: 
			fprintf(stderr, "Mode %o NOT IMPLEMENTED YET!\n", mode);
			exit(1);
		
	}
	
	return res;
}




void run(){
	pc = 01000;
	int i;
	while(1){
		word w = w_read(pc);
		printf("%06o %06o: ", pc, w);
		pc += 2;
		 
		for(i = 0; ; i++) {
			
			if((w & cmd[i].mask) == cmd[i].opcode){
				printf("%s ", cmd[i].name);
				if(cmd[i].params & HAS_SS == HAS_SS){
					ss = get_mr(w >> 6);
				}
				if(cmd[i].params & HAS_DD == HAS_DD){
					dd = get_mr(w);
				}
				cmd[i].do_func();
				printf("\n");
				break;
			}
		
		
		}
		
	}
	
}
