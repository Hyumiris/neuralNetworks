
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
			Vector v1(4);
			Vector v2 = v1.transpose();
			t.Assert(v2.Width() == v1.Height());
			t.Assert(v2.Height() == v1.Width());
		})
		.addTest("dot product", [](TestAssistant &t) {
			Vector v_col(3);
			v_col(0, 0) = 1.0;
			v_col(1, 0) = 2.0;
			v_col(2, 0) = 3.0;
			Vector v_row = v_col.transpose();

			t.Assert(v_row.dot(v_col) == 14.0);
		})
		.runTests();
}
