#include "ErrorReporter.h"
#include "ErrorType.h"
#include <iostream>

using std::cout;
using std::endl;

ErrorReporter::ErrorReporter(int row, int num, ErrorType type)
	:row(row),num(num),type(type){}

ErrorReporter::ErrorReporter()
:row(-1),num(-1),type(ErrorType::TRIGGER){}

void ErrorReporter::showError(){
	cout << "Error occured in row: " << row << ", col: " << num << ", ErrorType: " << errorTypeToString(type) << "." << endl;
}
