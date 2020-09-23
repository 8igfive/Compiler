#include "ErrorRepoter.h"
#include "ErrorType.h"
#include <iostream>

using std::cout;
using std::endl;

ErrorRepoter::ErrorRepoter(int row, int col, ErrorType type)
	:row(row),col(col),type(type){}

ErrorRepoter::ErrorRepoter()
:row(-1),col(-1),type(ErrorType::TRIGGER){}

void ErrorRepoter::showError(){
	cout << "Error occured in row: " << row << ", col: " << col << ", ErrorType: " << errorTypeToString(type) << "." << endl;
}
