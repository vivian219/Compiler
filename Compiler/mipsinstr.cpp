#include "mipsinstr.h"
#include <iostream>

using namespace std;

string MipsInstr::getTypeName(MIPSType type) {
	switch (type)
	{
	case li:
		return "li";
		break;
	case la:
		return "la";
		break;
	case lw:
		return "lw";
		break;
	case sw:
		return "sw";
		break;
	case jal:
		return "jal";
		break;
	case j:
		return "j";
		break;
	case jr:
		return "jr";
		break;
	case add:
		return "add";
		break;
	case addi:
		return "addi";
		break;
	case MIPSType::move:
		return "move";
		break;
	case sub:
		return "sub";
		break;
	case subi:
		return "subi";
		break;
	case mult:
		return "mul";
		break;
	case slash:
		return "div";
		break;
	case bgez:
		return "bgez";
		break;
	case blez:
		return "blez";
		break;
	case bgtz:
		return "bgtz";
		break;
	case bltz:
		return "bltz";
		break;
	case beq:
		return "beq";
		break;
	case bne:
		return "bne";
		break;
	case label:
		return "";
		break;
	case syscall:
		return "syscall";
		break;
	case comment:
		return "#";
		break;
	default:
		return "#ERROR";
		break;
	}
}

void MipsInstr::print() {
	cout << mips_op << des << src1 << src2 << endl;
}
string MipsInstr::getInstr() {
	return mips_op + des + src1 + src2;
}