/******** MIPS_DECODING.H ********/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mips_instructions.h"

#define ADDMASK 3

/* CONSTANTS */
int tabInst[24][16];

#define MAX_IMM 0xFFFF

/* INSTRUCTION CODE SHIFTS */
#define OPCODE_SHIFT 26
#define RS_SHIFT 21
#define RT_SHIFT 16
#define RD_SHIFT 11
#define SA_SHIFT 6
#define FCT_SHIFT 0
#define IMM_SHIFT 0

/* MASKS */
#define OPCODE_MASK 63
#define FCT_MASK 63
#define REG_MASK 31
#define IMM_MASK 65535
#define ADR_MASK 0x3FFFFFF

/* I-TYPE OPCODES */
#define ADDI_OPCODE 8

/* R-TYPE OPCODE */
#define RTYPE_OPCODE 0

/* R-TYPE FUNCTIONS */
#define MULT_FCT 24
#define DIV_FCT 26
#define ADD_FCT 32
#define SUB_FCT 34

/* FUNCTIONS PROTYPES */
int decodeFile(char file[], char inst[][32]);
void clean_stdin(void);
int charToInt(char tabChar[32], int addr, int* offset);
int strOffsetCpy(char dest[], int source[], int nbChar, int offset);
int removeSpaces(char str[]);
int encodeInstr(char instStr[32]);
int removeDollar(char str[]);
int removeParenthesis(char inst[]);
int replaceMnemo(char*);
int decodeInstr(CPU_s* cpu, int instr);
void letOneSpace(char* str);
