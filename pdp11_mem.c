#include <stdio.h>
#include <assert.h>


typedef  unsigned char  byte;    // 8 bit
typedef  unsigned short int word;    // 16 bit
typedef   word adr;  // 16 bit


#define ABC

#define MEMSIZE (64*1024)


byte mem[MEMSIZE];

void b_write(adr a, byte b);
byte b_read(adr a);
void w_write(adr a, word w);
word w_read(adr a);


#ifdef ABC

void test_mem(){
	byte b0 = 0x0a;
	// пишем байт, читаем байт
	b_write(2, b0);
	byte bres = b_read(2);
	//printf("\t\t %02hhx = %02hhx\n", b0, bres);
	assert(b0 == bres);
	
	// пишем два байта, читаем одно слово
	adr a = 4;
	byte b1 = 0xcb;
	b0 = 0x0a;
	word w = 0xcb0a;
	b_write(a, b0);
	b_write(a + 1, b1);
	word wres = w_read(a);
	//printf("2b_w/w_r \t %04hx = %02hhx%02hhx\n", wres, b1, b0);
	assert(wres == w);
	
	// пишу слово, читаю слово
	adr a = 4;
	word w0 = 0xabba;
	w_write(a, w0);
	wres = w_read(a);
	//printf("\t\t %04hx = %04hx\n", wres, w0);
	assert(wres == w0);
	
	// пишу слово, читаю два байта
	a = 4;
	b0 = 0x0a;
	b1 = 0xcb;
	w = 0xcb0a;
	w_write(a, w);
	byte b0_res = b_read(a);
	byte b1_res = b_read(a + 1);
	//printf("w_w/2b_r \t %02hhx = %02hhx, %02hhx = %02hhx\n", b0, b0_res, b1, b1_res);
	assert(b0 == b0_res);
	assert(b1 == b1_res);
}





int main() {
	test_mem();
	
	
	return 0;
}

#endif


void w_write(adr a, word w){
	assert(a % 2 == 0);
	mem[a] = (byte)((w << 8) >> 8);
	mem[a + 1] = (byte)(w >> 8);
}


word w_read(adr a){
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

