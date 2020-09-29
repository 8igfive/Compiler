#include "WordSymbol.h"
#include <algorithm>
#include <cctype>
#include "ErrorReporter.h"
using std::transform;

string symbolToString(WordSymbol symbol){
	return toString.find(symbol)->second;
}

bool isReservedWord(const string& word){
	string lowerWord(word);
	transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), tolower);
	return reservedWords.find(lowerWord)!=reservedWords.end();
}

WordSymbol reservedWordToSymbol(const string& word)
{
	string lowerWord(word);
	transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), tolower);
	auto itr = reservedWords.find(lowerWord);
	if (itr != reservedWords.end()) {
		return itr->second;
	}
	throw ErrorReporter();				//error occur
}

WordSymbol singleCharWordToSymbol(char c)
{
	auto itr = singleCharWords.find(c);
	if (itr != singleCharWords.end()) {
		return singleCharWords.find(c)->second;
	}
	throw ErrorReporter();				//error occur
}
