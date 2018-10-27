
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
		.addTest("mat-vec product", [](TestAssistant &t) {
			Matrix m_translate1(4, 4);
			m_translate1(0, 0) = 1.0;
			m_translate1(1, 1) = 1.0;
			m_translate1(2, 2) = 1.0;
			m_translate1(3, 3) = 1.0;
			m_translate1(0, 3) = 1.0;
			m_translate1(1, 3) = 1.0;
			m_translate1(2, 3) = 1.0;

			Matrix m_scale2(4, 4);
			m_scale2(0, 0) = 2.0;
			m_scale2(1, 1) = 2.0;
			m_scale2(2, 2) = 2.0;
			m_scale2(3, 3) = 1.0;

			Vector vec(4);
			vec(3, 0) = 1.0;

			Vector translateScaleVec = m_scale2 * m_translate1 * vec;
			Vector scaleTranslateVec = m_translate1 * m_scale2 * vec;

			t.Assert(translateScaleVec(0, 0) == 2.0);
			t.Assert(translateScaleVec(1, 0) == 2.0);
			t.Assert(translateScaleVec(2, 0) == 2.0);
			t.Assert(translateScaleVec(3, 0) == 1.0);

			t.Assert(scaleTranslateVec(0, 0) == 1.0);
			t.Assert(scaleTranslateVec(1, 0) == 1.0);
			t.Assert(scaleTranslateVec(2, 0) == 1.0);
			t.Assert(scaleTranslateVec(3, 0) == 1.0);
		})
		.addTest("[const] access", [](TestAssistant &t) {

			Vector v_col = Vector(3);
			v_col(1) = 1.0;
			v_col.at(2) = 2.0;

			Vector v_row = Vector(3).transpose();
			v_row(1) = 1.0;
			v_row.at(2) = 2.0;

			Vector const v_col_c(v_col);
			Vector const v_row_c(v_row);

			t.Assert(v_col.at(1) == 1.0);
			t.Assert(v_col(2) == 2.0);
			t.Assert(v_col(1, 0) == v_col(1));

			t.Assert(v_col_c.at(1) == 1.0);
			t.Assert(v_col_c(2) == 2.0);
			t.Assert(v_col_c(0, 1) == v_col_c(1));

			t.Assert(v_row.at(1) == 1.0);
			t.Assert(v_row(2) == 2.0);
			t.Assert(v_row(0, 1) == v_row(1));

			t.Assert(v_row_c.at(1) == 1.0);
			t.Assert(v_row_c(2) == 2.0);
			t.Assert(v_row_c(0, 1) == v_row_c(1));

			t.Assert(v_col == v_col_c);
			t.Assert(v_row == v_row_c);
			t.Assert(v_col != v_row);
			t.Assert(v_col_c != v_row_c);
		})
		.runTests();
}
