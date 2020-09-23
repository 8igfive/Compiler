#ifndef __WORDANALYSER_H__
#define __WORDANALYSER_H__

#include <iostream>
#include <sstream>
#include <memory>
#include "WordInstance.h"

using std::string;
using std::stringbuf;
using std::shared_ptr;

class WordAnalyser{

	int row;
	int col;
	int colOld;															//as a remember.
	int c;
	stringbuf buffer;

	inline void getChar();
	inline void moveBackChar();

	static inline bool isDigit(char c);
	static inline bool isLetter(char c);
	static inline bool isBlank(char c);									//don't include \n

	void handleBlank();
	shared_ptr<WordInstance> handleIdentifierOrReservedWord();
	shared_ptr<WordInstance> handleInteger();
	shared_ptr<WordInstance> handleChar();
	shared_ptr<WordInstance> handleString();
	shared_ptr<WordInstance> handleL();									//'<' or "<="	
	shared_ptr<WordInstance> handleG();									//'>' or ">="
	shared_ptr<WordInstance> handleE();									//'=' or '=='
	shared_ptr<WordInstance> handleN();									//"!="
	shared_ptr<WordInstance> handleSingleWord();

public:
	WordAnalyser(const string& source);
	shared_ptr<WordInstance> next();									//return "" when there is no token.
};

#endif // !__WORDANALYSER_H__

