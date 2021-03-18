#include "pdp.h"
#include <stdio.h>
#include <stdlib.h>


byte mem[MEMSIZE];
word reg[8];



int main() {
	test_mem();
	word w = 0000000;
	w_write(01000, w);
	run();
	
	return 0;
}


void load_file(){
	adr a;
	int n, i;
	while(feof(stdin) != 1){
		fscanf(stdin, "%hx", &a);
		fscanf(stdin, "%x", &n);
		for(i = 0; i < n; i++){
			fscanf(stdin, "%hhx", &mem[a + i]);
		}
	}

}


void mem_dump(adr start, word n){
	word w;
	for(int i = 0; i < n; i += 2){
		w = w_read(start + i);
		printf("%06o : %06o\n", start + i, w);
	}
}


