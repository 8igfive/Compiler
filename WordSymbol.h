#ifndef __WORDSYMBOL_H__
#define __WORDSYMBOL_H__

#include <unordered_map>
#include <unordered_set>

using std::unordered_map;
using std::unordered_set;
using std::string;

enum class WordSymbol {
	//标识符
	IDENFR,

	//整型常类
	INTCON,

	//字符常量
	CHARCON,

	//字符串
	STRCON,

	//保留字
	CONSTTK,		//const		
	INTTK,			//int
	CHARTK,			//char
	VOIDTK,			//void
	MAINTK,			//main
	IFTK,			//if
	ELSETK,			//else
	SWITCHTK,		//switch
	CASETK,			//case
	DEFAULTTK,		//default
	WHILETK,		//while
	FORTK,			//for
	SCANFTK,		//scanf
	PRINTFTK,		//printf
	RETURNTK,		//return

	//运算符
	PLUS,			//+
	MINU,			//-
	MULT,			//*
	DIV,			///
	LSS,			//<
	LEQ,			//<=
	GRE,			//>
	GEQ,			//>=
	EQL,			//==
	NEQ,			//!=
	COLON,			//:
	ASSIGN,			//=
	SEMICN,			//;
	COMMA,			//,
	LPARENT,		//(
	RPARENT,		//)
	LBRACK,			//[
	RBRACK,			//]
	LBRACE,			//{
	RBRACE,			//}

	//结束符
	ERROR,
	EXIT			
};

const unordered_map<WordSymbol, string> toString{
	{WordSymbol::IDENFR,			"IDENFR"},
	{WordSymbol::INTCON,			"INTCON"},
	{WordSymbol::CHARCON,			"CHARCON"},
	{WordSymbol::STRCON,			"STRCON"},
	{WordSymbol::CONSTTK,			"CONSTTK"},
	{WordSymbol::INTTK,				"INTTK"},
	{WordSymbol::CHARTK,			"CHARTK"},
	{WordSymbol::VOIDTK,			"VOIDTK"},
	{WordSymbol::MAINTK,			"MAINTK"},
	{WordSymbol::IFTK,				"IFTK"},
	{WordSymbol::ELSETK,			"ELSETK"},
	{WordSymbol::SWITCHTK,			"SWITCHTK"},
	{WordSymbol::CASETK,			"CASETK"},
	{WordSymbol::DEFAULTTK,			"DEFAULTTK"},
	{WordSymbol::WHILETK,			"WHILETK"},
	{WordSymbol::FORTK,				"FORTK"},
	{WordSymbol::SCANFTK,			"SCANFTK"},
	{WordSymbol::PRINTFTK,			"PRINTFTK"},
	{WordSymbol::RETURNTK,			"RETURNTK"},
	{WordSymbol::PLUS,				"PLUS"},
	{WordSymbol::MINU,				"MINU"},
	{WordSymbol::MULT,				"MULT"},
	{WordSymbol::DIV,				"DIV"},
	{WordSymbol::LSS,				"LSS"},
	{WordSymbol::LEQ,				"LEQ"},
	{WordSymbol::GRE,				"GRE"},
	{WordSymbol::GEQ,				"GEQ"},
	{WordSymbol::EQL,				"EQL"},
	{WordSymbol::NEQ,				"NEQ"},
	{WordSymbol::COLON,				"COLON"},
	{WordSymbol::ASSIGN,			"ASSIGN"},
	{WordSymbol::SEMICN,			"SEMICN"},
	{WordSymbol::COMMA,				"COMMA"},
	{WordSymbol::LPARENT,			"LPARENT"},
	{WordSymbol::RPARENT,			"RPARENT"},
	{WordSymbol::LBRACK,			"LBRACK"},
	{WordSymbol::RBRACK,			"RBRACK"},
	{WordSymbol::LBRACE,			"LBRACE"},
	{WordSymbol::RBRACE,			"RBRACE"},
	{WordSymbol::ERROR,				"ERROR"},
	{WordSymbol::EXIT,				"EXIT"}
};

const unordered_map<string, WordSymbol> reservedWords{
	{"const",						WordSymbol::CONSTTK},
	{"int",							WordSymbol::INTTK},
	{"char",						WordSymbol::CHARTK},
	{"void",						WordSymbol::VOIDTK},
	{"main",						WordSymbol::MAINTK},
	{"if",							WordSymbol::IFTK},
	{"else",						WordSymbol::ELSETK},
	{"switch",						WordSymbol::SWITCHTK},
	{"case",						WordSymbol::CASETK},
	{"default",						WordSymbol::DEFAULTTK},
	{"while",						WordSymbol::WHILETK},
	{"for",							WordSymbol::FORTK},
	{"scanf",						WordSymbol::SCANFTK},
	{"printf",						WordSymbol::PRINTFTK},
	{"return",						WordSymbol::RETURNTK}
};

const unordered_map<char, WordSymbol> singleCharWords{
	{'+',							WordSymbol::PLUS},
	{'-',							WordSymbol::MINU},
	{'*',							WordSymbol::MULT},
	{'/',							WordSymbol::DIV},
	{':',							WordSymbol::COLON},
	{';',							WordSymbol::SEMICN},
	{',',							WordSymbol::COMMA},
	{'(',							WordSymbol::LPARENT},
	{')',							WordSymbol::RPARENT},
	{'[',							WordSymbol::LBRACK},
	{']',							WordSymbol::RBRACK},
	{'{',							WordSymbol::LBRACE},
	{'}',							WordSymbol::RBRACE}
};

const unordered_set<WordSymbol> plusOrMinu{
	WordSymbol::PLUS,
	WordSymbol::MINU
};

const unordered_set<WordSymbol> MultOrDiv{
	WordSymbol::MULT,
	WordSymbol::DIV
};

const unordered_set<WordSymbol> Relation{
	WordSymbol::LSS,
	WordSymbol::LEQ,
	WordSymbol::GRE,
	WordSymbol::GEQ,
	WordSymbol::NEQ,
	WordSymbol::EQL
};

string symbolToString(WordSymbol symbol);

bool isReservedWord(const string &word);

WordSymbol reservedWordToSymbol(const string& s);

WordSymbol singleCharWordToSymbol(char c);

bool isPulsOrMinu(WordSymbol symbol);

bool isMultOrDiv(WordSymbol symbol);

bool isRelation(WordSymbol symbol);

#endif // !__WORDSYMBOL_H__


