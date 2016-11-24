#pragma once
#include"globalSignary.h"
enum MIType {
	MULT,
	DIVISION,
	ADD,
	SUB,
	NEG
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
