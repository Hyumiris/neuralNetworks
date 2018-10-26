
#include "Matrix.h"

#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

int __MATRIX_COUNT = 0;
int __MATRIX_DATA_COUNT = 0;
/*
------------------------------------------------- constructors
*/

Matrix::Matrix(int height, int width)
{
	if (width < 0 && height < 0)
	{
		throw std::out_of_range("width or height are negative");
	}
	_width = width;
	_height = height;
	_data = new double[_width * _height];
	__MATRIX_DATA_COUNT++;
	fill(begin(), end(), 0.0);
	__MATRIX_COUNT++;
}

Matrix::Matrix(Matrix const &m) : Matrix(m._height, m._width)
{
	copy(m.begin(), m.end(), begin());
}

Matrix::Matrix(Matrix &&m) : Matrix(0, 0)
{
	swap(*this, m);
}

/*
------------------------------------------------- assignment
*/

void swap(Matrix &m1, Matrix &m2)
{
	using std::swap;
	swap(m1._width, m2._width);
	swap(m1._height, m2._height);
	swap(m1._data, m2._data);
}

Matrix &Matrix::operator=(Matrix m)
{
	swap(*this, m);
	return *this;
}

/*
------------------------------------------------- accessors
*/

double &Matrix::operator()(int h, int w)
{
	return _data[_width * h + w];
}

double *Matrix::operator[](int h)
{
	return _data + (_width * h);
}

double Matrix::operator()(int h, int w) const
{
	return _data[_width * h + w];
}

double const *Matrix::operator[](int h) const
{
	return _data + (_width * h);
}

/*
------------------------------------------------- per element arithmetic
*/

Matrix const &Matrix::operator+=(Matrix const &m)
{
	if (m._width != _width || m._height != _height)
	{
		throw std::invalid_argument("Matrices have unequal size");
	}

	for (int h = _height - 1; h >= 0; --h)
		for (int w = _width - 1; w >= 0; --w)
			(*this)(h, w) += m(h, w);

	return *this;
}

Matrix const &Matrix::operator-=(Matrix const &m)
{
	if (m._width != _width || m._height != _height)
	{
		throw std::invalid_argument("Matrices have unequal size");
	}

	for (int h = _height - 1; h >= 0; --h)
		for (int w = _width - 1; w >= 0; --w)
			(*this)(h, w) -= m(h, w);

	return *this;
}

/*
------------------------------------------------- matrix operations
*/

Matrix const &Matrix::operator*=(Matrix const &m)
{
	if (m._height != _width)
	{
		throw std::invalid_argument("Matrix sizes do not match");
	}
	int commonLength = _width;

	Matrix tmp = Matrix(_height, m._width);

	for (int h = tmp._height - 1; h >= 0; --h)
		for (int w = tmp._width - 1; w >= 0; --w)
			for (int k = commonLength - 1; k >= 0; --k)
				tmp(h, w) += (*this)(h, k) * m(k, w);

	*this = std::move(tmp);
	return *this;
}

Matrix Matrix::transpose() const
{
	Matrix m = Matrix(_width, _height);

	for (int w = _width - 1; w >= 0; --w)
		for (int h = _height - 1; h >= 0; --h)
			m(w, h) = (*this)(h, w);

	return m;
}

/*
------------------------------------------------- testing
*/

void Matrix::print() const
{
	for (int h = 0; h < _height; h++)
	{
		cout << "| ";
		for (int w = 0; w < _width; w++)
			cout << (*this)(h, w) << " ";
		cout << "|" << endl;
	}
}

/*
------------------------------------------------- non-member operator
*/

bool operator==(Matrix const &m1, Matrix const &m2)
{
	return &m1 == &m2 || (m1.Width() == m2.Width() &&
						  m1.Height() == m2.Height() &&
						  equal(m1.begin(), m1.end(), m2.begin()));
}
bool operator!=(Matrix const &m1, Matrix const &m2) { return !(m1 == m2); }

Matrix operator+(Matrix const &m1, Matrix const &m2)
{
	Matrix retVal(m1);
	retVal += m2;
	return retVal;
}
Matrix operator-(Matrix const &m1, Matrix const &m2)
{
	Matrix retVal(m1);
	retVal -= m2;
	return retVal;
}
Matrix operator*(Matrix const &m1, Matrix const &m2)
{
	Matrix retVal(m1);
	retVal *= m2;
	return retVal;
}
