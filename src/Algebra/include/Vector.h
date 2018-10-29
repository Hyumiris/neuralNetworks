
#ifndef vector_h
#define vector_h

#include "Matrix.h"

#include <vector>

class Vector : public Matrix
{
  public:
	/* constructors */
	Vector(int length = 0);
	Vector(Vector const &v);
	Vector(Vector &&v);

	Vector(Matrix const &m);
	Vector(Matrix &&m);

	Vector(std::vector<double> const &v);

	/* assignment */
	friend void swap(Vector &v1, Vector &v2);
	Vector &operator=(Vector v);

	/* accessors */
	double &at(int pos);
	double at(int pos) const;
	using Matrix::at;

	double &operator()(int pos);
	double operator()(int pos) const;
	using Matrix::operator();

	// per element arithmetic
	Vector const &operator+=(Vector const &m);
	Vector const &operator-=(Vector const &m);
	Vector const &operator*=(double d);
	Vector const &operator/=(double d);

	/* accessors */
	int Length() const;

	/* vector properties */
	bool isColVector() const;
	bool isRowVector() const;

	/* Matrix/Vector operations */
	Vector transpose() const;
	double dot(Vector const & v) const;
	static double dot(Vector const & v1, Vector const & v2);

	/* conversion */
	operator std::vector<double>();
};

/* arithmetic */
Vector operator+(Vector const &v1, Vector const &v2);
Vector operator-(Vector const &v1, Vector const &v2);
Vector operator*(Vector const &v, double d);
Vector operator*(double d, Vector const &v);
Vector operator/(Vector const &v, double d);

Vector operator*(Matrix const &m, Vector const &v);

#endif
