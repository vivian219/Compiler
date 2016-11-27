#include "MipsCode.h"

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

}

//Format: ARRASS dst,src1,src2
// src1[src2] = dst
void MipsCode::ArrAssToMips(MiddleInstr* middle) {

}

//Format: ARRGET dst,src1,src2
// dst = src1[src2]
void MipsCode::ArrGetToMips(MiddleInstr* middle) {

}

//Format: BXX dst,src1,src2
// if src1 xx src2 goto dst
// src1, src2 : variable
// dst : label
void MipsCode::BranchToMips(MiddleInstr* middle) {

}

//Format: SETL label
void MipsCode::SetLabelToMips(MiddleInstr* middle) {

}

//Format: JUMP label
void MipsCode::JumpToMips(MiddleInstr* middle) {

}

//Format: CALL Func
// Func is function
void MipsCode::CallToMips(MiddleInstr* middle) {

}

//Format: RET dst,src
// dst = src
// dst : variable
// src : function
void MipsCode::RetToMips(MiddleInstr* middle) {

}

//Format: PUSH src
// src : variable(parameter)
// push, sp + 4
void MipsCode::PushToMips(MiddleInstr* middle) {

}

//Save Return address
void MipsCode::SaveContext() {

}

//Restore Return address
void MipsCode::RestoreContext() {

}

/***
 Stack:
		VAR		     offset($fp)  absolute
$sp		------------
		local 3          20         60
		local 2          16         56
		local 1          12         52
		ret value        8          48
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