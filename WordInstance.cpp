#include "WordInstance.h"

using std::make_shared;

WordInstance::WordInstance(WordSymbol symbol,const string& value)
	:symbol(symbol),value(value){}

WordInstance::WordInstance()
:symbol(WordSymbol::EXIT),value(""){}

WordSymbol WordInstance::getSymbol()
{
	return this->symbol;
}

shared_ptr<WordInstance> WordInstance::makeIndentifierOrReservedWord(const string& token){
	if (isReservedWord(token)) {
		return make_shared<WordInstance>(reservedWordToSymbol(token), token);
	}
	else {
		return make_shared<WordInstance>(WordSymbol::IDENFR, token);
	}
}

shared_ptr<WordInstance> WordInstance::makeInteger(const string& token){
	return make_shared<WordInstance>(WordSymbol::INTCON, token);
}

shared_ptr<WordInstance> WordInstance::makeChar(char c){
	string token;
	token.push_back(c);
	return make_shared<WordInstance>(WordSymbol::CHARCON, token);
}

/*shared_ptr<WordInstance> WordInstance::makeString(const string& token)
{
	return make_shared<WordInstance>(WordSymbol::STRCON, token);
}*/

ostream& operator<<(ostream& output, const WordInstance& wordInstance){
	output << symbolToString(wordInstance.symbol) << ' ' << wordInstance.value;
	return output;
}
