#include "pdp.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>


int options;


int main(int argc, char * argv[]) {
	test_mem();
	
	if(argc == 1){
		printf("Usage: < executable file >  < input_file > [-t] \n");
		return 0;
	}
	else if (argc > 1){
		load_file(argv[1]);
	}
	
	
	char * opts = "t"; 
	int opt; 
	 while((opt = getopt(argc, argv, opts)) != -1) { 
        switch(opt) {
            case 't': 
                options = options | Trace;
                break; 			
        }						//  возможно попозже добавлю больше опций
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


void logg(int curr_opt, const char * fmt, ...) {
	if(!(options & curr_opt))
		return;
	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	
}

