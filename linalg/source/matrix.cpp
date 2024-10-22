#include "matrix.h"
#include <iostream>

namespace linalg {

	// Constructors
	Matrix::Matrix(size_t rows) noexcept {
		m_rows = rows;
		m_ptr = new double[rows];
	}

	Matrix::Matrix(size_t rows, size_t columns) noexcept {
		m_rows = rows;
		m_columns = columns;
		m_ptr = new double[rows * columns];
	}

	Matrix::Matrix(const Matrix& m) noexcept {
		m_rows = m.m_rows;
		m_columns = m.m_columns;
		m_ptr = new double[m_rows * m_columns];
		for (size_t i = 0; i < m_rows * m_columns; ++i) {
			m_ptr[i] = m.m_ptr[i];
		}
	}

	Matrix::Matrix(Matrix&& m) noexcept {
		std::swap(m_ptr, m.m_ptr);
		std::swap(m_rows, m.m_rows);
		std::swap(m_columns, m.m_columns);
	}

	//One-dimensional matrix
	Matrix::Matrix(std::initializer_list<double> lst) noexcept {
		m_ptr = new double[lst.size()];
		m_rows = lst.size();
		m_columns = 1;
		size_t i = 0;
		for (double el : lst) {
			m_ptr[i++] = el;
		}
	}

	//Multidimensional matrix
	Matrix::Matrix(std::initializer_list<std::initializer_list<double>> lst) {
		m_ptr = new double[lst.size() * lst.begin()->size()];
		m_rows = lst.size();
		m_columns = lst.begin()->size();
		size_t i = 0;
		for (std::initializer_list row : lst) {
			if (row.size() != lst.begin()->size()) {
				throw std::runtime_error("All rows must have the same number of columns");
			}
			for (double el : row) {
				m_ptr[i++] = el;
			}
		}
	}


	//Methods
	void linalg::Matrix::reshape(int rows, int columns) {
		if (rows * columns != m_rows * m_columns) 
			throw std::runtime_error("Number of elements in reshaped matrix must be the same");
		m_rows = rows;
		m_columns = columns;
	}
	 
	//Operators

	std::ostream& operator<<(std::ostream& out, const Matrix& m) { //Output operator
		for (size_t i = 0; i < m.rows(); ++i) {
			for (size_t j = 0; j < m.columns(); ++j) {
				out << m(i, j) << ' ';
			}
			out << '\n';
		}
		return out;
	}
	
	double& Matrix::operator ()(size_t row, size_t column) { // Index operator for non-constant with 2 parameter
		if (row >= m_rows || column >= m_columns) {
			throw std::out_of_range("Index out of range");
		}
		return m_ptr[row * m_columns + column];
	}

	const double& Matrix::operator ()(size_t row, size_t column) const { //for constant with 2 parameter 
		if (row >= m_rows || column >= m_columns) {
			throw std::out_of_range("Index out of range");
		}
		return m_ptr[row * m_columns + column];
	}

	Matrix& Matrix::operator=(Matrix other) noexcept { //Assignment operator
		std::swap(*this, other);
		return *this;
	}

	//Arifmetic operators
	Matrix operator+(const Matrix& m1, const Matrix& m2) {
		if (m1.rows() != m2.rows() || m1.columns() != m2.columns()) 
			throw std::runtime_error("Matrix's size is incorrect");
		Matrix res(m1.rows(), m1.columns());
		for (size_t i = 0; i < m1.rows(); ++i) {
			for (size_t j = 0; j < m1.columns(); ++j) {
				res(i, j) = m1(i, j) + m2(i,j);
			}
		}
		return res;
	}
	
	Matrix& Matrix::operator+=(const Matrix& m) noexcept {
		*this = *this + m;
		return *this;
	}

	Matrix operator*(const Matrix& m, const double c) noexcept {
		Matrix res(m.rows(), m.columns());
		for (size_t i = 0; i < m.rows(); ++i) {
			for (size_t j = 0; j < m.columns(); ++j) {
				res(i, j) = m(i, j) * c;
			}
		}
		return res;
	}

	Matrix operator*(const double c, const Matrix& m) noexcept {
		return m * c;
	}

	Matrix operator-(const Matrix& m1, const Matrix& m2) {
		if ((m1.rows() != m2.rows()) || (m1.columns() != m2.columns()))
			throw std::runtime_error("Matrix sizes are different");
	}

	Matrix& Matrix::operator-=(const Matrix& m) noexcept {
		*this = *this - m; //move operator
		return *this;
	};

	Matrix& Matrix::operator*=(const double c) noexcept {
		*this = *this * c;
		return *this;
	}

	Matrix operator*(const Matrix& m1, const Matrix& m2) {
		if (m1.columns() != m2.rows()) 
			throw std::runtime_error("The sizes of the matrices are different"); 
		Matrix res(m1.rows(), m2.columns());
		for (size_t i = 0; i < res.rows(); ++i) {
			for (size_t j = 0; j < res.columns(); ++j) {
				res(i, j) = 0;
				for (size_t k = 0; k < m1.columns(); ++k) {
					res(i, j) += m1(i, k) * m2(k, j);
				}
			}
		}
		return res;
	}

	Matrix& Matrix::operator*=(const Matrix& m) noexcept {
		*this = *this * m;
		return *this;
	}

	
}