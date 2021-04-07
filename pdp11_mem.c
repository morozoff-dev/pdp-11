#include "pdp.h"
#include <stdio.h>
#include <stdlib.h>


byte mem[MEMSIZE];
word reg[8];



int main(int argc, char * argv[]) {
	test_mem();
	
	load_file(argv[1]);
	run();
	
	return 0;
}


void load_file(char * f){
	FILE * fin  = fopen(f, "r");
	adr a;
	int n, i;
	while(feof(fin) != 1){
		fscanf(fin, "%hx", &a);
		fscanf(fin, "%x", &n);
		for(i = 0; i < n; i++){
			fscanf(fin, "%hhx", &mem[a + i]);
		}
	}
	fclose(fin);

}


void mem_dump(adr start, word n){
	word w;
	for(int i = 0; i < n; i += 2){
		w = w_read(start + i);
		printf("%06o : %06o\n", start + i, w);
	}
}


