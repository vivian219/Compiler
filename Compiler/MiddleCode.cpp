#include"MiddleCode.h"
#include<iostream>
bool MiddleCode::insertMI(MIType _type, SignaryItem* _desAddr, SignaryItem* srcAddr1, SignaryItem* srcAddr2)
{
	MiddleInstr* _mi = new MiddleInstr(_type, _desAddr, srcAddr1, srcAddr2);
	if (_mi != NULL)
	{
		MIList.push_back(_mi);
		return true;
	}
	else
	{
		cout<< "middleinstr is null" << endl;
		return false;
	}
}
void MiddleCode::insertStr(string _s)
{
		strList.push_back(_s);
}
void MiddleCode::printMI()
{
	vector<MiddleInstr*>::iterator tmp;
	for (tmp = MIList.begin(); tmp != MIList.end(); tmp++)
	{
		(*tmp)->printMIT();
	}
}