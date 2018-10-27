
#include "Vector.h"

#include <stdexcept>
#include <algorithm>

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

/* accessors */

double &Vector::at(int pos)
{
	return this->isColVector() ? this->at(pos, 0) : this->at(0, pos);
}

double Vector::at(int pos) const
{
	return this->isColVector() ? this->at(pos, 0) : this->at(0, pos);
}

double &Vector::operator()(int pos)
{
	return this->isColVector() ? (*this)(pos, 0) : (*this)(0, pos);
}

double Vector::operator()(int pos) const
{
	return this->isColVector() ? (*this)(pos, 0) : (*this)(0, pos);
}

/* per element arithmetic */

Vector const &Vector::operator+=(Vector const &m)
{
	this->Matrix::operator+=(m);
	return *this;
}

Vector const &Vector::operator-=(Vector const &m)
{
	this->Matrix::operator-=(m);
	return *this;
}

Vector const &Vector::operator*=(double d)
{
	this->Matrix::operator*=(d);
	return *this;
}

Vector const &Vector::operator/=(double d)
{
	this->Matrix::operator/=(d);
	return *this;
}

/* vector properties */

bool Vector::isColVector() const
{
	return Width() == 1;
}

bool Vector::isRowVector() const
{
	return Height() == 1;
}

Vector Vector::transpose() const
{
	return Vector(this->Matrix::transpose());
}

double Vector::dot(Vector const &v) const
{
	if (!this->isRowVector() || !v.isColVector() || (Width() != v.Height()))
	{
		throw std::invalid_argument("the dot product can only be used on a row and a column vector of equal size");
	}

	double result;
	for (int i = Width() - 1; i >= 0; --i)
	{
		result += (*this)(0, i) * v(i, 0);
	}

	return result;
}

double Vector::dot(Vector const &v1, Vector const &v2)
{
	return v1.dot(v2);
}

Vector operator+(Vector const &v1, Vector const &v2)
{
	Vector v(v1);
	v += v2;
	return v;
}

Vector operator-(Vector const &v1, Vector const &v2)
{
	Vector v(v1);
	v -= v2;
	return v;
}

Vector operator*(Vector const &v, double d)
{
	Vector retVal(v);
	retVal *= d;
	return retVal;
}

Vector operator*(double d, Vector const &v)
{
	Vector retVal(v);
	retVal *= d;
	return retVal;
}

Vector operator/(Vector const &v, double d)
{
	Vector retVal(v);
	retVal /= d;
	return retVal;
}

Vector operator*(Matrix const &m, Vector const &v)
{
	return Vector(m * (Matrix const &)v);
}
