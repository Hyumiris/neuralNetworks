
#include <TestSuite.h>

#include <Vector.h>
#include <Matrix.h>

void testVector()
{
	TestSuite suite = TestSuite();

	suite
		.addTest("Creation", [](TestAssistant &t) {
			Vector v1(4);
			t.Assert(v1.Length() == 4);

			Vector v2(v1);
			t.Assert(v2 == v1);

			Vector v3(std::move(v2));
			t.Assert(v3 == v1);
			t.Assert(v3 != v2);
		})
		.addTest("Assignment", [](TestAssistant &t) {
			Vector v2, v3;
			Vector v1(4);

			v2 = v1;
			t.Assert(&v1 != &v2);
			t.Assert(v1 == v2);

			v3 = std::move(v2);
			t.Assert(&v2 != &v3);
			t.Assert(v2 != v3);
		})
		.addTest("Length on transpose", [](TestAssistant &t) {
			Vector v(4);

			Vector v2 = v.transpose();
			t.Assert(v2.Length() == 4);
			t.Assert(v2.Width() == v.Height());
			t.Assert(v2.Height() == v.Width());
		})
		.runTests();
}
