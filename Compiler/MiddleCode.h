#pragma once
#include<vector>
#include<string>
#include"middleinstr.h"
using namespace std;
class MiddleCode {
public:
	vector<string> strList;
	vector<MiddleInstr*> MIList;
	bool insertMI(MiddleInstr* _mi);
	void insertStr(string _s);
	void printMI();
};