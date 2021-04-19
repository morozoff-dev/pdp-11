
#pragma once

typedef  unsigned char  byte;    // 8 bit
typedef  unsigned short int word;    // 16 bit
typedef   word adr;  // 16 bit


typedef struct {
	word mask;
	word opcode;
	char * name;
	void (*do_func)(void);
	char params;
	
} Command;


typedef struct{
	word val;  // значение аргумента 
	word adr;  // адрес аргумента
	int where; // куда писать: в reg или mem
	
} Arg;

#define MEMSIZE (64*1024)
#define pc reg[7]

#define REG 0
#define MEM 1

#define NO_PARAMS 0
#define HAS_DD 1
#define HAS_SS 2
#define HAS_NN 4
#define HAS_R  8
#define HAS_BW 16

#define B 1
#define W 0


extern byte mem[MEMSIZE];
extern word reg[8];

extern Arg ss, dd;
extern int NN, R;

void w_write(adr a, word w, int where);
word w_read(adr a, int where);
void b_write(adr a, byte b, int where);
byte b_read(adr a, int where);

void test_mem();

void load_file();
void mem_dump(adr start, word n);

void do_halt();
void do_mov();
void do_add();
void do_nothing();
void do_sob();
void do_clr();
void run();

void reg_print();
