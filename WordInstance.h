#ifndef __WORDINSTANCE_H__
#define __WORDINSTANCE_H__

#include "WordSymbol.h"
#include <iostream>
#include <memory>

using std::ostream;
using std::shared_ptr;

class WordInstance{
	WordSymbol symbol;
	string value;
public:
	WordInstance(WordSymbol symbol, const string& value);
	WordInstance();
	WordSymbol getSymbol();
	string getValue();
	static shared_ptr<WordInstance> makeIndentifierOrReservedWord(const string& token);
	static shared_ptr<WordInstance> makeInteger(const string& token);
	static shared_ptr<WordInstance> makeChar(char c);
	//static shared_ptr<WordInstance> makeString(const string& token);
	friend ostream& operator<<(ostream& output, const WordInstance& wordInstance);
};

#endif // !__WORDINSTANCE_H__
