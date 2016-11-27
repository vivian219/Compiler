#pragma once
#include<string>
#include<map>
#include<vector>
using namespace std;
enum wordType {
	intTyp,
	charTyp,
	voidTyp
};
enum wordKind {
	constKind,
	TempConKind,
	varKind,
	TempVarKind,
	TempAddrKind,
	functionKind,
	arrKind,
	paraKind,

	label
	//for mips label
};
class SignaryItem {
public:
	string name;
	int size;
	wordKind wk;
	wordType wt;
	int intValue;
	char charValue;
	SignaryItem(string _name, int _size, wordKind _wk, wordType _wt, int _intValue, char _charValue)
	{
		name = _name;
		size = _size;
		wk = _wk;
		wt = _wt;
		intValue = _intValue;
		charValue = _charValue;
	}
};
class Signary {
public:
	string name;
	wordKind wk;
	wordType wt;
	int value;
	char constvalue;
	int size;
	int tempCount = 0;
//	globalSignary*  global;
	//Signary(globalSignary *_global);
	//bool ifDef(string name);
	Signary(string funcname) { name = funcname; }
	vector<wordType>* paraList = NULL;
	bool enterParaList(wordType wt, string name);
	bool enterSignary(string name, wordKind wk, wordType wt, int size, int intValue, char charValue);
	SignaryItem* querySignary(string name);
	vector<SignaryItem*> *sigList = new vector<SignaryItem*>();
	map<string, SignaryItem*> sigTable;
	void printSig();
	bool funCall(vector<SignaryItem*> _paraList);
	SignaryItem* genTemp(wordType wt,wordKind wk);
};
class globalSignary {
public:
	globalSignary() {};
	wordKind wk;
	wordType wt;
	string name;
	int intValue;
	char charValue;
	int size;
	//bool ifDef(string name);
	bool enterGlobSignary(string name, wordKind wk, wordType wt, int size, int intValue, char charValue);
	SignaryItem* queryGlobSignary(string name);
	vector<SignaryItem*> sigGlobList;
	map<string, SignaryItem*> sigGlobTable;
	map<string, Signary*>funcList;
	void printGlobSig();
};

