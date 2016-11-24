#include"globalSignary.h"
#include<iostream>
using namespace std;

bool globalSignary::enterGlobSignary(string name, wordKind wk, wordType wt, int size, int intValue, char charValue)
{
	map<string, SignaryItem*>::iterator sigTmp = sigGlobTable.find(name);
	if (sigTmp == sigGlobTable.end())
	{
		//cout << name << size << endl;
		SignaryItem* sigItemTmp = new SignaryItem(name, size, wk, wt, intValue, charValue);
		//cout << sigItemTmp->name << sigItemTmp->size << endl;
		sigGlobList.push_back(sigItemTmp);
		sigGlobTable[name] = sigItemTmp;
		return true;
	}
	else
	{
		//cout << sigGlobTable[name]->name << sigGlobTable[name]->size;
		return false;
	}
}
SignaryItem* globalSignary::queryGlobSignary(string name)
{
	map<string, SignaryItem*>::iterator sigTmp = sigGlobTable.find(name);
	if (sigTmp != sigGlobTable.end())
	{
		return sigGlobTable[name];
	}
	else
		return NULL;
}
void globalSignary::printGlobSig()
{
	/*for (int i = 0; i < sigGlobList.size(); i++)
	{
		SignaryItem* tmp= sigGlobList.at(i);
		cout << "name=" + tmp->name;
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
		cout<< " wt=" ;
		if (tmp->wt == wordType::charTyp)
			cout << "charTyp"<<endl;
		else if (tmp->wt == wordType::intTyp)
			cout << "intTyp"<<endl;
		else if (tmp->wt == wordType::voidTyp)
			cout << "voidTyp" << endl;
		else
			cout << "wt error";
	}*/
	cout << "the length of function list is" << funcList.size() << endl;
	
		map<string, Signary*>::iterator it;
		//string name = it->first;
		for (it = funcList.begin(); it != funcList.end(); it++)
		{
			Signary* sig = it->second;
			//cout << it->first << endl;
			//cout << sig->name << endl;
			sig->printSig();
			cout << endl;
		}
}
