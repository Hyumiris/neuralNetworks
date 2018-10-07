
#ifndef tester_h
#define tester_h

#include <stdexcept>


class TestAssistant
{
  public:
	virtual void SetUp(){};
	virtual void TearDown(){ };

	virtual void *getData() { return nullptr; };

	void asserta(bool b)
	{
		if (!b)
		{
			throw std::runtime_error("test assertion failed");
		}
	}
};

#endif
