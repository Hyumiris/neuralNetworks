
#include "Matrix.h"

#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

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
	if (this == &m)
	{
		return true;
	}
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

Matrix const &Matrix::operator*=(Matrix const &m)
{
	if (m._width != _width || m._height != _height)
	{
		throw std::invalid_argument("Matrices have unequal size");
	}

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
