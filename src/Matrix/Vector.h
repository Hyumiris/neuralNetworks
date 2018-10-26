
#ifndef vector_h
#define vector_h

#include "Matrix.h"

class Vector : public Matrix
{
  public:
	/* constructors */
	Vector(int length = 0);
	Vector(Vector const &v);
	Vector(Vector &&v);

	Vector(Matrix const &m);
	Vector(Matrix &&m);

	/* assignment */
	friend void swap(Vector &v1, Vector &v2);
	Vector &operator=(Vector v);

	// per element arithmetic
	Vector const &operator+=(Vector const &m);
	Vector const &operator-=(Vector const &m);
	Vector const &operator*=(double d);
	Vector const &operator/=(double d);

	/* accessors */
	int Length() const;

	Vector transpose() const;
};

Vector operator+(Vector const &v1, Vector const &v2);
Vector operator-(Vector const &v1, Vector const &v2);
Vector operator*(Vector const &v, double d);
Vector operator*(double d, Vector const &v);
Vector operator/(Vector const &v, double d);

Vector operator*(Matrix const &m, Vector const &v);

#endif
