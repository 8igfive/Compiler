#ifndef __WORDANALYSER_H__
#define __WORDANALYSER_H__

#include <iostream>
#include <cstdio>
#include <memory>
#include "WordInstance.h"

using std::string;
using std::shared_ptr;
using std::FILE;

class WordAnalyser{

	int row;
	int num;
	int numOld;															//as a remember.
	int c;
	FILE* file;
	

	inline void getChar() {
		c = fgetc(file);
		if (c == '\n') {
			row++;
			numOld = num;
			num = 1;
		}
	}
	inline void moveBackChar() {
		if (c == '\n') {
			row--;
			num = numOld;
		}
		fseek(file, -1L, SEEK_CUR);
	}

	static inline bool isDigit(char c) {
		return c >= '0' and c <= '9';
	}
	static inline bool isLetter(char c) {
		return c == '_' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
	}
	static inline bool isBlank(char c) {
		return c == ' ' || c == '\t' || c == '\r' || c == '\n';
	}

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
	WordAnalyser(FILE* fp);
	shared_ptr<WordInstance> next();									//return "" when there is no token.
};

#endif // !__WORDANALYSER_H__

