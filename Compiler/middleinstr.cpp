#include"middleinstr.h"
#include<iostream>
#include<string>

using namespace std;

MiddleInstr::MiddleInstr(MIType _type, SignaryItem* _desAddr, SignaryItem* _srcAddr1, SignaryItem* _srcAddr2)
{
	type = _type;
	desAddr = _desAddr;
	srcAddr1 = _srcAddr1;
	srcAddr2 = _srcAddr2;
}
string getMITypeName(MIType _type) {
	switch (_type)
	{
	case MULT:
		return "MULT";
		break;
	case DIVISION:
		return "DIV";
		break;
	case ADD:
		return "ADD";
		break;
	case SUB:
		return "SUB";
		break;
	case NEG:
		return "NEG";
		break;
	case ASSIGN:
		return "ASSIGN";
		break;
	case ARRASS:
		return "ARRASS";
		break;
	case ARRGET:
		return "ARRGET";
		break;
	case BLE:
		return "BLE";
		break;
	case BLS:
		return "BLS";
		break;
	case BGE:
		return "BGE";
		break;
	case BGR:
		return "BGR";
		break;
	case BEQ:
		return "BEQ";
		break;
	case BNE:
		return "BNE";
		break;
	case SETL:
		return "SETL";
		break;
	case JUMP:
		return "JUMP";
		break;
	case CALL:
		return "CALL";
		break;
	case RET:
		return "RET";
		break;
	case PUSH:
		return "PUSH";
		break;
	case BEIGN:
		return "BEGIN";
		break;
	case END:
		return "END";
		break;
	case PRINT:
		return "PRINT";
		break;
	case SCAN:
		return "SCAN";
		break;
	case FUNCGET:
		return "FUNCGET";
		break;
	default:
		return "UNDEFINE";
		break;
	}
}
void MiddleInstr::printMIT()
{
	cout << getMITypeName(type) << "\t";
	if (desAddr != NULL) {
		cout << desAddr->name << ",";
	}
	else {
		cout << "\t" << ",";
	}
	if (srcAddr1 != NULL) {
		cout << srcAddr1->name << ",";
	}
	else {
		cout << "\t" << ",";
	}
	if (srcAddr2 != NULL) {
		cout << srcAddr2->name << endl;
	}
	else {
		cout << endl;
	}
}