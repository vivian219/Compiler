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
	void translate();
	void prog();//��������
	void constState(bool ifglob);//����˵��
	//void integerDef();//��������
	void varState(bool ifglob, string _name, wordType wt);//����˵��
	//void charDef();
	void retFuncDef(SignaryItem* func);//�з���ֵ��������
	void voidFuncDef(SignaryItem* func);//�޷���ֵ��������
	void mainFunc();//����������
	void constDef(bool ifblob);//��������
	void varDef(bool ifglob, string _name, wordType wt);//��������
	void paraList();//��������
	void compState();//�������
	void stateList();//�����
	void statement();//���
	void condiState();//�������
	void doLoop();//doѭ��
	void forLoop();//forѭ��
	void readState();//�����
	void writeState();//д���
	void retState();//�������
	void assignState(SignaryItem* _ident);//��ֵ���
	SignaryItem* funcCallState(SignaryItem* func);//��������
	void condition(SignaryItem* _label, bool ifJ);//�������
	SignaryItem* expresstion();//���ʽ
	vector<SignaryItem*> valueParaList();//ֵ������
	SignaryItem* itemDef();//��
	SignaryItem* factorDef();//����
	void printSignary();
	bool funcEnterGlob(string name, wordType wt);
	bool queryIdent(string name);
	bool queryFunc(string name);
	SignaryItem* get(string name);
	void printMiddleCode();
};