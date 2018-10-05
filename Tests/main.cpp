
#include "TestSuite.tpp"

#include "Matrix.h"
#include "NeuralNetwork.h"

#include <algorithm>
#include <stdio.h>
#include <iostream>

struct MatrixTestData
{
	Matrix m;

	MatrixTestData()
	{
		m = Matrix(3, 3);
	}

	~MatrixTestData() {}

	static MatrixTestData *setUp() { return new MatrixTestData(); }
	static void tearDown(MatrixTestData *data) { delete data; }
};

int main()
{
	TestSuite<MatrixTestData> MatrixTests{};

	MatrixTests.addTest("Creation", [](MatrixTestData *d) {
		Matrix m = Matrix(3, 3);
		assert(m.end() - m.begin() == 9);

		Matrix m2 = Matrix(m);
		Matrix m3 = Matrix(&m);

		assert(m2 == m3);
	});
	MatrixTests.addTest("elementAccess", [](MatrixTestData *d) {
		Matrix &m = d->m;

		m(0, 0) = 0.0;
		m(0, 1) = 1.0;
		m(0, 2) = 2.0;

		assert(m[0][1] == 1.0);

		m[1][0] = 3.0;
		m[1][1] = 4.0;
		m[1][2] = 5.0;

		assert(m(1, 2) == 5.0);
	});
	MatrixTests.addTest("constAccess", [](MatrixTestData *d) {
		Matrix const &m = d->m;

		double a = m(0, 0) + m[1][1];
	});
	MatrixTests.addTest("elementWiseOp", [](MatrixTestData *d) {
		const int w = 4;
		const int h = 2;
		const int l = w * h;

		const double min = 3.0;
		const double max = min + l;

		Matrix m1 = Matrix(h, w);
		double counter = min;
		m1.op([&counter](double d) { return counter++; });

		assert(none_of(m1.begin(), m1.end(), [min, max](double d) { return d > max || d < min; }));
		for (double val = 3.0; val < 3.0 + l - 0.1; val += 1.0)
		{
			assert(any_of(m1.begin(), m1.end(), [val](double d) { return d == val; }));
		}
	});

	MatrixTests.runTests();

	return 0;
}
