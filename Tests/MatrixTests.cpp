
#include <TestSuite.h>

#include <Matrix.h>

class MatrixTestAssistant : public TestAssistant
{
	Matrix m;

  public:
	virtual void SetUp()
	{
		double count = 0.0;
		m = Matrix(3, 3);
		m.op([&count](double d) { return count++; });
	}
	virtual void TearDown()
	{
	}
	virtual void *getData()
	{
		return &m;
	}
};

void testMatrix()
{
	TestSuite_t<MatrixTestAssistant, TestCase>()
		.addTest("Constructors", [](TestAssistant &t) {
			Matrix m = Matrix(3, 3);
			t.Assert(m.Width() == 3);
			t.Assert(m.Height() == 3);

			Matrix m2(m);
			t.Assert(m == m2);
			Matrix m3(std::move(m));
			t.Assert(m != m3);

			t.Assert(m2 == m3);
		})
		.addTest("Assignment", [](TestAssistant &t) {
			Matrix &m = *(Matrix *)t.getData();
			Matrix m2, m3;

			m2 = m;
			t.Assert(&m != &m2);
			t.Assert(m == m2);
			m3 = std::move(m);
			t.Assert(&m != &m3);
			t.Assert(m != m3);

			t.Assert(&m2 != &m3);
			t.Assert(m2 == m3);
		})
		.addTest("Comparision", [](TestAssistant &t) {
			Matrix &m3x3 = *(Matrix *)t.getData();
			Matrix m = m3x3;
			t.Assert(m == m3x3);
			m(0, 0) += .1;
			t.Assert(m != m3x3);
		})
		.addTest("elementAccess", [](TestAssistant &t) {
			Matrix &m3x3 = *(Matrix *)t.getData();

			m3x3(0, 0) = 0.0;
			m3x3(0, 1) = 1.0;
			m3x3(0, 2) = 2.0;

			t.Assert(m3x3.at(0, 1) == 1.0);

			m3x3.at(1, 0) = 3.0;
			m3x3.at(1, 1) = 4.0;
			m3x3.at(1, 2) = 5.0;

			t.Assert(m3x3(1, 2) == 5.0);
		})
		.addTest("constAccess", [](TestAssistant &t) {
			Matrix const &m3x3 = *(Matrix *)t.getData();
			t.Assert(m3x3(1, 2) == m3x3.at(1, 2));
		})
		.addTest("elementWiseOp", [](TestAssistant &t) {
			int const w = 4;
			int const h = 2;
			int const l = w * h;

			double const min = 3.0;
			double const max = min + l;

			Matrix m1 = Matrix(h, w);
			Matrix m2 = Matrix(h, w);

			double counter = min;
			m1.op([&counter](double d) { return counter++; });
			m2.op(m1, [](double m2d, double m1d) { return m1d + 1.0; });

			t.Assert(none_of(m1.begin(), m1.end(), [min, max](double d) { return d >= max || d < min; }));
			for (double val = min; val < max - 0.1; val++)
			{
				t.Assert(any_of(m1.begin(), m1.end(), [val](double d) { return d == val; }));
			}

			t.Assert(none_of(m2.begin(), m2.end(), [min, max](double d) { return d >= max + 1.0 || d < min + 1.0; }));
			for (double val = min + 1.0; val < max + 0.9; val++)
			{
				t.Assert(any_of(m2.begin(), m2.end(), [val](double d) { return d == val; }));
			}
		})
		.addTest("Arithmetic", [](TestAssistant &t) {
			Matrix &m1_1 = *(Matrix *)t.getData();
			fill(m1_1.begin(), m1_1.end(), 1.0);
			Matrix m1_2 = m1_1;

			Matrix m2 = Matrix(m1_1.Height(), m1_1.Height());
			fill(m2.begin(), m2.end(), 2.0);

			m1_1 += m2;
			m1_2 = m1_2 + m2;
			t.Assert(all_of(m1_1.begin(), m1_1.end(), [](double d) { return d == 3.0; }));
			t.Assert(all_of(m1_2.begin(), m1_2.end(), [](double d) { return d == 3.0; }));

			m1_1 *= 2.0;
			m1_2 = m1_2 * 2.0;
			m1_2 = 2.0  * m1_2;
			t.Assert(all_of(m1_1.begin(), m1_1.end(), [](double d) { return d == 6.0; }));
			t.Assert(all_of(m1_2.begin(), m1_2.end(), [](double d) { return d == 12.0; }));

			m1_1 /= 2.0;
			m1_2 = m1_2 / 2.0;
			t.Assert(all_of(m1_1.begin(), m1_1.end(), [](double d) { return d == 3.0; }));
			t.Assert(all_of(m1_2.begin(), m1_2.end(), [](double d) { return d == 6.0; }));

			m1_1 -= m2;
			m1_2 = m1_2 - m2;
			t.Assert(all_of(m1_1.begin(), m1_1.end(), [](double d) { return d == 1.0; }));
			t.Assert(all_of(m1_2.begin(), m1_2.end(), [](double d) { return d == 4.0; }));
		})
		.addTest("Transpose", [](TestAssistant &t) {
			double count = 0.0;
			Matrix m34 = Matrix(3, 4);
			m34.op([&count](double d) { return count++; });
			Matrix m43 = m34.transpose(); // 1 ctor, 0 assignment

			for (int h = 0; h < m34.Height(); ++h)
				for (int w = 0; w < m34.Width(); ++w)
					t.Assert(m34(h, w) == m43(w, h));
		})
		.addTest("Mat multiplication", [](TestAssistant &t) {
			double count = 0.0;
			Matrix m34 = Matrix(3, 4);
			m34.op([&count](double d) { return count++; });
			Matrix m43 = m34.transpose();

			Matrix m33;
			Matrix m44;

			m33 = m34 * m43;
			m44 = m43 * m34;

			t.Assert(m33.Width() == 3 && m33.Height() == 3);
			t.Assert(m44.Width() == 4 && m44.Height() == 4);
		})
		.runTests();

	assert(__MATRIX_COUNT == 0);
	assert(__MATRIX_DATA_COUNT == 0);
}
