#include "pdp.h"
#include <stdio.h>
#include <assert.h>



void w_write(adr a, word w){
	assert(a % 2 == 0);
	mem[a] = (byte)w;
	mem[a + 1] = (byte)(w >> 8);    // w only unsigned
}


word w_read(adr a){
	assert(a % 2 == 0);
	word w = ((word)mem[a + 1]) << 8; 
	w = w | mem[a];
	return w;
	
}


void b_write(adr a, byte b){
	mem[a] = b;
	
}

byte b_read(adr a){
	return mem[a];
}
