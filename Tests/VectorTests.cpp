
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
		.addTest("Vector-Vector mult", [](TestAssistant &t) {
			double c = 0.0;
			Vector v1(5);
			v1.op([&c](double d) { return c++; });
			Vector v2(v1.transpose());

			Matrix m1 = v1.mult(v2);
			Matrix m2 = v2.mult(v1);

			t.Assert(m1.Width() == 5 && m1.Height() == 5);
			t.Assert(m2.Width() == 1 && m2.Height() == 1);
		})
		.addTest("Vector-Matrix mult", [](TestAssistant &t) {
			Vector v1(5);
			Vector v2(v1.transpose());

			Matrix m1 = v1.mult(v2);
			Matrix m2 = v2.mult(v1);

			t.Assert(m1.Width() == 5 && m1.Height() == 5);
			t.Assert(m2.Width() == 1 && m2.Height() == 1);
		})
		.runTests();
}
