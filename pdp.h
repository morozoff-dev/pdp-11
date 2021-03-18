
typedef  unsigned char  byte;    // 8 bit
typedef  unsigned short int word;    // 16 bit
typedef   word adr;  // 16 bit

#define MEMSIZE (64*1024)
#define pc reg[7]


extern byte mem[MEMSIZE];
extern word reg[8];

void b_write(adr a, byte b);
byte b_read(adr a);
void w_write(adr a, word w);
word w_read(adr a);

void test_mem();

void load_file();
void mem_dump(adr start, word n);

void do_halt();
void do_mov();
void do_add();
void do_nothing();
void run();
