#include "pdp.h"
#include <stdio.h>
#include <assert.h>

byte mem[MEMSIZE];
word reg[8];



void w_write(adr a, word w, int where){
	if(where == MEM){
	assert(a % 2 == 0);
	mem[a] = (byte)w;
	mem[a + 1] = (byte)(w >> 8);    // w only unsigned
	}
	else {
		reg[a] = w;
	}
}


word w_read(adr a, int where){
	if(where == MEM){
	assert(a % 2 == 0);
	word w = ((word)mem[a + 1]) << 8; 
	w = w | mem[a];
	return w;
	}
	else {
		return reg[a];
	}
	
}


void b_write(adr a, byte b, int where){
	if(where == MEM){
	mem[a] = b;
	}
	else {
		reg[a] = b;
	}
	
}


byte b_read(adr a, int where){
	if(where == MEM){
	return mem[a];
	}
	else {
		return (byte)reg[a];
	}
}
