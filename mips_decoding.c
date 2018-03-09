/******** MIPS_DECODING.C ********/
#include "mips_decoding.h"

/* Tableau des instructions MIPS utilisé dans tout le programme */
int tabInst[24][16]=
{
/** R-TYPES **/
/*
 OPCODE 
 |  FCT
 |  |    Inst. TYPE  
 |  |    |   Inst. LENGTH  
 |  |    |   |  Nb. Operands 
 |  |    |   |  |  SHIFT Op1 
 |  |    |   |  |  |   SHIFT Op2  
 |  |    |   |  |  |   |   SHIFT Op3  
 |  |    |   |  |  |   |   |   MASK Op1 
 |  |    |   |  |  |   |   |   |   MASK Op2 
 |  |    |   |  |  |   |   |   |   |   MASK Op3 
 |  |    |   |  |  |   |   |   |   |   |    INST. Letter 1
 |  |    |   |  |  |   |   |   |   |   |    |    INST. Letter 2
 |  |    |   |  |  |   |   |   |   |   |    |    |    INST. Letter 3
 |  |    |   |  |  |   |   |   |   |   |    |    |    |     INST. Letter 4
 |  |    |   |  |  |   |   |   |   |   |    |    |    |     |*/
{0, 32, 'r', 3, 3, 11, 21, 16, 31, 31, 31, 'a', 'd', 'd', '\0'},
{0, 34, 'r', 3, 3, 11, 21, 16, 31, 31, 31, 's', 'u', 'b', '\0'},
{0, 24, 'r', 4, 2, 21, 16, 31, 31, 'm', 'u', 'l', 't', '\0'},
{0, 26, 'r', 3, 2, 21, 16, 31, 31, 'd', 'i', 'v', '\0'},
{0, 42, 'r', 3, 3, 11, 21, 16, 31, 31, 31, 's', 'l', 't', '\0'},
{0, 16, 'r', 4, 1, 11, 31, 'm', 'f', 'h', 'i', '\0'},
{0, 18, 'r', 4, 1, 11, 31, 'm', 'f', 'l', 'o', '\0'},
{0, 2,  'r', 4, 3, 11, 16, 6, 31, 31, 31, 'r', 'o', 't', 'r', '\0'},
{0, 2,  'r', 3, 3, 11, 16, 6, 31, 31, 31, 's', 'r', 'l', '\0'},
{0, 0,  'r', 3, 3, 11, 16, 6, 31, 31, 31, 's', 'l', 'l', '\0'},
{0, 36, 'r', 3, 3, 11, 21, 16, 31, 31, 31, 'a', 'n', 'd', '\0'},
{0, 37, 'r', 2, 3, 11, 21, 16, 31, 31, 31, 'o', 'r', '\0'},
{0, 38, 'r', 3, 3, 11, 21, 16, 31, 31, 31, 'x', 'o', 'r', '\0'},
{0, 8,  'r', 2, 1, 21, 31, 'j', 'r', '\0'},

/** I-TYPES **/
{8 , 0, 'i', 4, 3, 16, 21, 0, 31, 31, 65535, 'a', 'd', 'd', 'i', '\0'},
{35, 0, 'i', 2, 3, 16, 0, 21, 31, 65535, 31, 'l', 'w', '\0'},
{43, 0, 'i', 2, 3, 16, 0, 21, 31, 65535, 31, 's', 'w', '\0'},
{15, 0, 'i', 3, 2, 16, 0, 31, 65535, 'l', 'u', 'i', '\0'},
{4 , 0, 'i', 3, 3, 21, 16, 0, 31, 31, 65535, 'b', 'e', 'q', '\0'},
{5 , 0, 'i', 3, 3, 21, 16, 0, 31, 31, 65535, 'b', 'n', 'e', '\0'},
{7 , 0, 'i', 4, 2, 21, 0, 31, 65535, 'b', 'g', 't', 'z', '\0'},
{6 , 0, 'i', 4, 2, 21, 0, 31, 65535, 'b', 'l', 'e', 'z', '\0'},

/** J-TYPES **/
{2, 0, 'j', 1, 1, 0, 0x3FFFFFF, 'j', '\0'},
{3, 0, 'j', 3, 1, 0, 0x3FFFFFF, 'j', 'a', 'l', '\0'}
};

void clean_stdin(void) /* Vide le buffer d'entrée du clavier */
{ 
int c; 
	do{ 
        	c = getchar(); 
	}while(c != '\n' && c != EOF); 
}

int decodeFile(char file[], char inst[][32]) /* Ouvre un fichier contenant du langage assembleur MIPS et décode chaque ligne jusqu'à la ligne contenant la chaine de caractère "end" */
{											 /* pour ensuite les stocker dans un tableau, retourne le nombre de lignes décodées. */
int i=0;
char c;
char cprev;
char tab[32][32];
FILE* fichier;
int tabIndex=0;
int tabIndex2=0;
int test=1;
int test_comm = 0;
strcpy(tab[0],"");
fichier = fopen(file, "r");

while(test==1){
        fscanf(fichier, "%c", &c);
	if(c == '#'){
		test_comm = 1;
	}
	if(test_comm == 1 && c!='\n'){
		c = ' ';
	} 
        if(c=='\n' && cprev!='\n'){
                tabIndex++;
                tabIndex2=0;
		test_comm = 0;
        }
        else if(c!='\n' && c!=' '){
		tab[tabIndex][tabIndex2]=c;
                tabIndex2++;
        }
	if(tab[tabIndex][tabIndex2-3]=='e' && tab[tabIndex][tabIndex2-2]=='n' && tab[tabIndex][tabIndex2-1]=='d'){
		test=0;
	}
	cprev = c;
}
for(i=0; i<tabIndex; i++){
	tab[i][strlen(tab[i])+1]='\0';
	strcpy(inst[i], tab[i]);
}
return tabIndex;
}

int charToInt(char tabChar[32], int addr, int* offset) /* Convertit un nombre en ASCII à la position addr de la chaine tabChar en nombre entier. Retourne le nombre. Retourne sa longueur du dans offset. */
{
int res = -1;
int sign = 1;
int i = 0;
int nb = 0;
/*addr = addr+*offset;*/
if(tabChar[addr]=='-'){
	sign = -1;
	addr++;
}
i = addr;
while(tabChar[i]>='0' && tabChar[i]<='9')
{
	i++;
}
if(i!=addr){
	res = 0;
}
nb = i-addr;
*offset += nb;
for(i=addr; i<addr+nb; i++)
{
	res += (int)(tabChar[i]-48)*((int)pow(10, addr+nb-i-1)); 
}
res = res*sign;
return res;
}


int strOffsetCpy(char dest[], int source[], int nbChar, int offset) /* Copie nbChar caractères de source[] à partir de l'adresse offset dans dest[]. */
{
int i = 0;
for(i=0; i<=nbChar; i++)
{
	dest[i] = (char)source[i+offset];
}
return i;
}

int removeSpaces(char str[]){ /* Enlève les espaces d'une chaine de caractères. */
unsigned int i = 0;
unsigned int j = 0;
char tmp[512];
while(i<strlen(str)){
	if(str[i]!=' ' && str[i]!='\n'){
		tmp[j]=str[i];
		j++;
	}
	i++;
}
tmp[j]='\0';
for(i=0; i<=j; i++){
	str[i] = tmp[i];
}
return 0;
}

int encodeInstr(char instStr[32]) /* Encode une instruction sous forme de chaine de caractères en hexadécimal. Retourne la valeure hexadécimale de l'instruction encodée. */
{
int i = 0;
int res = 0;
char instCmp[32];
int offset = 0;
int op1 = 0;
int op2 = 0;
int op3 = 0;
int j = 0;
char tmp;

replaceMnemo(instStr);
removeParenthesis(instStr);
removeDollar(instStr);
removeSpaces(instStr);

for(i=0; i<24; i++){
	op1 = 0;
	op2 = 0;
	op3 = 0;
	offset = 0;
	strOffsetCpy(instCmp, tabInst[i], tabInst[i][3]+1, 2*(tabInst[i][4])+5);
	if(strncmp(instStr, "addi", 4)==0 && tabInst[i][2*tabInst[i][4]+5]=='a' && tabInst[i][2*tabInst[i][4]+6]=='d' && tabInst[i][2*tabInst[i][4]+7]=='d' && tabInst[i][2*tabInst[i][4]+8]=='\0'){
		j++;
		tmp = instStr[4];
		instStr[4]='\0';
	}
	if(strncmp(instStr, instCmp, tabInst[i][3]+j)==0){
		if(j==1){
			instStr[4]=tmp;
			j=0;
		}
		if(tabInst[i][2]=='r'){

			res |= (RTYPE_OPCODE<<OPCODE_SHIFT);
			res |= (tabInst[i][1]<<FCT_SHIFT);
			if(tabInst[i][4]==1){
				op1 = charToInt(instStr, tabInst[i][3], &offset);
				res |= ((op1&tabInst[i][6])<<tabInst[i][5]);
			}
			else if(tabInst[i][4]==2){
				op1 = charToInt(instStr, tabInst[i][3], &offset);
				op2 = charToInt(instStr, tabInst[i][3]+1+offset, &offset);
				res |= ((op1&tabInst[i][7])<<tabInst[i][5]);
				res |= ((op2&tabInst[i][8])<<tabInst[i][6]);
			}
			else if(tabInst[i][4]==3){			
				op1 = charToInt(instStr, tabInst[i][3], &offset);
				op2 = charToInt(instStr, tabInst[i][3]+1+offset, &offset);
				op3 = charToInt(instStr, tabInst[i][3]+2+offset, &offset);
				res |= ((op1&tabInst[i][8])<<tabInst[i][5]);
				res |= ((op2&tabInst[i][9])<<tabInst[i][6]);
				res |= ((op3&tabInst[i][10])<<tabInst[i][7]);
			}
		}
		else if(tabInst[i][2]=='i'){
			res |= (tabInst[i][0]<<OPCODE_SHIFT);
/*			res |= (0<<FCT_SHIFT);*/
			if(tabInst[i][4]==2){
				op1 = charToInt(instStr, instStr[tabInst[i][3]], &offset);
				op2 = charToInt(instStr, instStr[tabInst[i][3]+1+offset], &offset);
				res |= ((op1&tabInst[i][7])<<tabInst[i][5]);
				res |= ((op2&tabInst[i][8])<<tabInst[i][6]);
			}
			else if(tabInst[i][4]==3){			
				op1 = charToInt(instStr, tabInst[i][3], &offset);
				op2 = charToInt(instStr, tabInst[i][3]+1+offset, &offset);
				op3 = charToInt(instStr, tabInst[i][3]+2+offset, &offset);
				res |= ((op1&tabInst[i][8])<<tabInst[i][5]);
				res |= ((op2&tabInst[i][9])<<tabInst[i][6]);
				res |= ((op3&tabInst[i][10])<<tabInst[i][7]);
			}

		}
		else if(tabInst[i][2]=='j'){
			res |= (tabInst[i][0] << OPCODE_SHIFT);
			op1 = charToInt(instStr, tabInst[i][3], &offset);
			res |= ((op1&tabInst[i][6])<<tabInst[i][5]);
		}
	}
}
if(res == 0){
if(strcmp(instStr,"quitter")==0){
		printf("Merci et à bientôt\n");		
		exit(0);	
	}
	printf("ERROR: Instruction not recognized: %s\n", instStr);
}
return res;
}

int removeDollar(char str[]) /* Supprime les '$' de la chaine de caractère str[]. */
{
unsigned int i = 0;
unsigned int j = 0;
char tmp[512];
while(i<strlen(str)){
	if(str[i]!='$' && str[i]!='\n'){
		tmp[j]=str[i];
		j++;
	}
i++;
}
tmp[j]='\0';
for(i=0; i<=j; i++){
	str[i] = tmp[i];
}
return 0;
}

int replaceMnemo(char inst[32]) /* Remplace les mnémoniques des registres par leurs numéros. */
{
int i = 0;
int j = 0;
int len = 0;
int offset = 0;
len = strlen(inst);
for(i=0; i<len; i++){
	if(inst[i]=='$'){
		offset = 0;
		if(inst[i+1]=='z' && inst[i+2]=='e' && inst[i+3]=='r' && inst[i+4]=='o'){
		inst[i+1]='0';
			for(j=2; j<=5; j++){
				inst[i+j]=inst[i+j+3];
				inst[i+j+3]=' ';
			}
		}
		else if(inst[i+1]=='a' && inst[i+2]=='t'){
			inst[i+1]='1';
			inst[i+2]=' ';
		}
		else if(inst[i+1]=='v'){
			inst[i+1]= (char)(charToInt(inst, i+2, &offset)+50);
			inst[i+2]=' ';
		}
		else if(inst[i+1]=='a' && inst[i+2]!='t'){
			inst[i+1]= (char)(charToInt(inst, i+2, &offset)+52);
			inst[i+2]=' ';
		}
		else if(inst[i+1]=='t' && inst[i+2]>='0' && inst[i+2]<='7'){
			if(charToInt(inst, i+2, &offset)<2){
				inst[i+1]= (char)(charToInt(inst, i+2, &offset)+'8');
				inst[i+2]=' ';
			}
			else{
				inst[i+1]= '1';
				inst[i+2] = (char)(charToInt(inst, i+2, &offset)+46);
				}
		}
		else if(inst[i+1]=='s' && inst[i+2]>='0' && inst[i+2]<='7'){
			if(charToInt(inst, i+2, &offset)<4){
				inst[i+1]= '1';
				inst[i+2]=(char)(charToInt(inst, i+2, &offset)+'6');
			}
			else{
				inst[i+1]= '2';
				inst[i+2] = (char)(charToInt(inst, i+2, &offset)+44);
			}
		}
		else if(inst[i+1]=='t' && inst[i+2]>='8' && inst[i+2]<='9'){
			inst[i+1]='2';
			inst[i+2]= (char)(charToInt(inst, i+2, &offset)+44);
		}
		else if(inst[i+1]=='k' && inst[i+2]>='0' && inst[i+2]<='1'){
			inst[i+1]='2';
			inst[i+2]= (char)(charToInt(inst, i+2, &offset)+54);
		}
		else if(inst[i+1]=='g' && inst[i+2]=='p'){
			inst[i+1]='2';
			inst[i+2]='8';
		}
		else if(inst[i+1]=='s' && inst[i+2]=='p'){
			inst[i+1]='2';
			inst[i+2]='9';
		}
		else if(inst[i+1]=='f' && inst[i+2]=='p'){
			inst[i+1]='3';
			inst[i+2]='0';
		}
		else if(inst[i+1]=='r' && inst[i+2]=='a'){
			inst[i+1]='3';
			inst[i+2]='1';
		}
	}
}
return 0;
}

int removeParenthesis(char inst[]) /* Supprime les parenthèses de le chaine de cractères inst[]. */
{
int len = 0;
int i = 0;
int j = 0;
char tmp[64];
len = strlen(inst);
while(i<len){
	if(inst[i]!='(' && inst[i]!=')'){
		tmp[j]=inst[i];
		j++;	
	}
	else if(inst[i]=='('){
		tmp[j]=',';
		j++;
	}
i++;
}
tmp[j]='\0';
strcpy(inst, tmp);
return 0;
}


int decodeInstr(CPU_s* cpu, int instr) /* Décode l'instruction instr (sous forme hexadécimale) et l'éxécute. Nécessite un pointeur sur strucutre CPU_s, contenant les registres et la mémoire. */
{
long opcode = 0;
char instCmp[32];
int i = 0;
short int op1 = 0;
short int op2 = 0;
short int op3 = 0;
int opj = 0;
int fct = 0;
opcode = ( (instr>>OPCODE_SHIFT) & OPCODE_MASK);
fct = ( (instr&(FCT_MASK<<FCT_SHIFT)) >> FCT_SHIFT );
	if(opcode != 0){
		fct = 0;
	}
	for(i=0; i<24; i++){
		op1 = 0;
		op2 = 0;
		op3 = 0;
		if(opcode == tabInst[i][0] && fct==tabInst[i][1]){
			strOffsetCpy(instCmp, tabInst[i], tabInst[i][3]+1, 2*tabInst[i][4]+5);
			if(tabInst[i][4]==1){
				op1 = (instr&(tabInst[i][6]<<tabInst[i][5])) >> tabInst[i][5];
				opj = (instr&(tabInst[i][6]<<tabInst[i][5])) >> tabInst[i][5];
			}
			else if(tabInst[i][4]==2){
				op1 = (instr&(tabInst[i][7]<<tabInst[i][5])) >> tabInst[i][5];
				op2 = (instr&(tabInst[i][8]<<tabInst[i][6])) >> tabInst[i][6];
			}
			else if(tabInst[i][4]==3){			
				op1 = (instr&(tabInst[i][8]<<tabInst[i][5])) >> tabInst[i][5];
				op2 = (instr&(tabInst[i][9]<<tabInst[i][6])) >> tabInst[i][6];
				op3 = (instr&(tabInst[i][10]<<tabInst[i][7])) >> tabInst[i][7];
			}
			printf("DECODED: %s // op1: %i // op2: %i // op3: %i\n", instCmp, op1, op2, op3);
			switch(opcode){
				case 0:
					switch(fct){
						case 32:
							add(cpu, op1, op2, op3);
						break;
						case 34:
							sub(cpu, op1, op2, op3);
						break;
						case 24:
							mult(cpu, op1, op2);
						break;
						case 26:
							divp(cpu, op1, op2);
						break;
						case 42:
							slt(cpu, op1, op2, op3);
						break;
						case 16:
							mfhi(cpu, op1);
						break;
						case 18:
							mflo(cpu, op1);
						break;
						case 2:
							srl(cpu, op1, op2, op3);
						break;
						case 0:
							sll(cpu, op1, op2, op3);
						break;
						case 36:
							andp(cpu, op1, op2, op3);
						break;
						case 37:
							orp(cpu, op1, op2, op3);
						break;
						case 38:
							xorp(cpu, op1, op2, op3);
						break;
						case 8:
							jr(cpu, op1);
						break;
						default:
						break;
					}	
				break;
				case 8:
					addi(cpu, op1, op2, op3);
				break;
				case 35:
					lw(cpu, op1, op2, op3);
				break;
				case 43:
					sw(cpu, op1, op2, op3);
				break;
				case 15:
					lui(cpu, op1, op3);
				break;
				case 4:
					beq(cpu, op1, op2, op3);
				break;
				case 5:
					bne(cpu, op1, op2, op3);
				break;
				case 7:
					bgtz(cpu, op1, op2);
				break;
				case 6:
					blez(cpu, op1, op2);
				break;
				case 2:
					jp(cpu, op1);
				break;
				case 3:
					jal(cpu, opj);
				break;
				default:
				break;
			}
		}
	}				
return 0;
}

void letOneSpace(char* str) /* Laisse un seul espace la ou il peut y en avoir plusieurs */
{
int len;
int i = 0;
int j = 0;
len = strlen(str);
while(i<len)
{
	if(*(str+i)==' ' && *(str+i-1)==' '){
		for(j=i; j<len-1; j++){
			*(str+j)=*(str+j+1);
		}
		*(str+j)='\0';
	}
i++;
}
}

