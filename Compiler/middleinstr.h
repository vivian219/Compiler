#pragma once
#include"globalSignary.h"
enum MIType {	
	//for calculation
	MULT,
	DIVISION,
	ADD,
	SUB,
	NEG,

	//for assign var1 = var2
	ASSIGN,
	//for array assign, array[index] = var
	ARRASS,
	//for array get, var = array[index]
	ARRGET,

	//for branch 
	BLE,
	//<=
	BLS,
	//<
	BGE,
	//>=
	BGR,
	//>
	BEQ,
	//==
	BNE,
	//!=

	//set a label as the target of jump
	SETL,

	//for jump
	JUMP,

	//for function call
	CALL,
	RET,
	PUSH,

	//for function definition
	BEIGN,
	END,

	//for system call
	WRITE,
	READ
};
class MiddleInstr {
public:
	MIType type;
	SignaryItem* desAddr;
	SignaryItem* srcAddr1;
	SignaryItem* srcAddr2;
	MiddleInstr(MIType _type, SignaryItem* _desAddr, SignaryItem* srcAddr1, SignaryItem* srcAddr2);
	void printMIT();
};
