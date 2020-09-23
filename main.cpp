#include <fstream>
#include <stdio.h>
#include "WordAnalyser.h"
#define INPUTFILENAME	"testfile.txt"
#define OUTPUTFILENAME	"output.txt"

using std::ofstream;
using std::ios;
using std::make_shared;
using std::endl;

int main() {
	FILE* testfile=fopen(INPUTFILENAME, "r");

	ofstream output;
	output.open(OUTPUTFILENAME, ios::out);


	shared_ptr<WordAnalyser> wordAnalyser = make_shared<WordAnalyser>(testfile);

	shared_ptr<WordInstance> wordInstance = wordAnalyser->next();
	while (wordInstance->getSymbol() != WordSymbol::EXIT) {
		output << *wordInstance << endl;
		wordInstance = wordAnalyser->next();
	}
	fclose(testfile);
	output.close();
	return 0;
}