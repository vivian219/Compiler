#include <iostream>
#include <map>
#include <sstream>//output
#include "lexer.h"
#include"grammer.h"
using namespace std;

Lexer::Lexer(string filename)
{
	iniReserTable();
	inputFile.open(filename);
	inputFile.getline(lBuffer, 1024);
	ll = strlen(lBuffer);
	cc = 0;
	getchar();
}
void Lexer::iniReserTable() {
	reserved["+"] = symbol::plus;
	reserved["-"] = symbol::minus;
	reserved["*"] = symbol::times;
	reserved["/"] = symbol::divison;
	reserved["="] = symbol::becomes;
	reserved["<"] = symbol::less;
	reserved["<="] = symbol::leq;
	reserved[">"] = symbol::gtr;
	reserved[">="] = symbol::geq;
	reserved["=="] = symbol::equal;
	reserved["!="] = symbol::neq;
	reserved["("] = symbol::lparen;
	reserved[")"] = symbol::rparen;
	reserved["["] = symbol::lsquare;
	reserved["]"] = symbol::rsquare;
	reserved["{"] = symbol::lbrac;
	reserved["}"] = symbol::rbrac;
	reserved[","] = symbol::comma;
	reserved[";"] = symbol::semicolon;
	reserved["'"] = symbol::quote;
	reserved["\""] = symbol::dquote;
	reserved["const"] = symbol::constsym;
	reserved["int"] = symbol::intsym;
	reserved["char"] = symbol::charsym;
	reserved["void"] = symbol::voidsym;
	reserved["main"] = symbol::mainsym;
	reserved["if"] = symbol::ifsym;
	reserved["else"] = symbol::elsesym;
	reserved["do"] = symbol::dosym;
	reserved["while"] = symbol::whilesym;
	reserved["for"] = symbol::forsym;
	reserved["scanf"] = symbol::scanfsym;
	reserved["printf"] = symbol::printfsym;
	reserved["return"] = symbol::returnsym;
}
void Lexer::getchar()
{
	if (cc == ll)
	{
		if (inputFile.eof())
		{
			ch = EOF;
			return;
		}
		inputFile.getline(lBuffer, 1024);
		ll = strlen(lBuffer);
		cc = 0;
		ch = lBuffer[cc];
		cc++;
		lCounter++;
	}
	else
	{
		ch = lBuffer[cc];
		cc++;
	}
}
word Lexer::getword()
{
	wCounter++;
//	cout << wCounter << " ";
	// space and tab
	while( (ch == ' ' || ch == '\t')||(ch=='\n'||ch==0))
		getchar();
	if (isalpha(ch)||ch=='_')//th beginning of ident must be an alpha
	{
		words.push_back(ch);
		getchar();
		while (isalnum(ch)||ch=='_')
		{
			words.push_back(ch);
			getchar();
		}
		//get the words
		string words_tmp(words.begin(), words.end());
		//check if the words we get is a reserved word
		map<string, symbol>::iterator loca = reserved.find(words_tmp);
		words.clear();
		if (loca == reserved.end())//the word is a ident
		{
			sym = symbol::ident;
			return word(sym, words_tmp);
		}
		else
		{
			sym = reserved[words_tmp];
			return word(sym, words_tmp);
		}
	}
	else if (isdigit(ch))
	{
		sym = symbol::number;
		int num = 0;
		if (ch == '0')
		{
			getchar();
			if (isdigit(ch))
			{
				error();
			}
			return word(sym, 0);
		}
		while (isdigit(ch))
		{
			num = num * 10 + ch - '0';
			getchar();
		}
		return word(sym, num);
	}
	else if (ch == '\'')
	{
		sym = symbol::charConst;
		getchar();
		char c = ch;
		getchar();
		getchar();
		string str(1, c);
		bool flag = false;
		if (str == "+" || str == "-")
			flag = true;
		else if (str == "*" || str == "/")
			flag = true;
		else if (isalnum(c))
			flag = true;
		else
			error();
		return word(sym, str);
	}
	else if (ch=='"')
	{
		sym = symbol::strConst;
		getchar();
		while (ch != '"')
		{
			words.push_back(ch);
			getchar();
		}
		getchar();
		string str(words.begin(), words.end());
		words.clear();
		return word(sym, str);
	}
	else if (ch == '<')
	{
		getchar();
		if (ch == '=')
		{
			getchar();
			sym = symbol::leq;
			return word(sym, "<=");
		}
		else
		{
			sym = symbol::less;
			return word(sym, "<");
		}
	}
	else if (ch == '>')
	{
		getchar();
		if (ch == '=')
		{
			getchar();
			sym = symbol::geq;
			return word(sym, ">=");
		}
		else
		{
			sym = symbol::gtr;
			return word(sym, ">");
		}
	}
	else if (ch == '=')
	{
		getchar();
		if (ch == '=')
		{
			sym = symbol::equal;
			getchar();
			return word(sym, "==");
		}
		else
		{
			sym = symbol::becomes;
			return word(sym, "=");
		}
	}
	else if (ch == '!')
	{
		getchar();
		if (ch == '=')
		{
			sym = symbol::neq;
			getchar();
			return word(sym, "!=");
		}
		else
		{
			cout << "Invalid:" << ch << endl;
			system("pause");
			//error;
		}
	}
	else if(ch==EOF)
	{
		sym = symbol::eofsym;
		return word(sym, "EOF");
	}
	else
	{
		string s(1,ch);
		map<string, symbol>::iterator tmp=reserved.find(s);
		if (tmp == reserved.end())
		{
			//error
			cout << "Reserved Invalid:" << ch << endl;
			system("pause");
			exit(0);
		}
		else
		{
			sym = reserved[s];
			getchar();
			return word(sym, s);
		}
	}
}
void Lexer::back()
{

}
