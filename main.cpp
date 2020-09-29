#include <fstream>
#include <cstdio>
#include "WordAnalyser.h"
#define INPUTFILENAME	"C:\\Users\\8igfive\\Desktop\\Schools\\������\\����\\��һ����ҵ\\testfile5.txt"
#define OUTPUTFILENAME	"output.txt"

using std::ofstream;
using std::ios;
using std::make_shared;
using std::endl;
using std::fopen;

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