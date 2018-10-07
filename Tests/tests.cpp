
#include <Matrix.h>

#include "TestSuite.h"

class MatrixTestAssistant : public TestAssistant
{
	Matrix m;

  public:
	virtual void SetUp()
	{
		double count = 0.0;
		m = Matrix(3, 3);
		m.op([&count](double d){ return count++; });
	};
	virtual void TearDown(){};
	virtual void *getData()
	{
		return &m;
	}
};

int main()
{

	TestSuite_t<MatrixTestAssistant, TestCase>()
		.addTest("Constructors", [](TestAssistant &t) {
			Matrix m = Matrix(3, 3);
			assert(m.Width() == 3);
			assert(m.Height() == 3);

			Matrix m2 = Matrix(m);
			Matrix m3 = Matrix(&m);

			assert(m2 == m3);
		})
		.addTest("Assignment", [](TestAssistant &t) {
			Matrix &m3x3 = *(Matrix *)t.getData();

			Matrix m = m3x3;
			assert(&m != &m3x3);
			assert(m == m3x3);
		})
		.addTest("Comparision", [](TestAssistant &t) {
			Matrix &m3x3 = *(Matrix *)t.getData();
			Matrix m = m3x3;
			assert(m == m3x3);
			m(0, 0) += .1;
			assert(m != m3x3);
		})
		.addTest("elementAccess", [](TestAssistant &t) {
			Matrix &m3x3 = *(Matrix *)t.getData();

			m3x3(0, 0) = 0.0;
			m3x3(0, 1) = 1.0;
			m3x3(0, 2) = 2.0;

			assert(m3x3[0][1] == 1.0);

			m3x3[1][0] = 3.0;
			m3x3[1][1] = 4.0;
			m3x3[1][2] = 5.0;

			assert(m3x3(1, 2) == 5.0);
		})
		.addTest("constAccess", [](TestAssistant &t) {
			Matrix const& m3x3 = *(Matrix*)t.getData();
			assert(m3x3(1, 2) == m3x3[1][2]);
		})
		.addTest("elementWiseOp", [](TestAssistant &t) {
			const int w = 4;
			const int h = 2;
			const int l = w * h;

			const double min = 3.0;
			const double max = min + l;

			Matrix m1 = Matrix(h, w);
			double counter = min;
			m1.op([&counter](double d) { return counter++; });

			assert(none_of(m1.begin(), m1.end(), [min, max](double d) { return d > max || d < min; }));
			for (double val = min; val < max - 0.1; val++)
			{
				assert(any_of(m1.begin(), m1.end(), [val](double d) { return d == val; }));
			}
		})
		.addTest("Arithmetic", [](TestAssistant &t) {
			Matrix& m1 = *(Matrix*)t.getData();
			Matrix m2 = m1;

			fill(m1.begin(), m1.end(), 1.0);
			fill(m2.begin(), m2.end(), 2.0);

			m1 += m2;
			assert(all_of(m1.begin(), m1.end(), [](double d) { return d == 3.0; }));

			m1 *= m2;
			assert(all_of(m1.begin(), m1.end(), [](double d) { return d == 6.0; }));

			m1 -= m2;
			assert(all_of(m1.begin(), m1.end(), [](double d) { return d == 4.0; }));
		})
		.addTest("Transpose", [](TestAssistant &t) {
			double count = 0.0;
			Matrix m34 = Matrix(3, 4);
			m34.op([&count](double d) { return count++; });
			Matrix &m43 = m34.transpose();

			for (int h = 0; h < m34.Height(); ++h)
				for (int w = 0; w < m34.Width(); ++w)
					assert(m34(h, w) == m43(w, h));
		})
		.runTests();

	return 0;
}
