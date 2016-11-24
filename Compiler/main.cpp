#include "lexer.h"
#include <iostream>
#include"grammer.h"
using namespace std;
int main() {
	/*Lexer lexer = Lexer(string("input2.txt"));
	while (1)
	{
		word w=lexer.getword();
		if(w.isEof())
			break;
	}*/
//	Grammer g = Grammer(string("input2.txt"));
	Grammer g = Grammer(string("input2.txt"));
	g.prog();
	
	cout << "Finished" << endl;
	system("pause");
}