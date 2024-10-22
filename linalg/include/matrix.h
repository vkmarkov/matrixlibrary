#pragma once
#include <initializer_list>
#include <iostream>

namespace linalg {

	class Matrix {
	public: //Constructors
		Matrix() noexcept {}
		Matrix(size_t rows) noexcept;
		Matrix(size_t rows, size_t columns) noexcept;
		Matrix(const Matrix& m) noexcept;
		Matrix(Matrix&& m) noexcept;
		Matrix::Matrix(std::initializer_list<double> lst) noexcept;
		Matrix::Matrix(std::initializer_list<std::initializer_list<double>> lst);

		//Destructor
		~Matrix() { delete[] m_ptr; }

	public: //Methods
		size_t rows() const noexcept { return m_rows; }
		size_t columns() const noexcept { return m_columns; }
		bool empty() const noexcept { return (m_rows == 0); }
		void reshape(int new_rows, int new_columns);
		double& Matrix::operator ()(size_t row, size_t column);
		const double& Matrix::operator ()(size_t row, size_t column) const;

	public: //Assignment and arifmetic operators
		Matrix& operator=(Matrix m) noexcept;
		Matrix& operator+=(const Matrix& m) noexcept;
		Matrix& operator-=(const Matrix& m) noexcept;
		Matrix& operator*=(const double c) noexcept;
		Matrix& operator*=(const Matrix& m) noexcept;

	private: //Fields
		double* m_ptr = nullptr;
		size_t m_rows = 0;
		size_t m_columns = 0;
	};

	std::ostream& operator<<(std::ostream&, const Matrix&);

	//Arifmetic operators
	Matrix operator+(const Matrix& m1, const Matrix& m2);
	Matrix operator-(const Matrix& m1, const Matrix& m2);
	Matrix operator*(const Matrix& m1, const Matrix& m2);
	Matrix operator*(const Matrix& m, const double c) noexcept;
	Matrix operator*(const double c, const Matrix& m) noexcept;

}