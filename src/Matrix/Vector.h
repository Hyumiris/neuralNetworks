
#ifndef vector_h
#define vector_h

#include "Matrix.h"

class Vector : Matrix
{
  public:

	Vector(int length);
	Vector(Vector const& v);
	Vector(Vector &&v);

	~Vector();

	friend void swap(Vector& v1, Vector& v2);
	Vector& operator=(Vector v);

};

#endif
