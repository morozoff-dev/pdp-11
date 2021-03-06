#include "pdp.h"
#include <stdio.h>
#include <assert.h>



void test_mem(){
	byte b0 = 0x0a;
	// пишем байт, читаем байт
	b_write(2, b0, MEM);
	byte bres = b_read(2, MEM);
	//printf("\t\t %02hhx = %02hhx\n", b0, bres);
	assert(b0 == bres);
	
	// пишем два байта, читаем одно слово
	adr a = 4;
	byte b1 = 0xcb;
	b0 = 0x0a;
	word w = 0xcb0a;
	b_write(a, b0, MEM);
	b_write(a + 1, b1, MEM);
	word wres = w_read(a, MEM);
	//printf("2b_w/w_r \t %04hx = %02hhx%02hhx\n", wres, b1, b0);
	assert(wres == w);
	
	// пишу слово, читаю слово
	a = 4;
	word w0 = 0xabba;
	w_write(a, w0, MEM);
	wres = w_read(a, MEM);
	//printf("\t\t %04hx = %04hx\n", wres, w0);
	assert(wres == w0);
	
	// пишу слово, читаю два байта
	a = 4;
	b0 = 0x0a;
	b1 = 0xcb;
	w = 0xcb0a;
	w_write(a, w, MEM);
	byte b0_res = b_read(a, MEM);
	byte b1_res = b_read(a + 1, MEM);
	//printf("w_w/2b_r \t %02hhx = %02hhx, %02hhx = %02hhx\n", b0, b0_res, b1, b1_res);
	assert(b0 == b0_res);
	assert(b1 == b1_res);
	
}
