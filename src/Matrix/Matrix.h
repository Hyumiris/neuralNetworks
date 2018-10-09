
#ifndef Matrix_h
#define Matrix_h

extern int __MATRIX_COUNT;
extern int __MATRIX_DATA_COUNT;

class Matrix
{
  public:
	// constructors
	Matrix(int _height = 0, int _width = 0);
	Matrix(Matrix const &m);
	Matrix(Matrix &&m);

	// destructor
	~Matrix()
	{
		delete[] _data;
		_data = nullptr;
		_width = 0;
		_height = 0;
		__MATRIX_DATA_COUNT--;
		__MATRIX_COUNT--;
	}

	// assignment
	// does a copy of all elements
	friend void swap(Matrix &m1, Matrix &m2);
	Matrix &operator=(Matrix m);

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
	Matrix transpose() const;
	Matrix mult(Matrix const &m);
	static Matrix mult(Matrix const &m1, Matrix const &m2);

	// simple output
	void print() const;

	template <typename t1, typename t2>
	void printState(t1 name, t2 add);

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
