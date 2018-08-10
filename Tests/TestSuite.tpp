
#ifndef testsuite_h
#define testsuite_h

#include <stdio.h>
#include <string>
#include <vector>

#include "TestCase.tpp"

template <typename infoObjType>
class TestSuite
{
  public:
	// constructor / destructor
	TestSuite() { this->tests = vector<TestCase<infoObjType>>(); }
	~TestSuite() {}

	// add testcases
	void addTest(TestCase<infoObjType> test) { tests.push_back(test); }
	void addTest(string name, test_func<infoObjType> fn, bool shouldPass = true) { addTest(TestCase<infoObjType>(name, fn, shouldPass)); }

	// run tests
	void runTests()
	{
		for (int i = 0; i < tests.size(); i++)
		{
			TestCase<infoObjType> &test = tests[i];

			setUp();
			bool success = test.run(data);
			tearDown();

			printf("%s %s\n", test.name.c_str(), success ? "successful" : "failed");
		}
	}

  private:
	void setUp() { data = infoObjType::setUp(); }
	void tearDown() { infoObjType::tearDown(data); }

  private:
	infoObjType *data;
	vector<TestCase<infoObjType>> tests;
};

#endif
