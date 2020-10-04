#include "GrammaAnalyser.h"
#include "Global.h"
#include "ErrorReporter.h"
#include "WordSymbol.h"
#include "WordAnalyser.h"
#include <algorithm>
#include <iostream>
#include <fstream>

using std::endl;
using std::cout;
using std::ofstream;

extern ofstream output;
extern shared_ptr<WordAnalyser> wordAnalyser;
extern unordered_map<string, IdenfrType> symbolTable;

void GrammaAnalyser::readToken(){
	if (!tokenPreRead.empty()) {
		token = tokenPreRead.at(0);
		tokenPreRead.pop_front();
	}
	else {
		token = (*wordAnalyser).next();
	}
}

shared_ptr<WordInstance> GrammaAnalyser::preReadToken(){
	if (index4TokenPreRead < tokenPreRead.size()) {
		shared_ptr<WordInstance> ret = tokenPreRead.at(index4TokenPreRead);
		index4TokenPreRead++;
		return ret;
	}
	shared_ptr<WordInstance> preReadToken = (*wordAnalyser).next();
	index4TokenPreRead++;
	tokenPreRead.push_back(preReadToken);
	return preReadToken;
}

void GrammaAnalyser::resetIndex4TokenPreRead(){
	index4TokenPreRead = 0;
}

void GrammaAnalyser::insertIntoSymbolTable(const string& name, IdenfrType type){
	string lowerWord(name);
	transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), tolower);
	symbolTable.emplace(lowerWord, type);
}

void GrammaAnalyser::stringHandler(){
	if (token->getSymbol() != WordSymbol::STRCON) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	output << u8"<字符串>" << endl;
	#endif // OUTPUT_KEY

	readToken();
}

void GrammaAnalyser::programHandler(){
	shared_ptr<WordInstance> pre;
	if (token->getSymbol() == WordSymbol::CONSTTK) {
		constDeclarationHandler();
	}
	if (token->getSymbol() == WordSymbol::INTTK||
		token->getSymbol() == WordSymbol::CHARTK) {
		resetIndex4TokenPreRead();
		pre = preReadToken();
		if (pre->getSymbol() != WordSymbol::IDENFR) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}
		pre = preReadToken();
		if (pre->getSymbol() != WordSymbol::LPARENT) {
			varDeclarationHandler();
		}
	}
	while (true) {
		if (token->getSymbol() == WordSymbol::INTTK ||
			token->getSymbol() == WordSymbol::CHARTK) {
			funcDefinationWithRetHandler();
		}
		else if (token->getSymbol() == WordSymbol::VOIDTK) {
			resetIndex4TokenPreRead();
			pre = preReadToken();
			if (pre->getSymbol() == WordSymbol::MAINTK) {
				break;
			}
			funcDefinationWithoutRetHandler();
		}
		else {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}
	}
	mainFuncHandler();

	#ifdef OUTPUT_KEY
	output << u8"<程序>" << endl;
	#endif // OUTPUT_KEY

	if (token->getSymbol() != WordSymbol::EXIT) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}
}

void GrammaAnalyser::constDeclarationHandler(){
	if (token->getSymbol() != WordSymbol::CONSTTK) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}
	while (token->getSymbol() == WordSymbol::CONSTTK) {

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		constDefinationHanlder();
		if (token->getSymbol()!=WordSymbol::SEMICN) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
	}

	#ifdef OUTPUT_KEY
	output << u8"<常量说明>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::constDefinationHanlder(){
	if (token->getSymbol() == WordSymbol::INTTK) {
		int flag = 0;
		while ((!flag)&&token->getSymbol() == WordSymbol::INTTK || flag&&token->getSymbol() == WordSymbol::COMMA) {

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
			if (token->getSymbol() != WordSymbol::IDENFR) {
				ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
				//error.handle();
				return;
			}

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
			if (token->getSymbol() != WordSymbol::ASSIGN) {
				ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
				//error.handle();
				return;
			}

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
			intHandler();
			flag++;
		}
	}
	else if (token->getSymbol() == WordSymbol::CHARTK) {
		int flag = 0;
		while ((!flag) && token->getSymbol() == WordSymbol::CHARTK || flag && token->getSymbol() == WordSymbol::COMMA) {

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
			if (token->getSymbol() != WordSymbol::IDENFR) {
				ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
				//error.handle();
				return;
			}

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
			if (token->getSymbol() != WordSymbol::ASSIGN) {
				ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
				//error.handle();
				return;
			}

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
			if (token->getSymbol() != WordSymbol::CHARCON) {
				ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
				//error.handle();
				return;
			}

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
			flag++;
		}
	}else{
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << u8"<常量定义>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::unsignedIntHandler(){
	if (token->getSymbol() != WordSymbol::INTCON) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	output << u8"<无符号整数>" << endl;
	#endif // OUTPUT_KEY

	readToken();
}

void GrammaAnalyser::intHandler(){
	if (isPulsOrMinu(token->getSymbol())) {

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
	}
	unsignedIntHandler();

	#ifdef OUTPUT_KEY
	output << u8"<整数>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::declarationHeadHandler(){
	if (token->getSymbol() != WordSymbol::INTTK &&
		token->getSymbol() != WordSymbol::CHARTK) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol() != WordSymbol::IDENFR) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	insertIntoSymbolTable(token->getValue(), IdenfrType::FUNCWITHRET);		//TODO symbolTable

	readToken();

	#ifdef OUTPUT_KEY
	output << u8"<声明头部>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::constHandler(){
	if (token->getSymbol() == WordSymbol::CHARCON) {

	#ifdef OUTPUT_KEY
		output << *token << endl;
	#endif // OUTPUT_KEY

		readToken();
	}
	else if (token->getSymbol() == WordSymbol::PLUS ||
		token->getSymbol() == WordSymbol::MINU ||
		token->getSymbol() == WordSymbol::INTCON) {
		intHandler();
	}
	else {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << u8"<常量>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::varDeclarationHandler(){
	resetIndex4TokenPreRead();
	if (token->getSymbol() != WordSymbol::INTTK &&
		token->getSymbol() != WordSymbol::CHARTK) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}
	shared_ptr<WordInstance> pre = preReadToken();
	if (pre->getSymbol() != WordSymbol::IDENFR) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}
	pre = preReadToken();
	if (pre->getSymbol() == WordSymbol::LPARENT) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}
	while (true) {
		resetIndex4TokenPreRead();
		if (token->getSymbol() != WordSymbol::INTTK &&
			token->getSymbol() != WordSymbol::CHARTK) {
			break;
		}
		pre = preReadToken();
		if (pre->getSymbol() != WordSymbol::IDENFR) {
			break;
		}
		pre = preReadToken();
		if (pre->getSymbol() == WordSymbol::LPARENT) {
			break;
		}
		WordSymbol symbol = pre->getSymbol();
		if (symbol == WordSymbol::SEMICN ||
			symbol == WordSymbol::COMMA ||
			symbol == WordSymbol::LBRACK ||
			symbol == WordSymbol::ASSIGN) {
			varDefinationHandler();
		}
		else {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}
		if (token->getSymbol() != WordSymbol::SEMICN) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
	}

	#ifdef OUTPUT_KEY
	output << u8"<变量说明>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::varDefinationHandler(){
	if (token->getSymbol() != WordSymbol::INTTK &&
		token->getSymbol() != WordSymbol::CHARTK) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}
	resetIndex4TokenPreRead();
	shared_ptr<WordInstance> pre = preReadToken();
	if (pre->getSymbol() != WordSymbol::IDENFR) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}
	pre = preReadToken();
	if (pre->getSymbol() == WordSymbol::LBRACK) {
		pre = preReadToken();
		if (pre->getSymbol() != WordSymbol::INTCON) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}
		pre = preReadToken();
		if (pre->getSymbol() != WordSymbol::RBRACK) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}
		pre = preReadToken();
		if (pre->getSymbol() == WordSymbol::LBRACK) {
			pre = preReadToken();
			if (pre->getSymbol() != WordSymbol::INTCON) {
				ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
				//error.handle();
				return;
			}
			pre = preReadToken();
			if (pre->getSymbol() != WordSymbol::RBRACK) {
				ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
				//error.handle();
				return;
			}
			pre = preReadToken();
		}
	}
	if (pre->getSymbol() == WordSymbol::ASSIGN) {
		varDefinationWithInitHandler();
	}
	else {
		varDefinationWithoutInitHanlder();
	}

	#ifdef OUTPUT_KEY
	output << u8"<变量定义>" << endl;
	#endif // !OUTPUT_KEY

}
  
void GrammaAnalyser::varDefinationWithoutInitHanlder(){
	if (token->getSymbol() != WordSymbol::INTTK &&
		token->getSymbol() != WordSymbol::CHARTK) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}
	int flag = 0;
	while ((!flag) && (token->getSymbol() == WordSymbol::INTTK || token->getSymbol() == WordSymbol::CHARTK) ||
		flag && token->getSymbol() == WordSymbol::COMMA) {
		
		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		if (token->getSymbol() != WordSymbol::IDENFR) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		if (token->getSymbol() == WordSymbol::LBRACK) {

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
			unsignedIntHandler();
			if (token->getSymbol() != WordSymbol::RBRACK) {
				ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
				//error.handle();
				return;
			}

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
			if (token->getSymbol() == WordSymbol::LBRACK) {

				#ifdef OUTPUT_KEY
				output << *token << endl;
				#endif // OUTPUT_KEY

				readToken();
				unsignedIntHandler();
				if (token->getSymbol() != WordSymbol::RBRACK) {
					ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
					//error.handle();
					return;
				}

				#ifdef OUTPUT_KEY
				output << *token << endl;
				#endif // OUTPUT_KEY

				readToken();
			}
		}
		flag++;
	}

	#ifdef OUTPUT_KEY
	output << u8"<变量定义无初始化>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::varDefinationWithInitHandler(){
	if (token->getSymbol() != WordSymbol::INTTK &&
		token->getSymbol() != WordSymbol::CHARTK) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}
	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol() != WordSymbol::IDENFR) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}
	
	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol() == WordSymbol::ASSIGN) {

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		constHandler();
	}
	else if (token->getSymbol() == WordSymbol::LBRACK) {

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		unsignedIntHandler();
		if (token->getSymbol() != WordSymbol::RBRACK) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		if (token->getSymbol() == WordSymbol::ASSIGN) {

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
			if (token->getSymbol() != WordSymbol::LBRACE) {
				ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
				//error.handle();
				return;
			}
			int flag = 0;
			while ((!flag) && token->getSymbol() == WordSymbol::LBRACE ||
				flag && token->getSymbol() == WordSymbol::COMMA) {

				#ifdef OUTPUT_KEY
				output << *token << endl;
				#endif // OUTPUT_KEY

				readToken();
				constHandler();
				flag++;
			}
			if (token->getSymbol() != WordSymbol::RBRACE) {
				ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
				//error.handle();
				return;
			}

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
		}
		else if (token->getSymbol() == WordSymbol::LBRACK) {

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
			unsignedIntHandler();
			if (token->getSymbol() != WordSymbol::RBRACK) {
				ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
				//error.handle();
				return;
			}

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KRY

			readToken();
			if (token->getSymbol() != WordSymbol::ASSIGN) {
				ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
				//error.handle();
				return;
			}

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
			if (token->getSymbol() != WordSymbol::LBRACE) {
				ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
				//error.handle();
				return;
			}
			int flag0 = 0;
			while ((!flag0) && token->getSymbol() == WordSymbol::LBRACE||
				flag0&&token->getSymbol()==WordSymbol::COMMA) {

				#ifdef OUTPUT_KEY
				output << *token << endl;
				#endif // OUTPUT_KEY

				readToken();
				if (token->getSymbol() != WordSymbol::LBRACE) {
					ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
					//error.handle();
					return;
				}
				int flag1 = 0;
				while ((!flag1) && token->getSymbol() == WordSymbol::LBRACE||
					flag1&&token->getSymbol()==WordSymbol::COMMA) {

					#ifdef OUTPUT_KEY
					output << *token << endl;
					#endif // OUTPUT_KEY

					readToken();
					constHandler();
					flag1++;
				}
				if (token->getSymbol() != WordSymbol::RBRACE) {
					ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
					//error.handle();
					return;
				}

				#ifdef OUTPUT_KEY
				output << *token << endl;
				#endif // OUTPUT_KEY
				readToken();
				flag0++;
			}
			if (token->getSymbol() != WordSymbol::RBRACE) {
				ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
				//error.handle();
				return;
			}

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
		}
		else {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}
	}
	else {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << u8"<变量定义及初始化>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::funcDefinationWithRetHandler(){
	declarationHeadHandler();
	if (token->getSymbol() != WordSymbol::LPARENT) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	paraTableHanlder();
	if (token->getSymbol() != WordSymbol::RPARENT) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol() != WordSymbol::LBRACE) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();

	complexSentenceHandler();
	if (token->getSymbol() != WordSymbol::RBRACE) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}
	
	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();

	#ifdef OUTPUT_KEY
	output << u8"<有返回值函数定义>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::funcDefinationWithoutRetHandler(){
	if (token->getSymbol() != WordSymbol::VOIDTK) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}
	
	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol() != WordSymbol::IDENFR) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	insertIntoSymbolTable(token->getValue(), IdenfrType::FUNCWITHOUTRET);	//TODO symbolTable

	readToken();
	if (token->getSymbol() != WordSymbol::LPARENT) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	paraTableHanlder();
	if (token->getSymbol() != WordSymbol::RPARENT) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol() != WordSymbol::LBRACE) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	complexSentenceHandler();
	if (token->getSymbol() != WordSymbol::RBRACE) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();

#ifdef OUTPUT_KEY
	output << u8"<无返回值函数定义>" << endl;
#endif // OUTPUT_KEY

}

void GrammaAnalyser::complexSentenceHandler(){
	if (token->getSymbol() == WordSymbol::CONSTTK) {
		constDeclarationHandler();
	}
	if (token->getSymbol() == WordSymbol::INTTK ||
		token->getSymbol() == WordSymbol::CHARTK) {
		varDeclarationHandler();
	}
	multSentencesHandler();

	#ifdef OUTPUT_KEY
	output << u8"<复合语句>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::paraTableHanlder(){
	int flag = 0;
	do {
		if (flag) {
			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
			if (token->getSymbol() != WordSymbol::INTTK &&
				token->getSymbol() != WordSymbol::CHARTK) {
				ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
				//error.handle();
				return;
			}

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
			if (token->getSymbol() != WordSymbol::IDENFR) {
				ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
				//error.handle();
				return;
			}

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
		}
		else {
			if (token->getSymbol() != WordSymbol::INTTK &&
				token->getSymbol() != WordSymbol::CHARTK) {
				break;
			}
			resetIndex4TokenPreRead();
			shared_ptr<WordInstance> pre = preReadToken();
			if (pre->getSymbol() != WordSymbol::IDENFR) {
				break;
			}
			
			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
			flag++;
		}
	} while (token->getSymbol()==WordSymbol::COMMA);
	
	#ifdef OUTPUT_KEY
	output << u8"<参数表>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::mainFuncHandler(){
	if (token->getSymbol() != WordSymbol::VOIDTK) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol() != WordSymbol::MAINTK) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol() != WordSymbol::LPARENT) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol() != WordSymbol::RPARENT) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol() != WordSymbol::LBRACE) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	complexSentenceHandler();
	if (token->getSymbol() != WordSymbol::RBRACE) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();

	#ifdef OUTPUT_KEY
	output << u8"<主函数>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::exprHanlder(){
	if (isPulsOrMinu(token->getSymbol())) {

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
	}
	int flag = 0;
	do {
		if (flag) {

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
			termHandler();
		}
		else {
			termHandler();
			flag++;
		}
	} while (isPulsOrMinu(token->getSymbol()));

	#ifdef OUTPUT_KEY
	output << u8"<表达式>" << endl;
	#endif // OUTPUT_KEU

}

void GrammaAnalyser::termHandler(){
	int flag = 0;
	do {
		if (flag) {

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
			factorHandler();
		}
		else {
			factorHandler();
			flag++;
		}
	} while (isMultOrDiv(token->getSymbol()));

	#ifdef OUTPUT_KEY
	output << u8"<项>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::factorHandler(){
	WordSymbol symbol = token->getSymbol();
	if (symbol==WordSymbol::PLUS||
		symbol==WordSymbol::MINU||
		symbol==WordSymbol::INTCON) {
		intHandler();
	}
	else if (symbol == WordSymbol::CHARCON) {

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
	}
	else if (symbol == WordSymbol::LPARENT) {
		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		exprHanlder();
		if (token->getSymbol() != WordSymbol::RPARENT) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
	}
	else if (symbol == WordSymbol::IDENFR) {
		string value = token->getValue();
		auto itr = symbolTable.find(value);
		if (itr != symbolTable.end()) {
			if (itr->second == IdenfrType::FUNCWITHRET) {
				funcCallWithRetHandler();
			}
			else {
				ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
				//error.handle();
				return;
			}
		}
		else {

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
			if (token->getSymbol() == WordSymbol::LBRACK) {

				#ifdef OUTPUT_KEY
				output << *token << endl;
				#endif // OUTPUT_KEY

				readToken();
				exprHanlder();
				if (token->getSymbol() != WordSymbol::RBRACK) {
					ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
					//error.handle();
					return;
				}

				#ifdef OUTPUT_KEY
				output << *token << endl;
				#endif // OUTPUT_KEY

				readToken();
				if (token->getSymbol() == WordSymbol::LBRACK) {

					#ifdef OUTPUT_KEY
					output << *token << endl;
					#endif // OUTPUT_KEY

					readToken();
					exprHanlder();
					if (token->getSymbol() != WordSymbol::RBRACK) {
						ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
						//error.handle();
						return;
					}

					#ifdef OUTPUT_KEY
					output << *token << endl;
					#endif // OUTPUT_KEY

					readToken();
				}
			}
		}
	}
	else {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << u8"<因子>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::sentenceHandler(){
	switch (token->getSymbol()) {
	case WordSymbol::WHILETK:
	case WordSymbol::FORTK:
		loopSenHandler();
		break;
	case WordSymbol::IFTK:
		conditionSenHandler();
		break;
	case WordSymbol::SWITCHTK:
		switchSenHandler();
		break;
	case WordSymbol::LBRACE:

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		multSentencesHandler();
		if(token->getSymbol()!=WordSymbol::RBRACE){
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		break;
	default: {
		switch (token->getSymbol()) {
		case WordSymbol::IDENFR: {
			string value = token->getValue();
			auto itr = symbolTable.find(value);
			if (itr != symbolTable.end()) {
				if (itr->second == IdenfrType::FUNCWITHRET) {
					funcCallWithRetHandler();
				}
				else {
					funcCallWithoutRetHandler();
				}
			}
			else {
				assignSenHandler();
			}
		}
		case WordSymbol::SCANFTK:
			scanfHandler();
			break;
		case WordSymbol::PRINTFTK:
			printfHandler();
			break;
		case WordSymbol::SEMICN:
			break;
		case WordSymbol::RETURNTK:
			retHandler();
			break;
		default:
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}
		if (token->getSymbol() != WordSymbol::SEMICN) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY
		readToken();
	}
	}

	#ifdef OUTPUT_KEY
	output << u8"<语句>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::assignSenHandler(){
	if (token->getSymbol() != WordSymbol::IDENFR) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol() == WordSymbol::LBRACK) {

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		exprHanlder();
		if (token->getSymbol() != WordSymbol::RBRACK) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		if (token->getSymbol() == WordSymbol::LBRACK) {

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
			exprHanlder();
			if (token->getSymbol() != WordSymbol::RBRACK) {
				ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
				//error.handle();
				return;
			}

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
		}
	}

	if (token->getSymbol() != WordSymbol::ASSIGN) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	exprHanlder();

	#ifdef OUTPUT_KEY
	output << u8"<赋值语句>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::conditionSenHandler(){
	if (token->getSymbol() != WordSymbol::IFTK) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol()!=WordSymbol::LPARENT) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	conditionHandler();
	if (token->getSymbol() != WordSymbol::RPARENT) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	sentenceHandler();
	if (token->getSymbol() == WordSymbol::ELSETK) {

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY
		
		readToken();
		sentenceHandler();
	}

	#ifdef OUTPUT_KEY
	output << u8"<条件语句>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::conditionHandler(){
	exprHanlder();
	if (!isRelation(token->getSymbol())) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	exprHanlder();

	#ifdef OUTPUT_KEY
	output << u8"<条件>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::loopSenHandler(){
	WordSymbol symbol=token->getSymbol();
	if (symbol == WordSymbol::WHILETK) {

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		if (token->getSymbol() != WordSymbol::LPARENT) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		conditionHandler();
		if (token->getSymbol() != WordSymbol::RPARENT) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		sentenceHandler();
	}
	else if (symbol == WordSymbol::FORTK) {

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		if (token->getSymbol() != WordSymbol::LPARENT) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		if (token->getSymbol() != WordSymbol::IDENFR) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		if (token->getSymbol() != WordSymbol::ASSIGN) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		exprHanlder();
		if (token->getSymbol() != WordSymbol::SEMICN) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		conditionHandler();
		if (token->getSymbol() != WordSymbol::SEMICN) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		if (token->getSymbol() != WordSymbol::IDENFR) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		if (token->getSymbol() != WordSymbol::ASSIGN) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		if (token->getSymbol() != WordSymbol::IDENFR) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		if (!isPulsOrMinu(token->getSymbol())) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		stepHandler();
		if (token->getSymbol() != WordSymbol::RPARENT) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		sentenceHandler();
	}
	else {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << u8"<循环语句>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::stepHandler(){
	if (token->getSymbol() != WordSymbol::INTCON) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}
	unsignedIntHandler();

	#ifdef OUTPUT_KEY
	output << u8"<步长>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::switchSenHandler(){
	if (token->getSymbol() != WordSymbol::SWITCHTK) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol() != WordSymbol::LPARENT) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	exprHanlder();
	if (token->getSymbol() != WordSymbol::RPARENT) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol() != WordSymbol::LBRACE) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	caseTableHandler();
	defaultHandler();
	if (token->getSymbol() != WordSymbol::RBRACE) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	output << u8"<情况语句>" << endl;
	#endif // OUTPUT_KEY

	readToken();
}

void GrammaAnalyser::caseTableHandler(){
	if (token->getSymbol() != WordSymbol::CASETK) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}
	while (token->getSymbol() == WordSymbol::CASETK) {
		caseHandler();
	}

	#ifdef OUTPUT_KEY
	output << u8"<情况表>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::caseHandler(){
	if (token->getSymbol() != WordSymbol::CASETK) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	constHandler();
	if (token->getSymbol() != WordSymbol::COLON) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	sentenceHandler();

	#ifdef OUTPUT_KEY
	output << u8"<情况子语句>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::defaultHandler(){
	if (token->getSymbol() != WordSymbol::DEFAULTTK) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol() != WordSymbol::COLON) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	sentenceHandler();

	#ifdef OUTPUT_KEY
	output << u8"<缺省>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::funcCallWithRetHandler(){
	funcCallHandler();

	#ifdef OUTPUT_KEY
	output << u8"<有返回值函数调用语句>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::funcCallWithoutRetHandler(){
	funcCallHandler();

	#ifdef OUTPUT_KEY
	output << u8"<无返回值函数调用语句>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::funcCallHandler(){
	if (token->getSymbol() != WordSymbol::IDENFR) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol() != WordSymbol::LPARENT) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	valueParaTableHandler();
	if (token->getSymbol() != WordSymbol::RPARENT) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
}

void GrammaAnalyser::valueParaTableHandler(){
	WordSymbol symbol = token->getSymbol();
	if (isPulsOrMinu(symbol) ||
		symbol == WordSymbol::IDENFR ||
		symbol == WordSymbol::LPARENT ||
		symbol == WordSymbol::INTCON ||
		symbol == WordSymbol::CHARCON) {
		int flag=0;
		do {
			if (flag) {

				#ifdef OUTPUT_KEY
				output << *token << endl;
				#endif // OUTPUT_KEY

				readToken();
				symbol = token->getSymbol();
				if (isPulsOrMinu(symbol) ||
					symbol == WordSymbol::IDENFR ||
					symbol == WordSymbol::LPARENT ||
					symbol == WordSymbol::INTCON ||
					symbol == WordSymbol::CHARCON) {
					exprHanlder();
				}
				else {
					ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
					//error.handle();
					return;
				}
			}
			else {
				exprHanlder();
				flag++;
			}
		} while (token->getSymbol()==WordSymbol::COMMA);
	}

	#ifdef OUTPUT_KEY
	output << u8"<值参数表>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::multSentencesHandler(){
	WordSymbol symbol = token->getSymbol();
	while (symbol == WordSymbol::WHILETK ||
		symbol == WordSymbol::FORTK ||
		symbol == WordSymbol::IFTK||
		symbol == WordSymbol::IDENFR ||
		symbol == WordSymbol::SCANFTK ||
		symbol == WordSymbol::PRINTFTK ||
		symbol == WordSymbol::SWITCHTK ||
		symbol == WordSymbol::SEMICN ||
		symbol == WordSymbol::RETURNTK ||
		symbol == WordSymbol::LBRACE) {
		sentenceHandler();
		symbol = token->getSymbol();
	}

	#ifdef OUTPUT_KEY
	output << u8"<语句列>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::scanfHandler(){
	if (token->getSymbol() != WordSymbol::SCANFTK) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol() != WordSymbol::LPARENT) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol() != WordSymbol::IDENFR) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol() != WordSymbol::RPARENT) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();

	#ifdef OUTPUT_KEY
	output << u8"<读语句>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::printfHandler(){
	if (token->getSymbol() != WordSymbol::PRINTFTK) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol() != WordSymbol::LPARENT) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}
	
	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol() == WordSymbol::STRCON) {
		stringHandler();
		if (token->getSymbol() == WordSymbol::COMMA) {

			#ifdef OUTPUT_KEY
			output << *token << endl;
			#endif // OUTPUT_KEY

			readToken();
			exprHanlder();
		}
	}
	else {
		exprHanlder();
	}
	if (token->getSymbol() != WordSymbol::RPARENT) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();

	#ifdef OUTPUT_KEY
	output << u8"<写语句>" << endl;
	#endif // OUTPUT_KEY

}

void GrammaAnalyser::retHandler(){
	if (token->getSymbol() != WordSymbol::RETURNTK) {
		ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
		//error.handle();
		return;
	}

	#ifdef OUTPUT_KEY
	output << *token << endl;
	#endif // OUTPUT_KEY

	readToken();
	if (token->getSymbol() == WordSymbol::LPARENT) {

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
		exprHanlder();
		if (token->getSymbol() != WordSymbol::RPARENT) {
			ErrorReporter error((*wordAnalyser).getRow(), (*wordAnalyser).getNum(), ErrorType::GRAMMAERROR);
			//error.handle();
			return;
		}

		#ifdef OUTPUT_KEY
		output << *token << endl;
		#endif // OUTPUT_KEY

		readToken();
	}

	#ifdef OUTPUT_KEY
	output << u8"<返回语句>" << endl;
	#endif // OUTPUT_KEY

}

GrammaAnalyser::GrammaAnalyser()
:index4TokenPreRead(0){}

void GrammaAnalyser::startAnalyse(){
	readToken();
	programHandler();
}
