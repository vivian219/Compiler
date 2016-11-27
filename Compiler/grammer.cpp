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
			retFuncDef(get(name));
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
			funcEnterGlob(name, wt);
			next();
			retFuncDef(get(name));
		}
		else if (token.word_sym == symbol::voidsym)
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

			funcEnterGlob(name, wordType::voidTyp);
			next();
			voidFuncDef(get(name));
		}
		cout << token.name << endl;
	}
	//main function begin.
	if (token.word_sym == symbol::mainsym)
	{
		//enter "main" into globalSignary.
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
			symbol op = token.word_sym; bool ifMinus=false;
			if (token.word_sym == symbol::plus || token.word_sym == symbol::minus)
			{
				if (token.word_sym == symbol::minus)
					ifMinus = true;
				next();
			}
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
				cout << "变量定义中标识符类型后无标识符" << endl;
			}
			next();
			if (token.word_sym == symbol::lparen)
			{
				funcEnterGlob(name, wt);
				retFuncDef(get(name));
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
/*
＜变量说明＞  ::= ＜变量定义＞;{＜变量定义＞;}
＜变量定义＞  ::= ＜类型标识符＞(＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’){,(＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’) }
*/
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

/*
＜有返回值函数定义＞  ::=  ＜声明头部＞‘(’＜参数＞‘)’ ‘{’＜复合语句＞‘}’
＜声明头部＞   ::=  int＜标识符＞|char＜标识符＞
*/
void Grammer::retFuncDef(SignaryItem* func)
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
		MCode.insertMI(MIType::BEIGN, func, NULL, NULL);
		next();
		compState();
		if (token.word_sym != symbol::rbrac)
		{
			error(); cout << "404" << endl;
		}
		MCode.insertMI(MIType::END, func, NULL, NULL);
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

/*
＜参数＞    ::= ＜参数表＞
＜参数表＞  ::=  ＜类型标识符＞＜标识符＞{,＜类型标识符＞＜标识符＞}| ＜空＞
*/
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
/*
＜无返回值函数定义＞::= void＜标识符＞‘(’＜参数＞‘)’‘{’＜复合语句＞‘}’
*/
void Grammer::voidFuncDef(SignaryItem* func)
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
	MCode.insertMI(MIType::BEIGN, func, NULL, NULL);
	next();
	compState();
	MCode.insertMI(MIType::END, func, NULL, NULL);
	if (token.word_sym != symbol::rbrac)
	{
		error(); cout << "488" << endl;
	}
	next();
	//cout << "this is a function without return statement" << endl;
}

/*
＜主函数＞::= void main‘(’‘)’ ‘{’＜复合语句＞‘}’
*/
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

/*
＜复合语句＞   ::=  ［＜常量说明＞］［＜变量说明＞］＜语句列＞
*/
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

/*
＜语句列＞   ::=｛＜语句＞｝
*/
void Grammer::stateList()
{
	while (true)
	{
		statement();
		if (token.word_sym == symbol::rbrac)
			break;
	}
}

/*
＜语句＞ ::= ＜条件语句＞｜＜循环语句＞｜‘{’＜语句列＞‘}’｜＜有返回值函数调用语句＞;  |＜无返回值函数调用语句＞;｜＜赋值语句＞;｜＜读语句＞;｜＜写语句＞;｜＜空＞;｜＜返回语句＞;
*/
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
			cout << "返回语句中缺少左括号" << endl;
		}
		next();
		expresstion();
		if (token.word_sym != symbol::rparen)
		{
			error(); cout << "627" << endl;
		}
		next();
		//cout << token.name << endl;
		if (token.word_sym != symbol::semicolon)
		{
			error(); cout << "632" << endl;
		}
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
			SignaryItem* _ident = get(name);
			assignState(_ident);
	//		cout << "this is a assign statement" << endl;
		}
		else if (token.word_sym == symbol::lparen)
		{
			if (!queryFunc(name))
			{
				cout << "can not find the function in the function list" << endl;
			}
			next();
			funcCallState(get(name));
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
/*
＜条件语句＞  ::=  if ‘(’＜条件＞‘)’＜语句＞［else＜语句＞］
*/
void Grammer::condiState()
{
	/* 
		 condition (else_label, false) #表达式为假跳转到else_label
			true_statement ();
			JUMP end_if_label;
else_label:
			false_statement ();
end_if_label:

	*/
	SignaryItem* end_if_label= globSig->genLabel();
	SignaryItem* else_label = globSig->genLabel();
	if (token.word_sym != symbol::lparen)
	{
		error(); cout << "684" << endl;
	}
	next();
	condition(else_label,false);
	if (token.word_sym != symbol::rparen)
	{
		error(); cout << "691" << endl;
	}
	next();
	statement();
	MCode.insertMI(MIType::JUMP, end_if_label,NULL,NULL);
	MCode.insertMI(MIType::SETL, else_label, NULL, NULL);
	if (token.word_sym == symbol::elsesym)
	{
		next();
		statement();
	}
	MCode.insertMI(MIType::SETL, end_if_label, NULL, NULL);
}

/*
＜条件＞      ::=  ＜表达式＞＜关系运算符＞＜表达式＞｜＜表达式＞
＜关系运算符＞ ::=  <｜<=｜>｜>=｜!=｜==
*/
void Grammer::condition(SignaryItem* _label,bool ifJ)
{
	SignaryItem *src1, *tmp;
	src1 = expresstion();
	set<symbol> relaOper = {
		symbol::leq,
		symbol::less,
		symbol::geq,
		symbol::gtr,
		symbol::equal,
		symbol::neq
	};
//	expr = expresstion(); BXX dst,src1,src2
	tmp = curSignary->genTemp(wordType::intTyp, wordKind::constKind);
	tmp->intValue = 0;
	if (relaOper.find(token.word_sym)!=relaOper.end())
	{
		MIType m;
		if (token.word_sym == symbol::leq)
		{
			if (ifJ)
				m = MIType::BLE;
			else
				m = MIType::BGR;
		}
		else if (token.word_sym == symbol::less)
		{
			if (ifJ)
				m = MIType::BLS;
			else
				m = MIType::BGE;
		}
		else if (token.word_sym == symbol::geq)
		{
			if (ifJ)
				m = MIType::BGE;
			else
				m = MIType::BLS;
		}
		else if (token.word_sym == symbol::gtr)
		{
			if (ifJ)
				m = MIType::BGR;
			else
				m = MIType::BLE;
		}
		else if (token.word_sym == symbol::equal)
		{
			if (ifJ)
				m = MIType::BEQ;
			else
				m = MIType::BNE;
		}
		else if(token.word_sym==symbol::neq)
		{
			if (ifJ)
				m = MIType::BNE;
			else
				m = MIType::BEQ;
		}
		next();
		SignaryItem* src2 = expresstion();
		MCode.insertMI(m, _label, src1, src2);
	}
	else
	{
		if (ifJ)
			MCode.insertMI(MIType::BNE, _label, src1, tmp);
		else
			MCode.insertMI(MIType::BEQ, _label, src1, tmp);
	}
}

/*
do＜语句＞while ‘(’＜条件＞‘)’
loop:      statement ();
condition (loop, false);
*/
void Grammer::doLoop()
{
	SignaryItem* do_label= globSig->genLabel();
	MCode.insertMI(MIType::SETL, do_label, NULL, NULL);
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
	condition(do_label,true);
	if (token.word_sym != symbol::rparen)
	{
		error(); cout << "733" << endl;
	}
	next();
}

/*
for‘(’＜标识符＞＝＜表达式＞;＜条件＞;＜标识符＞＝＜标识符＞(+|-)＜步长＞‘)’＜语句＞
variable = experssion ();
loop:
condition ( end_loop, false);
statement();
add or sub variable;
JUMP loop;
end_loop:

*/
void Grammer::forLoop()
{
	string name="";
	if (token.word_sym != symbol::lparen)
	{
		error();
		cout << "for loop的条件缺少左括号" << endl;
	}
	next();
	SignaryItem* var1;
	SignaryItem* var2;
	SignaryItem* end_loop_label = globSig->genLabel();
	SignaryItem* loop_label = globSig->genLabel();
	MCode.insertMI(MIType::SETL, loop_label, NULL, NULL);
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
	{
		error(); cout << "770" << endl;
	}
	next();
	condition(end_loop_label,false);
	if (token.word_sym != symbol::semicolon)
	{
		error(); cout << "776" << endl;
	}
	next();
	//var1 <标识符> = var2 <标识符> +|- step
	var1 = get(token.name);
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
	var2 = get(token.name);
	if (!queryIdent(token.name))
		cout << "the ident in the for loop did not defined" << endl;
	if (token.word_sym != symbol::ident)
	{
		error(); cout << "795" << endl;
	}
	next();
	bool ifAdd = false;
	if (token.word_sym != symbol::plus&&token.word_sym != symbol::minus)
	{
		error(); cout << "801" << endl;
	}
	else if (token.word_sym == symbol::plus)
		ifAdd = true;
	next();
	SignaryItem* step=curSignary->genTemp(wordType::intTyp,wordKind::TempConKind);
	step->intValue = token.value;
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
	if (ifAdd)
		MCode.insertMI(MIType::ADD, var1, var2, step);
	else
		MCode.insertMI(MIType::SUB, var1, var2, step);
	if (token.word_sym != symbol::rbrac)
	{
		error();
		cout << "for循环中缺少右大括号" << endl;
	}
	MCode.insertMI(MIType::JUMP, loop_label, NULL, NULL);
	MCode.insertMI(MIType::SETL, end_loop_label, NULL, NULL);
	next();
}

/*
＜赋值语句> ::=＜标识符＞＝＜表达式＞|＜标识符＞‘[’＜表达式＞‘]’=＜表达式＞
*/
void Grammer::assignState(SignaryItem* _ident)
{
//	SignaryItem* des = _ident;
	SignaryItem* src1=new SignaryItem();
	SignaryItem* src2= new SignaryItem();
	if (token.word_sym == symbol::becomes)
	{
		next();
		src1=expresstion();
		MIType m = MIType::ASSIGN;
		MCode.insertMI(m,_ident,src1,NULL);
	}
	else
	{
		next();
		src1=expresstion();
		if (token.word_sym != symbol::rsquare)
		{
			error(); cout << "834" << endl;
		}
		next();
		if (token.word_sym == symbol::becomes)
		{
			next();
			src2=expresstion();
		}
		MIType m = MIType::ARRASS;
		MCode.insertMI(m, src2, _ident, src1);
	}
}
/*
＜有返回值函数调用语句＞ ::= ＜标识符＞‘(’＜值参数表＞‘)’
＜无返回值函数调用语句＞ ::= ＜标识符＞‘(’＜值参数表＞‘)’
*/
SignaryItem* Grammer::funcCallState(SignaryItem* func)
{
	vector<SignaryItem*> para;
	if (token.word_sym == symbol::ident)
	{
		/*if (!queryFunc(token.name))
			cout << "the function did not defined" << endl;*/
		string funName = func->name;
		Signary* tmp = globSig->funcList[funName];
		para = valueParaList();
		vector<SignaryItem*>::iterator tmpPara;
		for (tmpPara = para.begin(); tmpPara != para.end(); tmpPara++)
		{
			MCode.insertMI(MIType::PUSH, *tmpPara, NULL, NULL);
		}
		//cout << name << para->size() << endl;
		tmp->funCall(para);
		
		if (token.word_sym != symbol::rparen)
		{
			error();
			cout << "函数调用语句缺少右括号" << endl;
		}
		next();
	}
	else if (token.word_sym == symbol::rparen)
	{
		next();
	}
	else
	{
		error(); cout << "868" << endl;
		return NULL;
	}
	MCode.insertMI(MIType::CALL, func, NULL, NULL);

	if (func->wt == wordType::voidTyp) {
		return NULL;
	}
	else {
		SignaryItem* tempRet = curSignary->genTemp(func->wt, wordKind::TempVarKind);
		MCode.insertMI(MIType::FUNCGET, tempRet, NULL, NULL);
		return tempRet;
	}
}
/*
＜值参数表＞::= ＜表达式＞{,＜表达式＞}｜＜空＞
*/
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
/*
＜读语句＞::=  scanf ‘(’＜标识符＞{,＜标识符＞}‘)’
*/
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
	MCode.insertMI(MIType::SCAN, get(token.name), NULL,NULL);
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
		MCode.insertMI(MIType::SCAN, get(token.name), NULL, NULL);
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

/*
＜写语句＞::= printf‘(’＜字符串＞,＜表达式＞‘)’|printf ‘(’＜字符串＞‘)’|printf ‘(’＜表达式＞‘)’
*/
void Grammer::writeState()
{
	if (token.word_sym != symbol::lparen)
	{
		error(); cout << "935" << endl;
	}
	next();
	if (token.word_sym == symbol::strConst)
	{
		//SignaryItem* strTmp=curSignary->genTemp(wordType::)
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

/*
＜返回语句＞::=  return[‘(’＜表达式＞‘)’]
*/
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
/*
＜表达式＞::= ［＋｜－］＜项＞{＜加法运算符＞＜项＞}
＜加法运算符＞ ::= +｜-
*/
SignaryItem* Grammer::expresstion()
{
	SignaryItem *firstTmp; bool ifMinus = false;
	if (token.word_sym == symbol::plus || token.word_sym == symbol::minus)
	{
		if (token.word_sym == symbol::minus)
			ifMinus = true;
		next();
	}
	firstTmp=itemDef();
	while (token.word_sym == symbol::plus || token.word_sym == symbol::minus)
	{
		MIType m = (token.word_sym == symbol::minus) ? MIType::SUB : MIType::ADD;
		SignaryItem* resultTmp = curSignary->genTemp(wordType::intTyp, wordKind::varKind);
		SignaryItem* secondTmp;
		next();
		secondTmp=itemDef();
		MCode.insertMI(m, resultTmp, firstTmp, secondTmp);
		firstTmp=resultTmp;
	}
	if (ifMinus)
		MCode.insertMI(MIType::NEG, firstTmp, firstTmp, NULL);
	return firstTmp;
}
/*
＜项＞::= ＜因子＞{＜乘法运算符＞＜因子＞}
*/
SignaryItem* Grammer::itemDef()
{
	SignaryItem* firstTmp;
	firstTmp=factorDef();
	while (token.word_sym == symbol::times || token.word_sym == symbol::divison)
	{
		MIType t = (token.word_sym == symbol::divison) ? MIType::DIVISION : MULT;
		SignaryItem* resultTmp=curSignary->genTemp(firstTmp->wt, wordKind::varKind);
		next();
		SignaryItem* secondTmp=factorDef();
		MCode.insertMI(t, resultTmp, firstTmp, secondTmp);
		firstTmp = resultTmp;
	}
	return firstTmp;
}
/*
＜因子＞::= ＜标识符＞｜＜标识符＞‘[’＜表达式＞‘]’｜＜整数＞|＜字符＞｜＜有返回值函数调用语句＞|‘(’＜表达式＞‘)’
*/
SignaryItem* Grammer::factorDef()
{
	string name = token.name;
	SignaryItem* tmp = get(name);
	if (token.word_sym == symbol::ident)
	{
		if (tmp == NULL)
		{
				cout << "the ident isn't defined" << name << endl;
		}
		string name = token.name;
		/*if (!queryIdent(token.name))
			cout << "the ident did not defined" << endl;*/
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
			//SignaryItem* para=funcCallState(get(name));
			//Signary* tmp = globSig->funcList[name];
			////cout << name << para->size() << endl;
			//tmp->funCall(para);
			tmp=funcCallState(get(name));
			//next();
		}
		else if (token.word_sym == symbol::lsquare)
		{
			next();
			SignaryItem* loc=expresstion();
			if (token.word_sym != symbol::rsquare)
			{
				error(); cout << "1049" << endl;
			}
			SignaryItem* res=new SignaryItem();
			MCode.insertMI(MIType::ARRGET, res, tmp, loc);
			tmp = res;
			next();
		}
	}
	else if (token.word_sym == symbol::charConst||token.word_sym==symbol::number)
	{
		if (token.word_sym == symbol::number)
		{
			tmp = curSignary->genTemp(wordType::intTyp, wordKind::TempConKind);
			tmp->intValue = token.value;
		}
		else
		{
			tmp = curSignary->genTemp(wordType::charTyp, wordKind::TempConKind);
			tmp->charValue = token.name.at(0);
		}
		next();
	}
	else if (token.word_sym == symbol::lparen)
	{
		next();
		tmp=expresstion();
		if (token.word_sym != symbol::rparen)
		{
			error(); cout << "1070" << endl;
		}
		next();
	}
	else if (token.word_sym == symbol::plus || token.word_sym == symbol::minus)
	{
		bool ifMinus=false;
		if (token.word_sym == symbol::minus)
		{
			ifMinus = true;
		}
		next();
		if (token.word_sym != symbol::number)
		{
			error(); cout << "1080" << endl;
		}
		MCode.insertMI(MIType::NEG, get(token.name), get(token.name), NULL);
		tmp = curSignary->genTemp(wordType::intTyp, wordKind::TempConKind);
		tmp->intValue = token.value;
		next();
	}
	else
	{
		error(); cout << "1086" << endl;
	}
	return tmp;
}
void Grammer::printSignary()
{
	cout << "print global signary" << endl;
	globSig->printGlobSig();
}

//Enter function into globalSignary.
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

// Check whether the function name exists.
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

//Get the name's SignaryItem from Sinary, or globalSignary.
SignaryItem* Grammer::get(string name)
{

	if (curSignary->querySignary(name) == NULL)
	{
		if (globSig->queryGlobSignary(name) == NULL)
			return NULL;
		else
			return (globSig->queryGlobSignary(name));
	}
	else
		return (curSignary->querySignary(name));
}
void Grammer::printMiddleCode()
{
	MCode.printMI();
}

//Translate middle code into mips code.
void Grammer::translate() {

}