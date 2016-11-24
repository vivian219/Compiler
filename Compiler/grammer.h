#include"word.h"
#include"lexer.h"
#include"globalSignary.h"
#include"MiddleCode.h"
#pragma once
void error();
class Grammer {
private :
	Lexer lexer_grammer;
	word token;
public:
	int funcNum = 0;
	Grammer(string _filename);
	MiddleCode MCode;
	Signary *curSignary;
	globalSignary *globSig=new globalSignary();
	map<string, Signary> sigList;
	void next();
	void prog();//程序处理函数
	void constState(bool ifglob);//常量说明
	//void integerDef();//整数定义
	void varState(bool ifglob, string _name, wordType wt);//变量说明
	//void charDef();
	void retFuncDef();//有返回值函数定义
	void voidFuncDef();//无返回值函数定义
	void mainFunc();//主函数处理
	void constDef(bool ifblob);//常量定义
	void varDef(bool ifglob, string _name, wordType wt);//变量定义
	void paraList();//参数表定义
	void compState();//复合语句
	void stateList();//语句列
	void statement();//语句
	void condiState();//条件语句
	void doLoop();//do循环
	void forLoop();//for循环
	void readState();//读语句
	void writeState();//写语句
	void retState();//返回语句
	void assignState();//赋值语句
	SignaryItem* funcCallState();//函数调用
	void condition();//条件语句
	SignaryItem* expresstion();//表达式
	vector<SignaryItem*> valueParaList();//值参数表
	SignaryItem* itemDef();//项
	SignaryItem* factorDef();//因子
	void printSignary();
	bool funcEnterGlob(string name, wordType wt);
	bool queryIdent(string name);
	bool queryFunc(string name);
	SignaryItem* get(string name);
};