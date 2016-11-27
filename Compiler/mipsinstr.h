#pragma once
#include <string>

using namespace std;
enum MIPSType {
	li,
	la,

	lw,
	sw,

	jal,
	j,
	jr,

	add,
	addi,
	move,
	sub,
	subi,
	mult,
	slash,

	bgez,
	blez,
	bgtz,
	bltz,
	beq,
	bne,

	label,

	syscall,

	comment
};

class MipsInstr {
public:
	string mips_op = "";
	string des = "";
	string src1 = "";
	string src2 = "";
	MipsInstr(MIPSType _mips_type, string _des = "", string _src1 = "", string _src2 = "") {
		mips_op = getTypeName(_mips_type);
		des = _des;
		src1 = _src1;
		src2 = _src2;
	}
	string getInstr();
	void print();
private:
	string getTypeName(MIPSType mips_type);
};

class PreDefine {
public:
	string label;
	string conString;
	PreDefine(string _label, string _const) {
		label = _label;
		conString = _const;
	}
	string getDefine() {
		return label + ": .ascizz " + conString;
	}
};