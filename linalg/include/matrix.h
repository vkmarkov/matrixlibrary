/**
 * @mainpage
 *
 * @section intro_sec Introduction
 *
 * Matrix is a C++ library for working with matrices. It provides a simple and
 * efficient way to perform common matrix operations, such as addition,
 * multiplication, and inversion. The library is designed to be easy to use and
 * provides a lot of useful functions for working with matrices.
 *
 * @section features_sec Features
 *
 * The main features of the library are:
 * - Matrix operations: addition, subtraction, multiplication, division,
 *   determinant, inverse, transpose, rank, etc.
 *
 * @section requirements_sec Requirements
 *
 * The library requires C++17 or higher to compile.
 *
 * @section example_sec Example
 *
 * Here is an example of how to use the library:
 *
 * @code
 * #include <iostream>
 * #include "matrix.h"
 *
 * int main() {
 *     linalg::Matrix a(2, 2);
 *     a(0, 0) = 1;
 *     a(0, 1) = 2;
 *     a(1, 0) = 3;
 *     a(1, 1) = 4;
 *
 *     Matrix b = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
 *     Matrix c = linalg::power(b, 2);
 *     std::cout << b << c;
 *     return 0;
 * }
 * @endcode
 */

#pragma once
#include <initializer_list>
#include <iostream>

namespace linalg {

	class Matrix {
	public: //Constructors
		Matrix() noexcept = default;
		Matrix(size_t rows);
		Matrix(size_t rows, size_t columns);
		Matrix(const Matrix& m) noexcept;//copy
		Matrix(Matrix&& m) noexcept;//move
		Matrix(std::initializer_list<double> lst) noexcept;
		Matrix(std::initializer_list<std::initializer_list<double>> lst);

		//Destructor
		~Matrix() { delete[] m_ptr; }

	public: //Methods
		size_t rows() const noexcept { return m_rows; }
		size_t columns() const noexcept { return m_columns; }
		bool empty() const noexcept { return (m_rows == 0); }
		void reshape(size_t new_rows, size_t new_columns);

		//Operators
		double& operator()(size_t row, size_t column);
		const double& operator()(size_t row, size_t column) const;

		//Assignment and arifmetic operators
		Matrix& operator=(Matrix m) noexcept;
		
		Matrix& operator+=(const Matrix& m);
		Matrix& operator-=(const Matrix& m);
		Matrix& operator*=(const double c) noexcept;
		Matrix& operator*=(const Matrix& m);

		//Methods for matrices
		double trace() const;
		double norm() const;
		Matrix Gauss(bool rref) const; //+
		double det() const;
		double minor(size_t rows, size_t columns) const; //+

	private: //Fields
		double* m_ptr = nullptr;
		size_t m_rows = 0;
		size_t m_columns = 0;
	};

	//The output operator
	std::ostream& operator<<(std::ostream&, const Matrix&);

	//Arifmetic operators
	Matrix operator+(const Matrix& m1, const Matrix& m2);
	Matrix operator-(const Matrix& m1, const Matrix& m2);
	Matrix operator*(const Matrix& m1, const Matrix& m2);
	Matrix operator*(const Matrix& m, const double c) noexcept;
	Matrix operator*(const double c, const Matrix& m) noexcept; ///delat

	//Assigment operators out of class
	bool operator==(const Matrix& m1, const Matrix& m2);
	bool operator!=(const Matrix& m1, const Matrix& m2);

	//Functions for matrices
	Matrix concatenate(const Matrix& m1, const Matrix& m2); //Вопрос, почему эти функции лежат вне класса
	Matrix transpose(const Matrix& m);
	Matrix uni(size_t n); //Auxiliary function for creating a unit matrix //+
	const Matrix invert_old(const Matrix& m);
	Matrix invert(const Matrix& m);
	Matrix power(const Matrix& m, int deg);
}