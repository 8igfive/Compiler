#ifndef __ERRORTYPE_H__
#define __ERRORTYPE_H__

#include <unordered_map>

using std::unordered_map;
using std::string;

enum class ErrorType {
	TRIGGER,
	WORDERROR
};

const unordered_map<ErrorType, string> typeToString{
	{ErrorType::TRIGGER,"TRIGGER"},
	{ErrorType::WORDERROR,"WORDERROR"}
};

string errorTypeToString(ErrorType type);

#endif // !__ERRORTYPE_H__

