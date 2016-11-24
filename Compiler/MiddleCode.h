#pragma once
#include<vector>
#include<string>
#include"middleinstr.h"
using namespace std;
class MiddleCode {
public:
	MiddleCode() { strList = vector<string>(); MIList = vector<MiddleInstr*>(); }
	vector<string> strList;
	vector<MiddleInstr*> MIList;
	bool insertMI(MIType _type, SignaryItem* _desAddr, SignaryItem* srcAddr1, SignaryItem* srcAddr2);
	void insertStr(string _s);
	void printMI();
};