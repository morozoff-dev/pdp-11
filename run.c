#include "pdp.h"
#include <stdio.h>

#define com_num 3

typedef struct {
	word mask;
	word opcode;
	char * name;
	void (*do_func)(void);
	
} Command;

Command cmd[] = {
	{0170000, 0010000, "mov", do_mov},
	{0170000, 0060000, "add", do_add},
	{0170000, 0000000, "halt", do_halt}
	
};

void run(){
	pc = 01000;
	int i;
	while(1){
		word w = w_read(pc);
		printf("%06o %06o: ", pc, w);
		pc += 2;
		for(i = 0; i < com_num; i++){
			if((w & cmd[i].mask) == cmd[i].opcode){
				puts(cmd[i].name);
				cmd[i].do_func();
			}
			else if (i == 2){
				printf("unknown\n");
			}
		}
		
	}
	
}
