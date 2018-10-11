
#include "Matrix.h"

#include <stdexcept>
#include <iostream>

template <typename func_type>
Matrix const &Matrix::op(func_type fn)
{
	for (int h = _height - 1; h >= 0; --h)
		for (int w = _width - 1; w >= 0; --w)
			(*this)(h, w) = fn((*this)(h, w));

	return *this;
}

template <typename func_type>
Matrix &Matrix::op(Matrix const &m, func_type fn)
{
	if (m._width != _width || m._height != _height)
	{
		throw std::invalid_argument("Matrices have unequal size");
	}

	for (int h = _height - 1; h >= 0; --h)
		for (int w = _width - 1; w >= 0; --w)
			(*this)(h, w) = fn((*this)(h, w), m(h, w));

	return *this;
}

template <typename t1, typename t2>
void Matrix::printState(t1 name, t2 add) const
{
	std::cout << name << ": " << this << " [" << this->_data << "]";
	std::cout << "   (" << _height << "|" << _width << ")";
	if (add)
	{
		std::cout << "   (" << add << ")";
	}
	std::cout << std::endl;
}
