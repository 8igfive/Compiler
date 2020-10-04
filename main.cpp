#include <fstream>
#include <cstdio>
#include <iostream>
#include "WordAnalyser.h"
#include "Global.h"

using std::ofstream;
using std::ios;
using std::make_shared;
using std::endl;
using std::cout;
using std::fopen;

//global variables part 

ofstream output;

FILE* testfile;

vector<ErrorReporter> errorCollector;

shared_ptr<WordAnalyser> wordAnalyser;

shared_ptr<GrammaAnalyser> grammaAnalyser;

unordered_map<string, IdenfrType> symbolTable;

int main() {
	testfile=fopen(INPUTFILENAME, "r");

	output.open(OUTPUTFILENAME, ios::out);

	wordAnalyser = make_shared<WordAnalyser>(testfile);

	grammaAnalyser = make_shared<GrammaAnalyser>();

	grammaAnalyser->startAnalyse();

	fclose(testfile);
	output.close();
	return 0;
}