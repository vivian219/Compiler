#include"middleinstr.h"
#include<iostream>
MiddleInstr::MiddleInstr(MIType _type, SignaryItem* _desAddr, SignaryItem* _srcAddr1, SignaryItem* _srcAddr2)
{
	type = _type;
	desAddr = _desAddr;
	srcAddr1 = _srcAddr1;
	srcAddr2 = _srcAddr2;
}
void MiddleInstr::printMIT()
{
	cout << type <<" "<< desAddr->name << " " << srcAddr1->name << " " << srcAddr2->name << endl;
}