#include "pdp.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>



int main(int argc, char * argv[]) {
	test_mem();
	
	if(argc == 1){
		printf("Usage: < executable file >  < input_file > \n");
		return 0;
	}
	else if (argc == 2){
		load_file(argv[1]);
	}
	
	run();
	
	return 0;
}


void load_file(char * f){
	FILE * fin  = fopen(f, "r");
	if (fin == NULL) {
        perror(f);
        exit(errno);
    }
	
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
		w = w_read(start + i, MEM);
		printf("%06o : %06o\n", start + i, w);
	}
}


