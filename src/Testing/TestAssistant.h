
#ifndef testassistant_h
#define testassistant_h

#include "TestResult.h"

#include <stdexcept>

class test_failed : public std::runtime_error
{
	using Code = TestResult::Code;

  public:
	Code code;

	test_failed(Code code) : std::runtime_error(""), code(code) {}
	test_failed(Code code, const char *m) : std::runtime_error(m), code(code) {}
};

class TestAssistant
{
	using Code = TestResult::Code;

  public:
	virtual void SetUp(){};
	virtual void TearDown(){};

	virtual void *getData() { return nullptr; };

	void Assert(bool b)
	{
		if (!b)
		{
			throw test_failed(Code::ASSERTION_FAILED, "generic assertion failed");
		}
	}
};

#endif
