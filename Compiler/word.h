#pragma once
#include <fstream>
using namespace std;
string inttoString(int num);

enum symbol {
	//words or number
	ident,//±êÊ¶·û
	number,//Êý×Ö
	//constant
	charConst,
	strConst,
	//operator
	plus,//+
	minus,//-
	times,//*
	divison,// /
	becomes,//=
	//comparison operator
	less,//<
	leq,//<=
	gtr,//>
	geq,//>=
	equal,//==
	neq,//!=
	//brackets
	lparen,//(
	rparen,//)
	lsquare,//[
	rsquare,//]
	lbrac,//{
	rbrac,//}
	//punctuation
	comma,//,
	semicolon,//;
	//quotation marks
	quote,//'
	dquote,//"
	//key words
	constsym,
	intsym,
	charsym,
	voidsym,
	mainsym,
	ifsym,
	elsesym,
	dosym,
	whilesym,
	forsym,
	scanfsym,
	printfsym,
	returnsym,
	//the end of the file
	eofsym
};
class word {
private:
	ofstream out;
public:
	string name;
	int value=0;
	symbol  word_sym;
	word(symbol sym,string name);
	word(symbol sym, int num);
	word() {}
	void printSym(symbol sym);
	bool isEof();
};