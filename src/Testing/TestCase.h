
#ifndef testcase_h
#define testcase_h

#include <string>

#include "TestAssistant.h"
#include "TestResult.h"

using namespace std;

struct TestCase
{
	using func = std::function<void(TestAssistant &tester)>;
	using Code = TestResult::Code;

	string name;
	func fn;
	bool shouldPass = true;

	TestCase(string name, func fn, bool shouldPass) : name(name), fn(fn), shouldPass(shouldPass) {}
	TestCase(string name, func fn) : name(name), fn(fn) {}

	TestResult run(TestAssistant &tester)
	{
		try
		{
			fn(tester);

			return shouldPass
					   ? TestResult(Code::OK, "")
					   : throw test_failed(Code::SHOULD_FAIL, "should have failed");
		}
		catch (test_failed &e)
		{
			return shouldPass
					   ? TestResult(e.code, e.what())
					   : TestResult(Code::OK, "");
		}
		catch (std::exception &e)
		{
			return shouldPass
					   ? TestResult(Code::ERROR_THROWN, e.what())
					   : TestResult(Code::OK, "");
		}
		catch (...)
		{
			return TestResult(Code::ERROR_THROWN, "a non exception was thrown");
		}
	}
};

#endif
