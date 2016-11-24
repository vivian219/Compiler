#include"globalSignary.h"
#include<iostream>
using namespace std;
//Signary::Signary(globalSignary *_global)
//{
//	global = _global;
//}
bool Signary::enterSignary(string name, wordKind wk, wordType wt, int size,int intValue,char charValue)
{
	map<string, SignaryItem*>::iterator sigTmp = sigTable.find(name);
	if (sigTmp == sigTable.end())
	{
		SignaryItem* sigTmp = new SignaryItem(name, size, wk, wt,intValue,charValue);
		sigList->push_back(sigTmp);
		sigTable[name] = sigTmp;
		return true;
	}
	else
		return false;
}
SignaryItem* Signary::querySignary(string _name)
{
	map<string, SignaryItem*>::iterator sigTmp = sigTable.find(_name);
	if (sigTmp != sigTable.end())
	{
		return sigTable[_name];
	}
	else
		return NULL;
}
void Signary::printSig()
{
	for (int i = 0; i < sigList->size(); i++)
	{
		SignaryItem* tmp = sigList->at(i);
		cout << "name=" << tmp->name;
		cout << " size=" << tmp->size;
		cout << "wk=";
		if (tmp->wk == wordKind::varKind)
			cout << "varKind";
		else if (tmp->wk == wordKind::arrKind)
			cout << "arrKind";
		else if (tmp->wk == wordKind::constKind)
			cout << "constKind";
		else if (tmp->wk == wordKind::functionKind)
			cout << "functionKind";
		else
			cout << "wk error";
		cout << " size=" << tmp->size;
		cout << "intValue=" << tmp->intValue;
		cout << "charValue=" << tmp->charValue;
		cout << " wt=";
		if (tmp->wt == wordType::charTyp)
			cout << "charTyp" << endl;
		else if (tmp->wt == wordType::intTyp)
			cout << "intTyp" << endl;
		else if (tmp->wt == wordType::voidTyp)
			cout << "voidTyp" << endl;
		else
			cout << "wt error";
	}
}
bool Signary::enterParaList(wordType wt, string name)
{
	map<string, SignaryItem*>::iterator tmp = sigTable.find(name);
	if (tmp == sigTable.end())
	{
		enterSignary(name, wordKind::paraKind, wt, 4, 0, NULL);//Ð´Èë·ûºÅ±í
		paraList->push_back(wt);
		return true;
	}
	else
	{
		cout << "parameter failed to enter the parameter list" << endl;
		return false;
	}
}
