#ifndef __ERRORREPORTER_H__
#define __ERRORREPORTER_H__ 

#include "ErrorType.h"

class ErrorReporter{
	int row;
	int num;
	ErrorType type;
	
public:
	ErrorReporter(int row, int num, ErrorType type);
	ErrorReporter();
	void showError();
};

#endif // !__ERRORREPORTER_H__