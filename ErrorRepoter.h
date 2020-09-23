#ifndef __ERRORREPORTER_H__
#define __ERRORREPORTER_H__ 

#include "ErrorType.h"

class ErrorRepoter{
	int row;
	int col;
	ErrorType type;
	
public:
	ErrorRepoter(int row, int col, ErrorType type);
	ErrorRepoter();
	void showError();
};

#endif // !__ERRORREPORTER_H__