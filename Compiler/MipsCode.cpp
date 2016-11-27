#include "MipsCode.h"
#include <sstream>
//#include"globalSignary.h"
//Define register
const string $t0 = "$t0";
const string $t1 = "$t1";
const string $t2 = "$t2";
const string $a0 = "$a0";
const string $v0 = "$v0";
const string $fp = "$fp";
const string $sp = "$sp";
const string $ra = "$ra";
const string $global_fp = "$0";

string tostring(int _value) {
	stringstream ss;
	ss << _value;
	return ss.str();
}

void MipsCode::ToMips(MiddleInstr* middle) {
	MIType type = middle->type;
	switch (type)
	{
	case MULT:
	case DIVISION:
	case ADD:
	case SUB:
	case NEG:
		CalcToMips(middle);
		break;
	case ASSIGN:
		AssignToMips(middle);
		break;
	case ARRASS:
		ArrAssToMips(middle);
		break;
	case ARRGET:
		ArrGetToMips(middle);
		break;
	case BLE:
	case BLS:
	case BGE:
	case BGR:
	case BEQ:
	case BNE:
		BranchToMips(middle);
		break;
	case SETL:
		BranchToMips(middle);
		break;
	case JUMP:
		JumpToMips(middle);
		break;
	case CALL:
		CallToMips(middle);
		break;
	case RET:
		RetToMips(middle);
		break;
	case PUSH:
		PushToMips(middle);
		break;
	case BEIGN:
		BeginToMips(middle);
		break;
	case END:
		EndToMips(middle);
		break;
	case PRINT:
		PrintToMips(middle);
		break;
	case SCAN:
		ScanToMips(middle);
		break;
	default:
		break;
	}
}

void MipsCode::CalcToMips(MiddleInstr* middle) {

}

//Format: ASSIGN dst,src
// dst = src
void MipsCode::AssignToMips(MiddleInstr* middle) {
	SignaryItem* target = middle->desAddr;
	SignaryItem* src = middle->srcAddr1;
	VarToReg($t0, src);
	RegToVar($t0, target);
}

//Format: ARRASS dst,src1,src2
// src1[src2] = dst
void MipsCode::ArrAssToMips(MiddleInstr* middle) {
	SignaryItem* target = middle->desAddr;
	SignaryItem* src1 = middle->srcAddr1;
	SignaryItem* src2 = middle->srcAddr2;
	VarToReg($t0, src2);
	addInstr(MIPSType::li, $t1,"4");
	addInstr(MIPSType::mult, $t0, $t0, $t1);
	VarToReg($t2, src1);
	addInstr(MIPSType::add, $t0, $t0, $t2);
	VarToReg($t1, target);
	addInstr(MIPSType::sw, $t1, "0", $t0);
}

//Format: ARRGET dst,src1,src2
// dst = src1[src2]
void MipsCode::ArrGetToMips(MiddleInstr* middle) {
	SignaryItem* target = middle->desAddr;
	SignaryItem* src1 = middle->srcAddr1;
	SignaryItem* src2 = middle->srcAddr2;
	VarToReg($t0, src2);
	addInstr(MIPSType::li, $t1, "4");
	addInstr(MIPSType::mult, $t0, $t0, $t1);
	VarToReg($t2, src1);
	addInstr(MIPSType::add, $t0, $t0, $t2);
	addInstr(MIPSType::lw, $t1, "0", $t0);
	RegToVar($t1, target);
}

//Format: BXX dst,src1,src2
// if src1 xx src2 goto dst
// src1, src2 : variable
// dst : label
void MipsCode::BranchToMips(MiddleInstr* middle) {
	SignaryItem* target = middle->desAddr;
	SignaryItem* src1 = middle->srcAddr1;
	SignaryItem* src2 = middle->srcAddr2;
	VarToReg($t0, src1);
	VarToReg($t1, src2);
	if (middle->type == MIType::BEQ) {
		addInstr(MIPSType::beq, target->name, $t0, $t1);
	}
	else if (middle->type == MIType::BNE) {
		addInstr(MIPSType::bne, target->name, $t0, $t1);
	}
	else if (middle->type == MIType::BLE) {
		addInstr(MIPSType::ble, target->name, $t0, $t1);
	}
	else if (middle->type == MIType::BLS) {
		addInstr(MIPSType::blt, target->name, $t0, $t1);
	}
	else if (middle->type == MIType::BGE) {
		addInstr(MIPSType::bge, target->name, $t0, $t1);
	}
	else if (middle->type == MIType::BGR) {
		addInstr(MIPSType::bgt, target->name, $t0, $t1);
	}

}

//Format: SETL label
void MipsCode::SetLabelToMips(MiddleInstr* middle) {
	addInstr(MIPSType::label, middle->desAddr->name);
}

//Format: JUMP label
void MipsCode::JumpToMips(MiddleInstr* middle) {
	addInstr(MIPSType::j, middle->desAddr->name);
}

//Format: CALL Func
// Func is function
void MipsCode::CallToMips(MiddleInstr* middle) {

}

//Format: RET dst
// dst : variable
// dst -> $v0
void MipsCode::RetToMips(MiddleInstr* middle) {
	VarToReg($v0, middle->desAddr);


}

//Format: PUSH src
// src : variable(parameter)
// push, sp + 4
void MipsCode::PushToMips(MiddleInstr* middle) {

}

//Save Return address
void MipsCode::SaveContext() {
	addInstr(MIPSType::sw, $fp, "0", $sp);
	addInstr(MIPSType::move, $fp, $sp);
	addInstr(MIPSType::addi, $sp, $sp, "4");
	addInstr(MIPSType::sw, $ra, "0", $sp);
	addInstr(MIPSType::addi, $sp, $sp, "4");
}

//Restore Return address
void MipsCode::RestoreContext() {
	addInstr(MIPSType::lw, $ra, "4", $fp);
	addInstr(MIPSType::move, $sp, $fp);
	addInstr(MIPSType::lw, $fp, "0", $fp);
}

/***
 Stack:
		VAR		     offset($fp)  absolute
$sp		------------
		local 3          16         56
		local 2          12         52
		local 1          8          48
		ret addr         4          44
		pre $fp          0          40
$fp		------------
		args3           -4          36
		args2           -8          32
		args1           -12         28
		old local 4     -16         24
		old local 3     -20         20
		old local 2     -24         16
		old local 1     -28         12
		old ret value   -32         8
		old ret addr    -36         4
		olc pre $fp     -40         0
pre $fp	-------------
*/
void MipsCode::BeginToMips(MiddleInstr* middle) {
	SaveContext();
}

void MipsCode::EndToMips(MiddleInstr* middle) {

}

//Format PRINT src
/***
           system call table
Service          $v0     Arguments
print integer     1      $a0 = integer to print
print string      4      $a0 = address of string
print character   11     $a0 = character to print
***/
void MipsCode::PrintToMips(MiddleInstr* middle) {

}
//Format SCAN src
/***
           system call table
Service          $v0     Results
read integer     5       $v0 contains integer read
read character   12      $v0 contains character read
***/

void MipsCode::ScanToMips(MiddleInstr* middle) {

}

void MipsCode::RegToVar(string _$i,SignaryItem* _var) {
	SignaryItem* tmp=cur_sig->querySignary(_var->name);
	if (tmp == NULL)
	{
		//sw $t0,0($t1)
		//sw $t0,4($fp)
		addInstr(MIPSType::sw, _$i, tostring(_var->offset), $global_fp);
	}
	else {
		addInstr(MIPSType::sw, _$i, tostring(_var->offset), $fp);
	}
}

void MipsCode::VarToReg(string _$i, SignaryItem* _var) {
	SignaryItem* tmp = cur_sig->querySignary(_var->name);
	if (tmp == NULL)
	{
		//sw $t0,0($t1)
		//sw $t0,4($fp)
		addInstr(MIPSType::lw, _$i, tostring(_var->offset), $global_fp);
	}
	else {
		addInstr(MIPSType::lw, _$i, tostring(_var->offset), $fp);
	}
}