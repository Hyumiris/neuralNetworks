
#ifndef testcase_h
#define testcase_h

#include <string>

#include "TestAssistant.h"

using namespace std;

struct TestCase
{
	using func = std::function<void(TestAssistant& tester)>;

	string name;
	func fn;
	bool shouldPass = true;

	TestCase(string name, func fn, bool shouldPass) : name(name), fn(fn), shouldPass(shouldPass) {}
	TestCase(string name, func fn) : name(name), fn(fn) {}

	bool run(TestAssistant& tester)
	{
		try
		{
			fn(tester);
			return shouldPass;
		}
		catch (...)
		{
			return !shouldPass;
		}
	}
};

#endif
