/******** MIPS_INSTRUCTIONS.H ********/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct{
	int ram[512];
	int regs[32];
	int pc;
	int hi;
	int lo;
} CPU_s;


/******** GLOBALS ********/
/*int regs[32];
int pc;
int hi;
int lo;*/

/******** FUNCTIONS ********/
int add(CPU_s* cpu, int rd, int rs, int rt);
int sub(CPU_s* cpu, int rd, int rs, int rt);
int slt(CPU_s* cpu, int rd, int rs, int rt);
int addi(CPU_s* cpu, int rd, int rs, int imm);
float divp(CPU_s* cpu, int rs, int rt);
int mult(CPU_s* cpu, int rs, int rt);
int mfhi(CPU_s* cpu, int rd);
int mflo(CPU_s* cpu, int rd);
int srl(CPU_s* cpu, int rd, int rt, int h);
int sll(CPU_s* cpu, int rd, int rt, int h);
int andp(CPU_s* cpu, int rd, int rs, int rt);
int orp(CPU_s* cpu, int rd, int rs, int rt);
int xorp(CPU_s* cpu, int rd, int rs, int rt);
int jr(CPU_s* cpu, int rs);
int lw(CPU_s* cpu, int rt, int offset, int rs);
int sw(CPU_s* cpu, int rt, int offset, int rs);
int lui(CPU_s* cpu, int rt, int imm);
int beq(CPU_s* cpu, int rs, int rt, int offset);
int bne(CPU_s* cpu, int rs, int rt, int offset);
int bgtz(CPU_s* cpu, int rs, int offset);
int blez(CPU_s* cpu, int rs, int offset);
int jp(CPU_s* cpu, int offset);
int jal(CPU_s* cpu, int offset);

void initRegs(CPU_s* cpu);
int getReg(CPU_s* cpu, int index);
void setReg(CPU_s* cpu, int reg, int value);
int getHi(CPU_s* cpu);
int getLo(CPU_s* cpu);

