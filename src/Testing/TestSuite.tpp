
#include "TestSuite.h"

template <typename testassist_t, typename testable_t>
TestSuite_t<testassist_t, testable_t> &TestSuite_t<testassist_t, testable_t>::addTest(testable_t test)
{
	tests.push_back(test);
	return (*this);
}

template <typename testassist_t, typename testable_t>
template <typename test_func>
TestSuite_t<testassist_t, testable_t> &TestSuite_t<testassist_t, testable_t>::addTest(string name, test_func fn, bool shouldPass)
{
	tests.push_back(testable_t(name, fn, shouldPass));
	return (*this);
}

template <typename testassist_t, typename testable_t>
void TestSuite_t<testassist_t, testable_t>::runTests()
{
	for (int i = 0; i < tests.size(); i++)
	{
		testable_t &test = tests[i];

		tester.SetUp();
		TestResult result = test.run(tester);
		tester.TearDown();

		std::string resString = result.code == TestResult::OK ? "[SUCCESS]" : "[FAILURE]";
		resString.resize(12, ' ');
		std::string name = test.name;
		name.resize(20, ' ');
		name.resize(23, ' ');

		std::cout << resString << name << result.msg << std::endl;
	}
}
