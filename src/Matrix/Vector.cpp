
#include "Vector.h"

#include <stdexcept>

/* constructors */

Vector::Vector(int length) : Matrix(length, 1) {}

Vector::Vector(Vector const &v) : Matrix(v) {}

Vector::Vector(Vector &&v) : Vector(0)
{
	swap(*this, v);
}

Vector::Vector(Matrix const &m) : Matrix(m)
{
	if ((this->Width() != 1) && (this->Height() != 1))
	{
		this->Matrix::~Matrix();
		throw std::invalid_argument("The Matrix needs to have at least one dimension of size 1");
	}
}

Vector::Vector(Matrix &&m) : Matrix(std::move(m))
{
	if ((this->Width() != 1) && (this->Height() != 1))
	{
		this->Matrix::~Matrix();
		throw std::invalid_argument("The Matrix needs to have at least one dimension of size 1");
	}
}

/* assignment */

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

int Vector::Length() const
{
	return this->Width() == 1 ? this->Height() : this->Width();
}

Vector Vector::transpose() const
{
	Matrix m(*this);
	return Vector(m.transpose());
}

Vector operator*(Matrix const &m, Vector const &v) {
	return Vector(m.operator*(v));
}
