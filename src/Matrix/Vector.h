
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

	/* accessors */
	int Length() const;

	Vector transpose() const;
};

Vector operator*(Matrix const &m, Vector const &v);

#endif
