#include "hw_helper.h"

static uint32_t reg = 0;

uint32_t __get_R0(void)
{
	__ASM volatile ("mov %0, R0" : "=r" (reg) );
	return reg;
}

uint32_t __get_R1(void)
{
	__ASM volatile ("mov %0, R1" : "=r" (reg) );
	return reg;
}

uint32_t __get_R2(void)
{
	__ASM volatile ("mov %0, R2" : "=r" (reg) );
	return reg;
}

uint32_t __get_R3(void)
{
	__ASM volatile ("mov %0, R3" : "=r" (reg) );
	return reg;
}

uint32_t __get_R4(void)
{
	__ASM volatile ("mov %0, R4" : "=r" (reg) );
	return reg;
}

uint32_t __get_R5(void)
{
	__ASM volatile ("mov %0, R5" : "=r" (reg) );
	return reg;
}

uint32_t __get_R6(void)
{
	__ASM volatile ("mov %0, R6" : "=r" (reg) );
	return reg;
}

uint32_t __get_R7(void)
{
	__ASM volatile ("mov %0, R7" : "=r" (reg) );
	return reg;
}

uint32_t __get_R8(void)
{
	__ASM volatile ("mov %0, R8" : "=r" (reg) );
	return reg;
}

uint32_t __get_R9(void)
{
	__ASM volatile ("mov %0, R9" : "=r" (reg) );
	return reg;
}

uint32_t __get_R10(void)
{
	__ASM volatile ("mov %0, R10" : "=r" (reg) );
	return reg;
}

uint32_t __get_R11(void)
{
	__ASM volatile ("mov %0, R11" : "=r" (reg) );
	return reg;
}

uint32_t __get_R12(void)
{
	__ASM volatile ("mov %0, R12" : "=r" (reg) );
	return reg;
}

