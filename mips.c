/*#include "mips_instructions.h"*/
#include "mips_decoding.h"
#include <libgen.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
CPU_s cpu;
int val = 0;
int reg = 0;
char fic[32];
char inst[512][32];
char RegNum[32];
char commande[32];
int nbInstr = 0;
int instruction=0;
int i =0;
int choix;

/*printf("size of short: %i\n", sizeof(short));*/
initRegs(&cpu);
if(argc>1){
	if(strcmp(argv[1], "-f")==0)
	{	
		strcpy(fic, argv[2]);
		nbInstr = decodeFile(fic, inst);
		for(i=0; i<nbInstr; i++){
			instruction = encodeInstr(inst[i]);
			if(instruction !=0){
				printf("Instruction:.............. %s\n", inst[i]);
				printf("Instruction Code:......... 0x%X\n\n", instruction);
				cpu.ram[i] = instruction;
			}
			else{
				printf("Error is line %i\n\n", i+1);
			}
		}
		while(cpu.ram[cpu.pc]!=0){
			decodeInstr(&cpu, cpu.ram[cpu.pc]);
		}
		argv[1][0]='-';
		argv[1][1]='i';
	}
	if(strcmp(argv[1], "-p") == 0)
	{	
		strcpy(fic, argv[2]);
		nbInstr = decodeFile(fic, inst);
			
		while(i<nbInstr){
		printf("Voulez-vous afficher la ligne %d?\n",i+1);
		printf("1:Oui\n2:Non\n");
		scanf("%d",&choix);
		switch(choix){
		case 1:	
			instruction = encodeInstr(inst[i]);
			if(instruction !=0){
				printf("Instruction:.............. %s\n", inst[i]);
				printf("Instruction Code:......... 0x%X\n\n", instruction);
				cpu.ram[i] = instruction;
			}
			else{
				printf("Error is line %i\n\n", i+1);
			}
		break;
		case 2:
		instruction = encodeInstr(inst[i]);
			if(instruction !=0){
				cpu.ram[i] = instruction;
			}
		printf("ligne %d dépassée\n",i+1);
		break;
		}
		i++;
		}
		while(cpu.ram[cpu.pc] != 0){
			decodeInstr(&cpu, cpu.ram[cpu.pc]);
		}
		clean_stdin();
		argv[1][0]='-';
		argv[1][1]='i';
	}
	if(strcmp(argv[1], "-i")==0){
	int i = 0;
		for(i=1; i<33; i++){
			printf("Registre numéro %i: %i\n",i,cpu.regs[i]);
		}		
		do{
			fgets(commande, 32, stdin);
			if(strncmp(commande, "get reg", 7)==0){
				if(strncmp(commande, "get reg hi", 10)==0){
					printf("reg hi = %i\n", getHi(&cpu));
				}
				else if(strncmp(commande, "get reg lo", 10)==0){
					printf("reg lo = %i\n", getLo(&cpu));
				}
				else{
					replaceMnemo(commande);
					removeDollar(commande);
					reg = charToInt(commande, 8, &i);
					val = getReg(&cpu, reg);
					printf("reg %i = %i\n", reg, val);
				}
			}
			else if(strncmp(commande, "set reg", 7)==0){
				replaceMnemo(commande);
				removeDollar(commande);
				letOneSpace(commande);
				printf("commande: %s\n", commande);
				i = 0;
				reg = charToInt(commande, 8, &i);
				val = charToInt(commande, 10+i-1, &i);
				if(reg == -1){
					printf("Enter register: ");
					fgets(RegNum, 16, stdin);
					replaceMnemo(RegNum);
					removeDollar(RegNum);
					printf("reg: %s\n", RegNum);
					i = 0;
					reg = charToInt(RegNum, 0, &i);
				}
				if(val == -1){
					printf("Enter value for register %i\n", reg);
					scanf("%i", &val);
					getchar();
				}
				setReg(&cpu, reg, val);
			}
			else{
			instruction = encodeInstr(commande);
			if(instruction != 0){
				printf("Instruction: %s\nInst Code: %X\n\n", commande, instruction);
				decodeInstr(&cpu, instruction);
			}
			}
			if(strcmp(commande,"exit")==0){
				for(i=1; i<33; i++){
					printf("Registre numéro %i: %i\n",i,cpu.regs[i]);
				}
			exit(0);
			}
		}while(strcmp(commande, "exit")!=0);
	}
}
return 0;
}  
