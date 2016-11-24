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
			cout << "类型标识符后面无标识符" << endl;
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
				cout << "有返回值函数定义缺少函数名" << endl;
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
				cout << "无返回值函数定义缺少函数名" << endl;
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
			cout << "格式非法，常量声明结束没有加分号" << endl;
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
				cout << "格式非法，常量定义时缺少标识符" << endl;
			}
			name = token.name;
			next();
			if (token.word_sym != symbol::becomes)
			{
				error();
				cout << "常量定义时缺少等号" << endl;
			}
			next();
			symbol op = token.word_sym;
			if (token.word_sym == symbol::plus || token.word_sym == symbol::minus)
				next();
			if (token.word_sym != symbol::number)
			{
				error();
				cout << "定义int型常量时数字格式不正确" << endl;
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
				error();
			}
			next();
			if (token.word_sym != symbol::becomes)
			{
				error();
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
				error();
			}
			next();
			if (token.word_sym != symbol::comma)
				break;
		}
	}
	else
		error();
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
				cout << "变量定义中标识符类型后无标识符" << endl;
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
				cout << "数组下标不为整数" << endl;
				size = 10;
			}
			next();
			if (token.word_sym != symbol::rsquare)
			{
				error();
				cout << "数组定义中缺少右括号" << endl;
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
				cout << "变量定义中逗号后面缺少标识符" << endl;
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
			error();
		next();
		if (token.word_sym == symbol::rparen)
		{
			next();
		}
		else
		{
			paraList();
			if (token.word_sym != symbol::rparen)
				error();
			next();
		}
		if (token.word_sym != symbol::lbrac)
			error();
		next();
		compState();
		if (token.word_sym != symbol::rbrac)
			error();
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
			cout << "有返回值函数定义缺少函数名" << endl;
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
			cout << "函数定义参数列表缺少类型标识符" << endl;
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
			cout << "函数定义的参数列表缺少标识符" << endl;
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
		error();
	next();
	if (token.word_sym == symbol::rparen)
	{
		next();
	}
	else
	{
		paraList();
		if (token.word_sym != symbol::rparen)
			error();
		next();
	}
	if (token.word_sym != symbol::lbrac)
	{
		error();
	}
	next();
	compState();
	if (token.word_sym != symbol::rbrac)
		error();
	next();
	//cout << "this is a function without return statement" << endl;
}
void Grammer::mainFunc()
{
	if (token.word_sym != symbol::lparen)
		error();
	next();
	if (token.word_sym != symbol::rparen)
		error();
	next();
	if (token.word_sym != symbol::lbrac)
		error();
	next();
	compState();
	if (token.word_sym != symbol::rbrac)
		error();
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
				cout << "复合语句的变量声明没有标识符" << endl;
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
			cout << "do-while循环中缺少分号" << endl;
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
			error();
		next();
	}
	else if (token.word_sym == symbol::printfsym)
	{
		next();
		writeState();
		if (token.word_sym != symbol::semicolon)
			error();
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
			cout << "返回语句中缺少左括号" << endl;
		}
		next();
		expresstion();
		if (token.word_sym != symbol::rparen)
			error();
		next();
		if (token.word_sym != symbol::semicolon)
			error();
		next();
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
			next();
			funcCallState();
	//		cout << "this is a function call statement" << endl;
		}
		else
			error();
		if (token.word_sym == symbol::semicolon)
		{
			next();
		}
		else
			error();
	}
}
void Grammer::condiState()
{
	if (token.word_sym != symbol::lparen)
		error();
	next();
	condition();
	if (token.word_sym != symbol::rparen)
		error();
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
		error();
	}
	next();
	if (token.word_sym != symbol::lparen)
		error();
	next();
	condition();
	if (token.word_sym != symbol::rparen)
		error();
	next();
}
void Grammer::forLoop()
{
	string name="";
	if (token.word_sym != symbol::lparen)
	{
		error();
		cout << "for loop的条件缺少左括号" << endl;
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
		cout << "for loop的条件初始化语句缺少标识符" << endl;
	}
	next();
	if (token.word_sym != symbol::becomes)
	{
		error();
		cout << "for loop的条件中缺少等号" << endl;
	}
	next();
	expresstion();
	if (token.word_sym != symbol::semicolon)
		error();
	next();
	condition();
	if (token.word_sym != symbol::semicolon)
		error();
	next();
	if (!queryIdent(token.name))
		cout << "the ident in the for loop did not defined" << endl;
	if (token.word_sym != symbol::ident)
		error();
	next();
	if (token.word_sym != symbol::becomes)
		error();
	next();
	if (!queryIdent(token.name))
		cout << "the ident in the for loop did not defined" << endl;
	if (token.word_sym != symbol::ident)
		error();
	next();
	if (token.word_sym != symbol::plus&&token.word_sym != symbol::minus)
		error();
	next();
	if (token.word_sym != symbol::number || token.name == "0")
		error();
	next();
	if (token.word_sym != symbol::rparen)
		error();
	next();
	statement();
	if (token.word_sym != symbol::rbrac)
	{
		error();
		cout << "for循环中缺少右大括号" << endl;
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
			error();
		next();
		if (token.word_sym == symbol::becomes)
		{
			next();
			expresstion();
		}
	}
}
void Grammer::funcCallState()
{
	if (token.word_sym == symbol::ident)
	{
		if (!queryFunc(token.name))
			cout << "the function did not defined" << endl;
		valueParaList();
		if (token.word_sym != symbol::rparen)
		{
			error();
			cout << "函数调用语句缺少右括号" << endl;
		}
		next();
	}
	else if (token.word_sym == symbol::rparen)
		next();
	else
		error();
}
void Grammer::valueParaList()
{
	expresstion();
	while (token.word_sym == symbol::comma)
	{
		next();
		expresstion();
	}
}
void Grammer::readState()
{
	if (token.word_sym != symbol::lparen)
		error();
	next();
	if (!queryIdent(token.name))
		cout << "the ident in the read statement did not defined" << endl;
	if (token.word_sym != symbol::ident)
		error();
	next();
	while (token.word_sym == symbol::comma)
	{
		next();
		if (!queryIdent(token.name))
			cout << "the ident in the read statement did not defined" << endl;
		if (token.word_sym != symbol::ident)
			error();
		next();
	}
	if (token.word_sym != symbol::rparen)
	{
		error();
		cout << "读语句中缺少右小括号" << endl;
	}
	next();
//	cout << "this is a read statement" << endl;
}
void Grammer::writeState()
{
	if (token.word_sym != symbol::lparen)
		error();
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
			error();
		next();
	}
	else
	{
		expresstion();
		if (token.word_sym != symbol::rparen)
			error();
		next();
	}
//	cout << "this is a write statement" << endl;
}
void Grammer::retState()
{
	if (token.word_sym != symbol::lparen)
		error();
	next();
	expresstion();
	if (token.word_sym != symbol::rparen)
		error();
	next();
}
void Grammer::expresstion()
{
	if (token.word_sym == symbol::plus || token.word_sym == symbol::minus)
	{
		next();
	}
	itemDef();
	while (token.word_sym == symbol::plus || token.word_sym == symbol::minus)
	{
		next();
		itemDef();
	}
}
void Grammer::itemDef()
{
	factorDef();
	while (token.word_sym == symbol::times || token.word_sym == symbol::divison)
	{
		next();
		factorDef();
	}
}
void Grammer::factorDef()
{
	if (token.word_sym == symbol::ident)
	{
		if (!queryIdent(token.name))
			cout << "the ident did not defined" << endl;
		next();
		if (token.word_sym == symbol::lparen)
		{
			next();
			funcCallState();
		}
		else if (token.word_sym == symbol::lsquare)
		{
			next();
			expresstion();
			if (token.word_sym != symbol::rsquare)
				error();
			next();
		}
	}
	else if (token.word_sym == symbol::charConst||token.word_sym==symbol::number)
	{
		next();
	}
	else if (token.word_sym == symbol::lparen)
	{
		next();
		expresstion();
		if (token.word_sym != symbol::rparen)
			error();
		next();
	}
	else if (token.word_sym == symbol::plus || token.word_sym == symbol::minus)
	{
		next();
		if (token.word_sym != symbol::number)
			error();
		next();
	}
	else
		error();
}
void Grammer::printSignary()
{
	cout << "print global signary" << endl;
	globSig->printGlobSig();
}
bool Grammer::funcEnterGlob(string name,wordType wt)
{
	funcNum++;
	cout << "function"<<funcNum<< " name=" << name << endl;
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
		return false;
	return true;
}