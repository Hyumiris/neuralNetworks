
#ifndef vector_h
#define vector_h

#include "Matrix.h"

class Vector : public Matrix
{
  public:

	Vector(int length = 0);
	Vector(Vector const& v);
	Vector(Vector &&v);

	friend void swap(Vector& v1, Vector& v2);
	Vector& operator=(Vector v);

};

#endif
