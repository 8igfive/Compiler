#include <fstream>
#include <sstream>
#include "WordAnalyser.h"
#define INPUTFILENAME	"testfile.txt"
#define OUTPUTFILENAME	"output.txt"

using std::ifstream;
using std::ofstream;
using std::ios;
using std::make_shared;
using std::istreambuf_iterator;
using std::endl;
using std::stringstream;

int main() {
	ifstream testfile;
	testfile.open(INPUTFILENAME, ios::in);

	ofstream output;
	output.open(OUTPUTFILENAME, ios::out);

	stringstream buf;

	buf << testfile.rdbuf();

	shared_ptr<WordAnalyser> wordAnalyser = make_shared<WordAnalyser>(buf.str());

	shared_ptr<WordInstance> wordInstance = wordAnalyser->next();
	while (wordInstance->getSymbol() != WordSymbol::EXIT) {
		output << *wordInstance << endl;
		wordInstance = wordAnalyser->next();
	}
	testfile.close();
	output.close();
	return 0;
}