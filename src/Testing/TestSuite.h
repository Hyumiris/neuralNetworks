
#ifndef testsuite_h
#define testsuite_h

#include <iostream>
#include <string>
#include <vector>

#include "TestCase.h"
#include "TestAssistant.h"

using namespace std;

template <typename testassist_t, typename testable_t>
class TestSuite_t
{
  public:
	// constructor / destructor
	TestSuite_t() { tester = testassist_t(); }
	~TestSuite_t() {}

	// add testcases
	TestSuite_t<testassist_t, testable_t> &addTest(testable_t test);
	template <typename test_func>
	TestSuite_t<testassist_t, testable_t> &addTest(string name, test_func fn, bool shouldPass = true);

	// run tests
	void runTests();

  private:
	testassist_t tester;
	vector<testable_t> tests;
};

using TestSuite = TestSuite_t<TestAssistant, TestCase>;

#include "TestSuite.tpp"

#endif
