
#ifndef testresult_h
#define testresult_h

#include <string>

struct TestResult
{
	enum Code
	{
		OK,
		SHOULD_FAIL,
		ASSERTION_FAILED,
		ERROR_THROWN
	};

	Code code;
	std::string msg;

	TestResult(Code code, std::string message) : code(code), msg(message) {}
};

#endif
