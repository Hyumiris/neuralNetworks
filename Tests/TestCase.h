
#ifndef testcase_h
#define testcase_h

#include <string>

using namespace std;

template <class infoObjType>
using test_func = void (*)(infoObjType *obj);

template <class infoObjType>
struct TestCase
{
	string name;
	test_func<infoObjType> fn;
	bool shouldPass = true;

	TestCase(string name, test_func<infoObjType> fn, bool shouldPass) : name(name), fn(fn), shouldPass(shouldPass) {}
	TestCase(string name, test_func<infoObjType> fn) : name(name), fn(fn) {}

	bool run(infoObjType *p)
	{
		try
		{
			fn(p);
			return shouldPass;
		}
		catch (...)
		{
			return !shouldPass;
		}
	}
};

#endif
