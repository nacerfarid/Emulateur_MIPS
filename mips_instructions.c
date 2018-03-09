/******** MIPS_INSTRUCTIONS.C ********/

#include "mips_instructions.h"
#include <inttypes.h>

int offset=4;

void initRegs(CPU_s* cpu){
int i = 0;
	for(i=0; i<32; i++){
		cpu->regs[i]=0;
	}
	for(i=0; i<512; i++){
		cpu->ram[i]=0;
	}
	cpu->pc = 0;
	cpu->hi = 0;
	cpu->lo = 0;
}

int add(CPU_s* cpu, int rd, int rs, int rt)
{
cpu->regs[rd] = cpu->regs[rs] + cpu->regs[rt];
cpu->pc++;
return 0;
}

int addi(CPU_s* cpu, int rd, int rs, int imm)
{
cpu->regs[rd] = cpu->regs[rs] + imm;
cpu->pc++;
return 0;
}

int sub(CPU_s* cpu, int rd, int rs, int rt)
{
cpu->regs[rd] = cpu->regs[rs] - cpu->regs[rt];
cpu->pc++;
return 0;
}

int slt(CPU_s* cpu, int rd, int rs, int rt)
{
	if ((cpu->regs[rs]) <= (cpu->regs[rt])){
		cpu->regs[rd] = 1;
	}
	else{
		cpu->regs[rd] = 0;
	}
cpu->pc++;
return 0;
}

int mult(CPU_s* cpu, int rs, int rt)
{
int64_t lotmp = 0;
int64_t hitmp = 0;
lotmp =(int64_t)((int64_t)cpu->regs[rs]*(int64_t)cpu->regs[rt]);
printf("resultat=%" PRId64 "\n", lotmp);
hitmp = lotmp;
lotmp &= 0x00000000FFFFFFFF;
hitmp = hitmp>>32;
cpu->lo = lotmp;
cpu->hi = hitmp;
cpu->pc++;
return 0;
}

float divp(CPU_s* cpu, int rs, int rt)
{
int64_t lotmp = 0;
int64_t hitmp = 0;
lotmp =(cpu->regs[rs]/cpu->regs[rt]);
hitmp =(cpu->regs[rs]%cpu->regs[rt]);
printf("partie entière=%" PRId64 "\n", lotmp);
printf("Reste=%" PRId64 "\n", hitmp);
lotmp &= 0x00000000FFFFFFFF;
hitmp = hitmp>>32;
cpu->lo = lotmp;
cpu->hi = hitmp;
cpu->pc++;
return 0;
}

int mfhi(CPU_s* cpu, int rd)
{
cpu->regs[rd]=cpu->hi;
cpu->pc++;
return 0;
}

int mflo(CPU_s* cpu, int rd)
{
cpu->regs[rd]=cpu->lo;
cpu->pc++;
return 0;
}

int srl(CPU_s* cpu, int rd, int rt, int h)
{
cpu->regs[rd]=(cpu->regs[rt]>>h);
cpu->pc++;
return 0;
}

int sll(CPU_s* cpu, int rd, int rt, int h)
{
cpu->regs[rd]=(cpu->regs[rt]<<h);
cpu->pc++;
return 0;
}

int andp(CPU_s* cpu, int rd, int rs, int rt)
{
cpu->regs[rd]=cpu->regs[rs]&cpu->regs[rt];
cpu->pc++;
return 0;
}

int orp(CPU_s* cpu, int rd, int rs, int rt)
{
cpu->regs[rd]=cpu->regs[rs]|cpu->regs[rt];
cpu->pc++;
return 0;
}

int xorp(CPU_s* cpu, int rd, int rs, int rt)
{
cpu->regs[rd]=cpu->regs[rs]^cpu->regs[rt];
cpu->pc++;
return 0;
}

int jr(CPU_s* cpu, int rs)
{
cpu->pc = cpu->regs[rs];
return 0;
}

int lw(CPU_s* cpu, int rt, int offset, int rs)
{
cpu->regs[rt]=cpu->ram[cpu->regs[rs]+offset];
cpu->pc++;
return 0;
}

int sw(CPU_s* cpu, int rt, int offset, int rs)
{
cpu->ram[cpu->regs[rs]+offset]=cpu->regs[rt];
cpu->pc++;
return 0;
}

int lui(CPU_s* cpu, int rt, int imm)
{
cpu->regs[rt]=(imm<<16);
cpu->pc++;
return 0;
}

int beq(CPU_s* cpu, int rs, int rt, int offset)
{
	if(cpu->regs[rs] == cpu->regs[rt]){
		cpu->pc = cpu->pc + offset;
	}
	else{
		cpu->pc++;
	}
return 0;
}

int bne(CPU_s* cpu, int rs, int rt, int offset)
{
	if(cpu->regs[rs] != cpu->regs[rt]){
		cpu->pc = cpu->pc + offset;
	}
	else{
		cpu->pc++;
	}
return 0;
}

int bgtz(CPU_s* cpu, int rs, int offset)
{
	if(cpu->regs[rs] > 0){
		cpu->pc = cpu->pc + offset;
	}
	else{
		cpu->pc++;
	}
return 0;
}

int blez(CPU_s* cpu, int rs, int offset)
{
	if(cpu->regs[rs] <= 0){
		cpu->pc = cpu->pc + offset;
	}
	else{
		cpu->pc++;
	}
return 0;
}

int jp(CPU_s* cpu, int offset)
{
cpu->pc += offset;
return 0;
}

int jal(CPU_s* cpu, int offset)
{
cpu->regs[31] = cpu->pc+1;
cpu->pc += offset;
return 0;
}

int getReg(CPU_s* cpu, int index)
{
return cpu->regs[index];
}

void setReg(CPU_s* cpu, int reg, int value)
{
cpu->regs[reg] = value;
}

int getHi(CPU_s* cpu)
{
return cpu->hi;
}

int getLo(CPU_s* cpu)
{
return cpu->lo;
}

