
#include "TestSuite.tpp"

#include "Matrix.h"
#include "NeuralNetwork.h"

struct MatrixTestData {
	Matrix m;

	MatrixTestData() {
		m = Matrix(3, 3);
	}

	~MatrixTestData() { }

	static MatrixTestData* setUp() { return new MatrixTestData(); }
	static void tearDown(MatrixTestData* data) { delete data; }
};

int main()
{
	TestSuite<MatrixTestData> MatrixTests{};

	MatrixTests.addTest("Creation", [] (MatrixTestData* d) {
		Matrix m = Matrix(3, 3);
		assert(m.end() - m.begin() == 9);

		Matrix m2 = Matrix(m);
		Matrix m3 = Matrix(&m);

		assert(m2 == m3);
		return;
	});

	MatrixTests.runTests();

	return 0;
}
