#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <memory>
#include <vector>
#include <fstream>
#include <cstdio>
#include "WordAnalyser.h"
#include "GrammaAnalyser.h"
#include "ErrorReporter.h"
#include "IdenfrType.h"

using std::shared_ptr;
using std::vector;
using std::ofstream;
using std::unordered_map;

//control part

#define OUTPUT_KEY

//file part

#define INPUTFILENAME	"C:\\Users\\8igfive\\Desktop\\Schools\\大三上\\编译\\第一次作业\\testfile5.txt"
#define OUTPUTFILENAME	"output.txt"

#endif // !__GLOBAL_H__