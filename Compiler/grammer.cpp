#include"grammer.h"
#include"globalSignary.h"
#include"word.h"
#include<iostream>
#include<set>
void error()
{
	cout << "error" << endl;
}
Grammer::Grammer(string _filename):lexer_grammer(_filename) {
	next();
}
void Grammer::next()
{
	token = lexer_grammer.getword();
}
void Grammer::prog()
{
	//wordType funcWt = wordType::intTyp; string funName;
	if (token.word_sym==symbol::constsym)
	{
		bool ifglob = true;
		constState(true);
	}
	if (token.word_sym==symbol::intsym||token.word_sym==symbol::charsym)
	{
		wordType wt;
		if (token.word_sym == symbol::intsym)
			wt = wordType::intTyp;
		else
			wt = wordType::charTyp;
		next();
		string name=token.name;
		if (token.word_sym != ident)
		{
			error();
			cout << "���ͱ�ʶ�������ޱ�ʶ��" << endl;
		}
		next();
		if (token.word_sym != symbol::lparen)
		{
			if (token.word_sym != symbol::lsquare)
				globSig->enterGlobSignary(name, wordKind::varKind, wt, 4, 0, NULL);
			varState(true, name, wt);
		}
		else
		{
			bool enter=funcEnterGlob(name, wt);
			if (!enter)
			{
				cout << "function " << name << "enter the signary failed" << endl;
			}
		}
	}
	while (true)
	{
		if (token.word_sym== symbol::intsym || token.word_sym ==symbol::charsym)
		{
			wordType wt;
			if (token.word_sym == symbol::intsym)
				wt = wordType::intTyp;
			else
				wt = wordType::intTyp;
			next();
			string name = token.name;
			if (token.word_sym != symbol::ident)
			{
				error();
				name = "ident";
				cout << "�з���ֵ��������ȱ�ٺ�����" << endl;
			}
			/*globSig->enterGlobSignary(name,wordKind::functionKind,wt,4,0,NULL);
			globSig->funcList[name] = new Signary(name);
			curSignary = globSig->funcList[name];
			cout << "curSignary="<<curSignary->name <<"name="<<globSig->funcList[name]->name<< endl;*/
			funcEnterGlob(name, wt);
			next();
		}
		if (token.word_sym == symbol::lparen)
		{
			retFuncDef();
		}
		if (token.word_sym == symbol::voidsym)
		{
			string name;
			next();
			name = token.name;
			if (token.word_sym == symbol::mainsym)
				break;
			else if (token.word_sym != symbol::ident)
			{
				error();
				cout << "�޷���ֵ��������ȱ�ٺ�����" << endl;
			}
			//Signary*sigTmp = new Signary();
			/*cout << "funcName:" << name << endl;
			globSig->funcList[name] = new Signary(name);
			cout << "After:" << endl;
			globSig->enterGlobSignary(name, wordKind::functionKind,wordType::voidTyp, 4, 0, NULL);
			curSignary = globSig->funcList[name];
			curSignary->printSig();*/
			funcEnterGlob(name, wordType::voidTyp);
			next();
			voidFuncDef();
		}
	}
	if (token.word_sym == symbol::mainsym)
	{
	//	Signary*sigTmp = new Signary();
		/*globSig->funcList["main"] = new Signary("main");
		globSig->enterGlobSignary("main", wordKind::functionKind, wordType::voidTyp, 4, 0, NULL);
		curSignary = globSig->funcList["main"];*/
		funcEnterGlob("main", wordType::voidTyp);
		next();
		mainFunc();
	}
	else
	{
		error();
		cout << "120" << endl;
	}
	printSignary();
}
void Grammer::constState(bool ifglob)
{
	while (token.word_sym == symbol::constsym)
	{
		next();
		constDef(ifglob);
		if (token.word_sym != symbol::semicolon)
		{
			error();
			cout << "��ʽ�Ƿ���������������û�мӷֺ�" << endl;
		}
		next();
	}
}
void Grammer::constDef(bool ifglob)
{
	if (token.word_sym == symbol::intsym)
	{
		while (1)
		{
			string name=""; 
			int intValue=0;
			next();
			if (token.word_sym != symbol::ident)
			{
				error();
				cout << "��ʽ�Ƿ�����������ʱȱ�ٱ�ʶ��" << endl;
			}
			name = token.name;
			next();
			if (token.word_sym != symbol::becomes)
			{
				error();
				cout << "��������ʱȱ�ٵȺ�" << endl;
			}
			next();
			symbol op = token.word_sym;
			if (token.word_sym == symbol::plus || token.word_sym == symbol::minus)
				next();
			if (token.word_sym != symbol::number)
			{
				error();
				cout << "����int�ͳ���ʱ���ָ�ʽ����ȷ" << endl;
			}
			intValue = token.value;
			if (op == symbol::minus)
				intValue = -intValue;
			bool enter;
			if (ifglob)
			{
				enter=globSig->enterGlobSignary(name, wordKind::constKind,wordType::intTyp,4, intValue,NULL);
			}
			else
			{
			//	cout << "local function name=" << curSignary->name << endl;
				enter=curSignary->enterSignary(name, wordKind::constKind, wordType::intTyp, 4, intValue, NULL);
			}
			if (enter == false)
			{
				
				cout << "constant enter signary fail,cause the constant has been defined" << endl;
			}
			next();
			if (token.word_sym != symbol::comma)
			{
				break;
			}
		}
	}
	else if (token.word_sym == symbol::charsym)
	{
		while (1)
		{
			next();
			string name;
			name = token.name;
			if (token.word_sym != symbol::ident)
			{
				error(); cout << "202" << endl;
			}
			next();
			if (token.word_sym != symbol::becomes)
			{
				error(); cout << "207" << endl;
			}
			next();
			char ch = token.name.at(0);
			if (ifglob)
			{
				globSig->enterGlobSignary(name, wordKind::constKind, wordType::charTyp, 1, 0, ch);
			}
			else
			{
				//cout << "local function name=" << curSignary->name << endl;
				curSignary->enterSignary(name, wordKind::constKind, wordType::charTyp, 1, 0, ch);
			}
			if (token.word_sym != symbol::charConst)
			{
				error(); cout << "222" << endl;
			}
			next();
			if (token.word_sym != symbol::comma)
				break;
		}
	}
	else
	{
		error(); cout << "230" << endl;
	}
}
void Grammer::varState(bool ifglob, string _name, wordType _wt)
{
	string name=_name; wordType wt=_wt;
	while (1)
	{
		if (token.word_sym == symbol::semicolon)
		{
			if (ifglob)
				globSig->enterGlobSignary(name, wordKind::varKind, wt, 0, 0, NULL);
			else
			{
				curSignary->enterSignary(name, wordKind::varKind, wt, 0, 0, NULL);
				//cout << "local function name=" << curSignary->name << endl;
			}
			next();
			if (token.word_sym == symbol::intsym)
				wt = wordType::intTyp;
			else
				wt = wordType::charTyp;
			if (token.word_sym != symbol::intsym&&token.word_sym != charsym)
			{
				wt = wordType::intTyp;
				//cout << "this is variable statement" << endl;
				return;
			}
			next();
			name = token.name;
			if (token.word_sym != symbol::ident)
			{
				error();
				cout << "���������б�ʶ�����ͺ��ޱ�ʶ��" << endl;
			}
			next();
			if (token.word_sym == symbol::lparen)
			{
				funcEnterGlob(name, wt);
				return;
			}
			else if (token.word_sym == symbol::comma)
			{
				if (ifglob)
					globSig->enterGlobSignary(name, wordKind::varKind, wt, 0, 0, NULL);
				else
				{
					curSignary->enterSignary(name, wordKind::varKind, wt, 0, 0, NULL);
				//	cout << "local function name=" << curSignary->name << endl;
				}
				continue;
			}
			else
				continue;
		}
		else
		{

			varDef(ifglob,name,wt);
		}
	//	cout << "this is variable statement" << endl;
	}
}
void Grammer::varDef(bool ifglob,string _name,wordType wt)
{
	string name=_name; int size=0;
	while (true)
	{
		if (token.word_sym == symbol::semicolon)
			return;
		if (token.word_sym == symbol::lsquare)
		{

			next();
			size = token.value;
		//	cout << "size=" << token.value<<endl;
			if (token.word_sym != symbol::number)
			{
				error();
				cout << "�����±겻Ϊ����" << endl;
				size = 10;
			}
			next();
			if (token.word_sym != symbol::rsquare)
			{
				error();
				cout << "���鶨����ȱ��������" << endl;
			}
			if (ifglob)
			{
				//cout << "array1 size=" <<size<< endl;
				globSig->enterGlobSignary(name, wordKind::arrKind, wt, size, 0, NULL);
				//cout <<  globSig->sigGlobTable[name]->size<<endl;
			}
			else
			{
				//cout << "array2 size=" <<size<< endl;
				//cout << "local function name=" << curSignary->name << endl;
				curSignary->enterSignary(name, wordKind::arrKind, wt, size, 0, NULL);
			}
			next();
		}
		if (token.word_sym == symbol::comma)
		{
			next();
			name = token.name;
			if (token.word_sym != symbol::ident)
			{
				error();
				name = "ident";
				cout << "���������ж��ź���ȱ�ٱ�ʶ��" << endl;
			}
			next();
			int size = 4;
			if (token.word_sym == symbol::lsquare)
			{
				next();
				if (token.word_sym != symbol::number)
				{
					error();
					cout << "the define of array lack of integer as index" << endl;
					size = 1;
				}
				size = token.value;
				next();
				if (token.word_sym != symbol::rsquare)
				{
					error();
					cout << "the arrry define lack of ]" << endl;
				}
				next();
			}
			if (ifglob)
			{
				globSig->enterGlobSignary(name, wordKind::varKind, wt, size, 0, NULL);
			}
			else
			{
				//cout << "local function name=" << curSignary->name << endl;
				curSignary->enterSignary(name, wordKind::varKind, wt, size, 0, NULL);
			}
		}
	}
}
void Grammer::retFuncDef()
{
	while (true)
	{
		if (token.word_sym != symbol::lparen)
		{
			error(); cout << "380" << endl;
		}
		next();
		if (token.word_sym == symbol::rparen)
		{
			next();
		}
		else
		{
			paraList();
			if (token.word_sym != symbol::rparen)
			{
				error(); cout << "392" << endl;
			}
			next();
		}
		if (token.word_sym != symbol::lbrac)
		{
			error(); cout << "398" << endl;
		}
		next();
		compState();
		if (token.word_sym != symbol::rbrac)
		{
			error(); cout << "404" << endl;
		}
		//cout << "this is a function with return statment" << endl;
		next();
		if (token.word_sym != symbol::intsym&&token.word_sym != symbol::charsym)
			break;
		wordType wt;
		if (token.word_sym == symbol::intsym)
			wt = wordType::intTyp;
		else
			wt = wordType::charTyp;
		next();
		string name = token.name;
		if (token.word_sym != symbol::ident)
		{
			error();
			cout << "�з���ֵ��������ȱ�ٺ�����" << endl;
			name = "ident";
		}
		//globSig->enterGlobSignary(name, wordKind::functionKind, wt, 4, 0, NULL);
		////Signary*sigTmp = new Signary();
		//globSig->funcList[name] = new Signary(name);
		//curSignary = globSig->funcList[name];
		funcEnterGlob(name, wt);
		next();
	}
}
void Grammer::paraList()
{
	wordType wt; string name="";
	while (true)
	{
		if (token.word_sym != symbol::intsym&&token.word_sym != symbol::charsym)
		{
			error();
			cout << "������������б�ȱ�����ͱ�ʶ��" << endl;
		}
		if (token.word_sym == symbol::intsym)
			wt = wordType::intTyp;
		else
			wt = wordType::charTyp;
		next();
		name = token.name;
		curSignary->enterParaList(wt, name);
		if (token.word_sym != symbol::ident)
		{
			error();
			cout << "��������Ĳ����б�ȱ�ٱ�ʶ��" << endl;
		}
		next();
		if (token.word_sym != symbol::comma)
			break;
		next();
	}
}
void Grammer::voidFuncDef()
{
	if (token.word_sym != symbol::lparen)
	{
		error(); cout << "463" << endl;
	}
	next();
	if (token.word_sym == symbol::rparen)
	{
		next();
	}
	else
	{
		paraList();
		if (token.word_sym != symbol::rparen)
		{
			error(); cout << "475" << endl;
		}
		next();
	}
	if (token.word_sym != symbol::lbrac)
	{
		error(); cout << "482" << endl;
	}
	next();
	compState();
	if (token.word_sym != symbol::rbrac)
	{
		error(); cout << "488" << endl;
	}
	next();
	//cout << "this is a function without return statement" << endl;
}
void Grammer::mainFunc()
{
	if (token.word_sym != symbol::lparen)
	{
		error(); cout << "496" << endl;
	}
	next();
	if (token.word_sym != symbol::rparen)
	{
		error(); cout << "501" << endl;
	}
	next();
	if (token.word_sym != symbol::lbrac)
	{
		error(); cout << "507" << endl;
	}
	next();
	compState();
	if (token.word_sym != symbol::rbrac)
	{
		error(); cout << "512" << endl;
	}
	next();
//	cout << "this is main function" << endl;
}
void Grammer::compState()
{
		if (token.word_sym == symbol::constsym)
		{
			constState(false);
		}
		if (token.word_sym == symbol::intsym || token.word_sym == symbol::charsym)
		{
			string name; wordType wt;
			if (token.word_sym == symbol::intsym)
				wt = wordType::intTyp;
			else
				wt = wordType::charTyp;
			next();
			name = token.name;
			if (token.word_sym != symbol::ident)
			{
				error();
				name = "ident";
				cout << "�������ı�������û�б�ʶ��" << endl;
			}
			next();
			varState(false,name,wt);
		}
		if (token.word_sym == symbol::rbrac)
		{
			return;
		}
		else
		{
			stateList();
		}
}
void Grammer::stateList()
{
	while (true)
	{
		statement();
		if (token.word_sym == symbol::rbrac)
			break;
	}
}
void Grammer::statement()
{
	if (token.word_sym == symbol::ifsym)
	{
		next();
		condiState();
	//	cout << "this is a if_condition statement" << endl;
	}
	else if (token.word_sym == symbol::dosym)
	{
		next();
		doLoop();
		if (token.word_sym != symbol::semicolon)
		{
			error();
			cout << "do-whileѭ����ȱ�ٷֺ�" << endl;
		}
		next();
	//	cout << "this is a do_while_loop statement" << endl;
	}
	else if (token.word_sym == symbol::forsym)
	{
		next();
		forLoop();
	//	cout << "this is a for_loop statement" << endl;
	}
	else if (token.word_sym == symbol::lbrac)
	{
		next();
		stateList();
	}
	else if (token.word_sym == symbol::scanfsym)
	{
		next();
		readState();
		if (token.word_sym != symbol::semicolon)
		{
			error(); cout << "597" << endl;
		}
		next();
	}
	else if (token.word_sym == symbol::printfsym)
	{
		next();
		writeState();
		if (token.word_sym != symbol::semicolon)
		{
			error(); cout << "607" << endl;
		}
		next();
	}
	else if (token.word_sym == symbol::returnsym)
	{
		next();
		if (token.word_sym == symbol::semicolon)
		{
			next();
			return;
		}
		if (token.word_sym != symbol::lparen)
		{
			error();
			cout << "���������ȱ��������" << endl;
		}
		next();
		expresstion();
		if (token.word_sym != symbol::rparen)
		{
			error(); cout << "627" << endl;
		}
		next();
		cout << token.name << endl;
		if (token.word_sym != symbol::semicolon)
		{
			error(); cout << "632" << endl;
		}

		//next();
	}
	else if (token.word_sym == symbol::semicolon)
	{
		next();
	//	cout << "this is an empty statement" << endl;
	}
	else if (token.word_sym == symbol::ident)
	{
		string name = token.name;
		next();
		if (token.word_sym == symbol::becomes||token.word_sym==symbol::lsquare)
		{
			if (!queryIdent(name))
				cout << "the ident did not defined" << endl;
			assignState();
	//		cout << "this is a assign statement" << endl;
		}
		else if (token.word_sym == symbol::lparen)
		{
			if (!queryFunc(name))
			{
				cout << "can not find the function in the function list" << endl;
			}
			next();
			/*vector<wordType>* para = funcCallState();
			Signary* tmp = globSig->funcList[name];
			cout << name << para->size() << endl;
			tmp->funCall(para);*/
	//		cout << "this is a function call statement" << endl;
		}
		else
		{
			error(); cout << "669" << endl;
		}
		if (token.word_sym == symbol::semicolon)
		{
			next();
		}
		else
		{
			error(); cout << "677" << endl;
		}
	}
}
void Grammer::condiState()
{
	if (token.word_sym != symbol::lparen)
	{
		error(); cout << "684" << endl;
	}
	next();
	condition();
	if (token.word_sym != symbol::rparen)
	{
		error(); cout << "691" << endl;
	}
	next();
	statement();
	if (token.word_sym == symbol::elsesym)
	{
		next();
		statement();
	}
}
void Grammer::condition()
{
	expresstion();
	set<symbol> relaOper = {
		symbol::leq,
		symbol::less,
		symbol::geq,
		symbol::gtr,
		symbol::equal,
		symbol::neq
	};
	if (relaOper.find(token.word_sym)!=relaOper.end())
	{
		next();
		expresstion();
	}
}
void Grammer::doLoop()
{
	statement();
	if (token.word_sym != symbol::whilesym)
	{
		error(); cout << "723" << endl;
	}
	next();
	if (token.word_sym != symbol::lparen)
	{
		error(); cout << "727" << endl;
	}
	next();
	condition();
	if (token.word_sym != symbol::rparen)
	{
		error(); cout << "733" << endl;
	}
	next();
}
void Grammer::forLoop()
{
	string name="";
	if (token.word_sym != symbol::lparen)
	{
		error();
		cout << "for loop������ȱ��������" << endl;
	}
	next();
	/*if (curSignary->querySignary(name) == NULL)
	{
		if (globSig->queryGlobSignary(name) == NULL)
		{
			cout << "the ident int the for loop did not defined" << endl;
		}
	}*/
	if(!queryIdent(token.name))
		cout << "the ident in the for loop did not defined" << endl;
	if (token.word_sym != symbol::ident)
	{
		error();
		cout << "for loop��������ʼ�����ȱ�ٱ�ʶ��" << endl;
	}
	next();
	if (token.word_sym != symbol::becomes)
	{
		error();
		cout << "for loop��������ȱ�ٵȺ�" << endl;
	}
	next();
	expresstion();
	if (token.word_sym != symbol::semicolon)
	{
		error(); cout << "770" << endl;
	}
	next();
	condition();
	if (token.word_sym != symbol::semicolon)
	{
		error(); cout << "776" << endl;
	}
	next();
	if (!queryIdent(token.name))
		cout << "the ident in the for loop did not defined" << endl;
	if (token.word_sym != symbol::ident)
	{
		error(); cout << "783" << endl;
	}
	next();
	if (token.word_sym != symbol::becomes)
	{
		error(); cout << "788" << endl;
	}
	next();
	if (!queryIdent(token.name))
		cout << "the ident in the for loop did not defined" << endl;
	if (token.word_sym != symbol::ident)
	{
		error(); cout << "795" << endl;
	}
	next();
	if (token.word_sym != symbol::plus&&token.word_sym != symbol::minus)
	{
		error(); cout << "801" << endl;
	}
	next();
	if (token.word_sym != symbol::number || token.name == "0")
	{
		error(); cout << "805" << endl;
	}
	next();
	if (token.word_sym != symbol::rparen)
	{
		error(); cout << "810" << endl;
	}
	next();
	statement();
	if (token.word_sym != symbol::rbrac)
	{
		error();
		cout << "forѭ����ȱ���Ҵ�����" << endl;
	}
	next();
}
void Grammer::assignState()
{
	if (token.word_sym == symbol::becomes)
	{
		next();
		expresstion();
	}
	else
	{
		next();
		expresstion();
		if (token.word_sym != symbol::rsquare)
		{
			error(); cout << "834" << endl;
		}
		next();
		if (token.word_sym == symbol::becomes)
		{
			next();
			expresstion();
		}
	}
}
SignaryItem* Grammer::funcCallState()
{
	vector<SignaryItem*> para;
	if (token.word_sym == symbol::ident)
	{
		/*if (!queryFunc(token.name))
			cout << "the function did not defined" << endl;*/
		para=valueParaList();
		Signary* tmp = globSig->funcList[token.name];
		//cout << name << para->size() << endl;
		tmp->funCall(para);
		if (token.word_sym != symbol::rparen)
		{
			error();
			cout << "�����������ȱ��������" << endl;
		}
		next();
	}
	else if (token.word_sym == symbol::rparen)
	{
		next();
		return NULL;
	}
	else
	{
		error(); cout << "868" << endl;
		return NULL;
	}
}
vector<SignaryItem*> Grammer::valueParaList()
{
	vector<SignaryItem*> para = vector<SignaryItem*>();
	SignaryItem* tmp=expresstion();
	para.push_back(tmp);
	while (token.word_sym == symbol::comma)
	{
		next();
		tmp=expresstion();
		para.push_back(tmp);
	}
	return para;
}
void Grammer::readState()
{
	if (token.word_sym != symbol::lparen)
	{
		error(); cout << "902" << endl;
	}
	next();
	if (!queryIdent(token.name))
		cout << "the ident in the read statement did not defined" << endl;
	if (token.word_sym != symbol::ident)
	{
		error(); cout << "909" << endl;
	}
	next();
	while (token.word_sym == symbol::comma)
	{
		next();
		if (!queryIdent(token.name))
			cout << "the ident in the read statement did not defined" << endl;
		if (token.word_sym != symbol::ident)
		{
			error(); cout << "919" << endl;
		}
		next();
	}
	if (token.word_sym != symbol::rparen)
	{
		error();
		cout << "�������ȱ����С����" << endl;
	}
	next();
//	cout << "this is a read statement" << endl;
}
void Grammer::writeState()
{
	if (token.word_sym != symbol::lparen)
	{
		error(); cout << "935" << endl;
	}
	next();
	if (token.word_sym == symbol::strConst)
	{
		next();
		if (token.word_sym == symbol::comma)
		{
			next();
			expresstion();
		}
		if (token.word_sym != symbol::rparen)
		{
			error(); cout << "948" << endl;
		}
		next();
	}
	else
	{
		expresstion();
		if (token.word_sym != symbol::rparen)
		{
			error(); cout << "957" << endl;
		}
		next();
	}
//	cout << "this is a write statement" << endl;
}
void Grammer::retState()
{
	if (token.word_sym != symbol::lparen)
	{
		error(); cout << "967" << endl;
	}
	next();
	expresstion();
	if (token.word_sym != symbol::rparen)
	{
		error(); cout << "973" << endl;
	}
	next();
}
wordType Grammer::expresstion()
{
	wordType wt;
	if (token.word_sym == symbol::plus || token.word_sym == symbol::minus)
	{
		next();
	}
	wt=itemDef();
	while (token.word_sym == symbol::plus || token.word_sym == symbol::minus)
	{
		next();
		itemDef();
	}
	return wt;
}
wordType Grammer::itemDef()
{
	wordType wt;
	wt=factorDef();
	while (token.word_sym == symbol::times || token.word_sym == symbol::divison)
	{
		next();
		factorDef();
	}
	return wt;
}
wordType Grammer::factorDef()
{
	wordType wt; string name=token.name;
	if (token.word_sym == symbol::ident)
	{
		SignaryItem* tmp=curSignary->querySignary(name);
		if (tmp == NULL)
		{
			tmp = globSig->queryGlobSignary(name);
			if (tmp == NULL)
				cout << "the ident isn't defined" << name << endl;
			else
				wt = tmp->wt;
			//next();
			/*if (token.word_sym != symbol::lparen)
			{
				error(); cout << "1021" << endl;
			}
			next();*/
			//cout << "cannot find the function" <<name<< endl;
		}
		else
			wt = tmp->wt;
		string name = token.name;
		if (!queryIdent(token.name))
			cout << "the ident did not defined" << endl;
		next();
		if (token.word_sym == symbol::lparen)
		{
			if (queryFunc(name))
			{
				if (globSig->sigGlobTable[name]->wt == wordType::voidTyp)
				{
					cout << "function without return value cannot be a factor" << endl;
				}
			}
			else
			{
				cout << "the function did not defined" << name << endl;
			}
			next();
			//vector<wordType>* para=funcCallState();
			//Signary* tmp = globSig->funcList[name];
			////cout << name << para->size() << endl;
			//tmp->funCall(para);
			next();
		}
		else if (token.word_sym == symbol::lsquare)
		{
			next();
			expresstion();
			if (token.word_sym != symbol::rsquare)
			{
				error(); cout << "1049" << endl;
			}
			next();
		}
	}
	else if (token.word_sym == symbol::charConst||token.word_sym==symbol::number)
	{
		if (token.word_sym == symbol::charConst)
			wt = wordType::charTyp;
		else
			wt = wordType::intTyp;
		next();
	}
	else if (token.word_sym == symbol::lparen)
	{
		SignaryItem* tmp=globSig->queryGlobSignary(name);
		wt = tmp->wt;
		next();
		expresstion();
		if (token.word_sym != symbol::rparen)
		{
			error(); cout << "1070" << endl;
		}
		next();
	}
	else if (token.word_sym == symbol::plus || token.word_sym == symbol::minus)
	{
		wt = wordType::intTyp;
		next();
		if (token.word_sym != symbol::number)
		{
			error(); cout << "1080" << endl;
		}
		next();
	}
	else
	{
		error(); cout << "1086" << endl;
	}
	return wt;
}
void Grammer::printSignary()
{
	cout << "print global signary" << endl;
	globSig->printGlobSig();
}
bool Grammer::funcEnterGlob(string name,wordType wt)
{
	funcNum++;
	//cout << "function"<<funcNum<< " name=" << name << endl;
	map<string,Signary*>::iterator sigTmp = globSig->funcList.find(name);
	if (sigTmp == globSig->funcList.end())
	{
		globSig->funcList[name] = new Signary(name);
		globSig->enterGlobSignary(name, wordKind::functionKind, wt, 4, 0, NULL);
		curSignary = globSig->funcList[name];
		return true;
	}
	else
		return false;
}
bool Grammer::queryIdent(string name)
{
	if (curSignary->querySignary(name) == NULL)
	{
		if (globSig->queryGlobSignary(name) == NULL)
		{
			return false;
		}
	}
	return true;
}
bool Grammer::queryFunc(string name)
{
	map<string, Signary*>::iterator tmp= globSig->funcList.find(name);
	if (tmp == globSig->funcList.end())
	{
		map<string, Signary*>::iterator it;
		//string name = it->first;
		cout << name << "can not find int the function list" << endl;
		for (it = globSig->funcList.begin(); it != globSig->funcList.end(); it++)
		{
			Signary* sig = it->second;
			cout << it->first << endl;
			cout << sig->name << endl;
			//sig->printSig();
			cout << endl;
		}
		return false;
	}
	return true;
}