#pragma once
#include "word.h"
#include<string>
#include<map>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

class Lexer {
	
private:
	ifstream inputFile;
	map<string, symbol> reserved;
	vector<char> words;
	char ch=' ';
	int ll;
	int cc;
	int lCounter = 0;
	int wCounter = 0;
	char lBuffer[1024];

public:
	Lexer(string filename);
	void getchar();
	symbol sym;
	word getword();
	void iniReserTable();
	void back();
};