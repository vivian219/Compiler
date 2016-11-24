#include "word.h"
#include <string>
#include<iostream>
#include<sstream>
string inttoString(int num)
{
	stringstream ss;
	ss << num;
	return ss.str();
}
word::word(symbol sym, string _name)
{
	word_sym = sym;
	//printSym(sym);
	name = _name;
	//cout << " " + name << endl;

}
word::word(symbol sym, int num)
{
	word_sym = sym;
	//printSym(sym);
	name = inttoString(num);
	//cout << " ";
	//cout << num<<endl;
	value = num;
}
 void word:: printSym(symbol sym)
{
	 if (sym == symbol::plus)
		 cout << "plus";
	 else if (sym == symbol::minus)
		 cout << "minus";
	 else if (sym == symbol::times)
		 cout << "times";
	 else if (sym == symbol::divison)
		 cout << "division";
	 else if (sym == symbol::becomes)
		 cout << "becomes";
	 else if (sym == symbol::less)
		 cout << "less";
	 else if (sym == symbol::leq)
		 cout << "leq";
	 else if (sym == symbol::gtr)
		 cout << "gtr";
	 else if (sym == symbol::geq)
		 cout << "geq";
	 else if (sym == symbol::equal)
		 cout << "equal";
	 else if (sym == symbol::neq)
		 cout << "neq";
	 else if (sym == symbol::lparen)
		 cout << "lparen";
	 else if (sym == symbol::rparen)
		 cout << "rparen";
	 else if (sym == symbol::lsquare)
		 cout << "lsquare";
	 else if (sym == symbol::rsquare)
		 cout << "rsquare";
	 else if (sym == symbol::lbrac)
		 cout << "lbrac";
	 else if (sym == symbol::rbrac)
		 cout << "rbrac";
	 else if (sym == symbol::comma)
		 cout << "comma";
	 else if (sym == symbol::semicolon)
		 cout << "semicolon";
	 else if (sym == symbol::quote)
		 cout << "quote";
	 else if (sym == symbol::dquote)
		 cout << "dquote";
	 else if (sym == symbol::constsym)
		 cout << "constsym";
	 else if (sym == symbol::intsym)
		 cout << "intsym";
	 else if (sym == symbol::charsym)
		 cout << "charsym";
	 else if (sym == symbol::voidsym)
		 cout << "voidsym";
	 else if (sym == symbol::mainsym)
		 cout << "mainsym";
	 else if (sym == symbol::ifsym)
		 cout << "ifsym";
	 else if (sym == symbol::elsesym)
		 cout << "elsesym";
	 else if (sym == symbol::dosym)
		 cout << "dosym";
	 else if (sym == symbol::whilesym)
		 cout << "whilesym";
	 else if (sym == symbol::forsym)
		 cout << "forsym";
	 else if (sym == symbol::scanfsym)
		 cout << "scanfsym";
	 else if (sym == symbol::printfsym)
		 cout << "printfsym";
	 else if (sym == symbol::ident)
		 cout << "ident";
	 else if (sym == symbol::number)
		 cout << "number";
	 else if (sym == symbol::charConst)
		 cout << "charConst";
	 else if (sym == symbol::strConst)
		 cout << "strConst";
	 else if (sym == symbol::returnsym)
		 cout << "returnsym";
}

 bool word::isEof() {
	 if (word_sym == symbol::eofsym)
		 return true;
	 return false;
 }