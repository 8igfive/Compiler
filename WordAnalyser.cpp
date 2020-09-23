#include "WordAnalyser.h"
#include "ErrorRepoter.h"

using std::make_shared;

void WordAnalyser::handleBlank() {
	while (isBlank(c)) {
		getChar();
	}
}

shared_ptr<WordInstance> WordAnalyser::handleIdentifierOrReservedWord(){
	string token;
	while (isLetter(c) || isDigit(c)) {
		token.push_back(c);
		getChar();
	}
	if (c != EOF) {
		moveBackChar();
	}
	return WordInstance::makeIndentifierOrReservedWord(token);
}

shared_ptr<WordInstance> WordAnalyser::handleInteger(){
	string token;
	while (isDigit(c)) {
		token.push_back(c);
		getChar();
	}
	if (c != EOF) {
		moveBackChar();
	}
	return WordInstance::makeInteger(token);
}

shared_ptr<WordInstance> WordAnalyser::handleChar(){
	getChar();
	if (isLetter(c) || isDigit(c) || c == '+' || c == '-' || c == '*' || c == '/') {
		shared_ptr<WordInstance> ch = WordInstance::makeChar(c);
		getChar();
		if (c == '\'') {
			return ch;
		}
	}
	throw ErrorRepoter();
}

shared_ptr<WordInstance> WordAnalyser::handleString(){
	string token;
	getChar();
	while (c == 32 || c == 33 || c >= 35 && c <= 126) {
		token.push_back(c);
		getChar();
	}
	if (c == '"') {
		return make_shared<WordInstance>(WordSymbol::STRCON, token);
	}
	else {
		throw ErrorRepoter();
	}
}

shared_ptr<WordInstance> WordAnalyser::handleL(){
	getChar();
	if (c == '=') {
		return make_shared<WordInstance>(WordSymbol::LEQ, "<=");
	}
	if (c != EOF) {
		moveBackChar();
	}
	return make_shared<WordInstance>(WordSymbol::LSS, "<");
}

shared_ptr<WordInstance> WordAnalyser::handleG(){
	getChar();
	if (c == '=') {
		return make_shared<WordInstance>(WordSymbol::GEQ, ">=");
	}
	if (c != EOF) {
		moveBackChar();
	}
	return make_shared<WordInstance>(WordSymbol::GRE, ">");
}

shared_ptr<WordInstance> WordAnalyser::handleE()
{
	getChar();
	if (c == '=') {
		return make_shared<WordInstance>(WordSymbol::EQL, "==");
	}
	if (c != EOF) {
		moveBackChar();
	}
	return make_shared<WordInstance>(WordSymbol::ASSIGN, "=");
}

shared_ptr<WordInstance> WordAnalyser::handleN(){
	getChar();
	if (c == '=') {
		return make_shared<WordInstance>(WordSymbol::NEQ, "!=");
	}
	throw ErrorRepoter();
}

shared_ptr<WordInstance> WordAnalyser::handleSingleWord(){
	string token;
	token.push_back(c);
	return make_shared<WordInstance>(singleCharWordToSymbol(c), token);
}

WordAnalyser::WordAnalyser(FILE* fp)
:row(1),col(0),colOld(0),c(0),file(fp){
}

shared_ptr<WordInstance> WordAnalyser::next(){
	try {
		getChar();
		if (isBlank(c)) {
			handleBlank();
		}
		if (isLetter(c)) {
			return handleIdentifierOrReservedWord();
		}
		else if (isDigit(c)) {
			return handleInteger();
		}
		else if (c == '\'') {
			return handleChar();
		}
		else if (c == '"') {
			return handleString();
		}
		else if (c == '<') {
			return handleL();
		}
		else if (c == '>') {
			return handleG();
		}
		else if (c == '=') {
			return handleE();
		}
		else if (c == '!') {
			return handleN();
		}
		else if (c == EOF) {
			return make_shared<WordInstance>();
		}
		else {
			return handleSingleWord();
		}
	}
	catch (ErrorRepoter e) {						//assume e is trigger
		throw ErrorRepoter(row, col, ErrorType::WORDERROR);
	}
}
