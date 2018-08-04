
#include "Matrix.h"

#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

/*
------------------------------------------------- constructors
*/

Matrix::Matrix(int height, int width)
{
	assert(width >= 0 && height >= 0);
	_width = width;
	_height = height;
	_data = new double[_width * _height];
	fill(begin(), end(), 0.0);
}

Matrix::Matrix(Matrix const &m) : Matrix(m._height, m._width)
{
	copy(m.begin(), m.end(), begin());
}

/*
------------------------------------------------- assignment
*/

Matrix &Matrix::operator=(Matrix const &m)
{
	if (this == &m)
		return *this;
	delete[] _data;
	_width = m._width;
	_height = m._height;
	_data = new double[_width * _height];
	copy(m.begin(), m.end(), begin());
	return *this;
}

/*
------------------------------------------------- comparision
*/

bool Matrix::operator==(Matrix const &m)
{
	if (_width != m._width)
	{
		return false;
	}
	if (_height != m._height)
	{
		return false;
	}
	return equal(begin(), end(), m.begin());
}

/*
------------------------------------------------- accessors
*/

double &Matrix::operator()(int h, int w)
{
	assert(h >= 0 && w >= 0);
	assert(h < _height && w < _width);
	return _data[_width * h + w];
}

double *Matrix::operator[](int h)
{
	assert(h > 0 && h < _height);
	return _data + (_width * h);
}

double Matrix::operator()(int h, int w) const
{
	assert(h >= 0 && w >= 0);
	assert(h < _height && w < _width);
	return _data[_width * h + w];
}

double const *Matrix::operator[](int h) const
{
	assert(h > 0 && h < _height);
	return _data + (_width * h);
}

/*
------------------------------------------------- per element operation
*/

Matrix const &Matrix::op(double (*fn)(double))
{
	for (int h = _height - 1; h >= 0; --h)
		for (int w = _width - 1; w >= 0; --w)
			(*this)(h, w) = fn((*this)(h, w));

	return *this;
}

Matrix &Matrix::op(Matrix const &m, double (*fn)(double, double))
{
	assert(m._width == _width);
	assert(m._height == _height);

	for (int h = _height - 1; h >= 0; --h)
		for (int w = _width - 1; w >= 0; --w)
			(*this)(h, w) = fn((*this)(h, w), m(h, w));

	return *this;
}

/*
------------------------------------------------- per element arithmetic
*/

Matrix const &Matrix::operator+=(Matrix const &m)
{
	assert(m._width == _width);
	assert(m._height == _height);

	for (int h = _height - 1; h >= 0; --h)
		for (int w = _width - 1; w >= 0; --w)
			(*this)(h, w) += m(h, w);

	return *this;
}

Matrix const &Matrix::operator-=(Matrix const &m)
{
	assert(m._width == _width);
	assert(m._height == _height);

	for (int h = _height - 1; h >= 0; --h)
		for (int w = _width - 1; w >= 0; --w)
			(*this)(h, w) -= m(h, w);

	return *this;
}

Matrix const &Matrix::operator*=(Matrix const &m)
{
	assert(m._width == _width);
	assert(m._height == _height);

	for (int h = _height - 1; h >= 0; --h)
		for (int w = _width - 1; w >= 0; --w)
			(*this)(h, w) *= m(h, w);

	return *this;
}

Matrix &Matrix::operator+(Matrix const &m) const
{
	Matrix &retVal = *(new Matrix(*this));
	retVal += m;
	return retVal;
}

Matrix &Matrix::operator-(Matrix const &m) const
{
	Matrix &retVal = *(new Matrix(*this));
	retVal -= m;
	return retVal;
}

Matrix &Matrix::operator*(Matrix const &m) const
{
	Matrix &retVal = *(new Matrix(*this));
	retVal *= m;
	return retVal;
}

/*
------------------------------------------------- matrix operations
*/

Matrix &Matrix::transpose() const
{
	Matrix &m = *(new Matrix(_width, _height));

	for (int w = _width - 1; w >= 0; --w)
		for (int h = _height - 1; h >= 0; --h)
			m(w, h) = (*this)(h, w);

	return m;
}

Matrix &Matrix::mult(Matrix const &m)
{
	assert(_width == m._height);
	int commonLength = _width;

	Matrix tmp = Matrix(_height, m._width);

	for (int h = tmp._height - 1; h >= 0; --h)
		for (int w = tmp._width - 1; w >= 0; --w)
			for (int k = commonLength - 1; k >= 0; --k)
				tmp(h, w) += (*this)(h, k) * m(k, w);
	return (*this = tmp);
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
