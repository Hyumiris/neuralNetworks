
#include "Vector.h"

Vector::Vector(int length) : Matrix(length, 1) {}

Vector::Vector(Vector const &v) : Matrix(v) {}

Vector::Vector(Vector &&v) : Matrix(0, 0)
{
	swap(*this, v);
}

Vector::~Vector() {}

Vector &Vector::operator=(Vector v)
{
	swap(*this, v);
	return *this;
}

void swap(Vector &v1, Vector &v2)
{
	using std::swap;
	swap((Matrix &)v1, (Matrix &)v2);
}
