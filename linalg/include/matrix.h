#pragma once
#include <initializer_list>
#include <iostream>

namespace linalg {

	class Matrix {
	public: //Constructors
		Matrix() noexcept {}
		Matrix(size_t rows);
		Matrix(size_t rows, size_t columns);
		Matrix(const Matrix& m) noexcept;//copy
		Matrix(Matrix&& m) noexcept;//move
		Matrix::Matrix(std::initializer_list<double> lst) noexcept;
		Matrix::Matrix(std::initializer_list<std::initializer_list<double>> lst);

		//Destructor
		~Matrix() { delete[] m_ptr; }

	public: //Methods
		size_t rows() const noexcept { return m_rows; }
		size_t columns() const noexcept { return m_columns; }
		bool empty() const noexcept { return (m_rows == 0); }
		void reshape(int new_rows, int new_columns);

		//Operators
		double& Matrix::operator ()(size_t row, size_t column);
		const double& Matrix::operator ()(size_t row, size_t column) const;

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
	Matrix operator*(const double c, const Matrix& m) noexcept;

	//Assigment operators out of class
	bool operator==(const Matrix& m1, const Matrix& m2);
	bool operator!=(const Matrix& m1, const Matrix& m2);

	//Functions for matrices
	Matrix concatenate(const Matrix& m1, const Matrix& m2); //Вопрос, почему эти функции лежат вне класса
	Matrix transpose(const Matrix& m);
	Matrix uni(size_t n); //Auxiliary function for creating a unit matrix //+
	const Matrix invert(const Matrix& m);
	Matrix power(const Matrix& m, int deg);
}