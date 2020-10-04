#ifndef __GRAMMAANALYSER_H__
#define __GRAMMAANALYSER_H__

#include <memory>
#include "WordInstance.h"
#include "IdenfrType.h"
#include <deque>

using std::shared_ptr;
using std::deque;


class GrammaAnalyser
{
	//read token part
	shared_ptr<WordInstance> token;
	deque<shared_ptr<WordInstance>> tokenPreRead;
	int index4TokenPreRead;

	void readToken();
	shared_ptr<WordInstance> preReadToken();
	void resetIndex4TokenPreRead();					//reset before every time you want to preread


	//symbolTable part
	void insertIntoSymbolTable(const string& name,IdenfrType type);	//based on symbolTable

	//analyse part
	void stringHandler();

	void programHandler();

	void constDeclarationHandler();
	void constDefinationHanlder();
	void unsignedIntHandler();
	void intHandler();
	void declarationHeadHandler();
	void constHandler();

	void varDeclarationHandler();
	void varDefinationHandler();
	void varDefinationWithoutInitHanlder();
	void varDefinationWithInitHandler();

	void funcDefinationWithRetHandler();
	void funcDefinationWithoutRetHandler();
	void complexSentenceHandler();
	void paraTableHanlder();
	void mainFuncHandler();

	void exprHanlder();
	void termHandler();
	void factorHandler();

	void sentenceHandler();
	void assignSenHandler();
	void conditionSenHandler();
	void conditionHandler();
	void loopSenHandler();
	void stepHandler();
	void switchSenHandler();
	void caseTableHandler();
	void caseHandler();
	void defaultHandler();
	void funcCallWithRetHandler();
	void funcCallWithoutRetHandler();
	void funcCallHandler();
	void valueParaTableHandler();
	void multSentencesHandler();
	void scanfHandler();
	void printfHandler();
	void retHandler();

public:
	GrammaAnalyser();
	void startAnalyse();
};

#endif // !__GRAMMAANALYSER_H__

