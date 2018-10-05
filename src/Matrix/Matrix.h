
#ifndef Matrix_h
#define Matrix_h

class Matrix
{
  public:
	// constructors
	Matrix(int _height = 0, int _width = 0);
	Matrix(Matrix const &m);
	Matrix(Matrix const *m) : Matrix(*m) {}

	// destructor
	~Matrix() { delete[] _data; }

	// assignment
	// does a copy of all elements
	Matrix &operator=(Matrix const &m);

	// comparision
	bool operator==(Matrix const &m);
	bool operator!=(Matrix const &m) { return !this->operator==(m); }

	// accessors
	int Width() const { return _width; }
	int Height() const { return _height; }

	// accessing the elements
	double &operator()(int h, int w);
	double *operator[](int h);
	double operator()(int h, int w) const;
	double const *operator[](int h) const;

	// general per element operation

	template <typename func_type>
	Matrix const &op(func_type fn);
	template <typename func_type>
	Matrix &op(Matrix const &m, func_type fn);

	// per element arithmetic
	Matrix const &operator+=(Matrix const &m);
	Matrix const &operator-=(Matrix const &m);
	Matrix const &operator*=(Matrix const &m);

	Matrix &operator+(Matrix const &m) const;
	Matrix &operator-(Matrix const &m) const;
	Matrix &operator*(Matrix const &m) const;

	// Matrix operatins
	Matrix &transpose() const;
	Matrix &mult(Matrix const &m);

	// simple output
	void print() const;

	// stl minimum
	double *begin() { return _data; }
	double *end() { return _data + (_width * _height); }
	double const *begin() const { return _data; }
	double const *end() const { return _data + (_width * _height); }

  private:
	int _width;
	int _height;

	double *_data;
};

#include "Matrix.tpp"

#endif
