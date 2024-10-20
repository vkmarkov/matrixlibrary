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


	//Methods
	void linalg::Matrix::reshape(int rows, int columns) {
		if (rows * columns != m_rows * m_columns) 
			throw std::runtime_error("Number of elements in reshaped matrix must be the same");
		m_rows = rows;
		m_columns = columns;
	}
	 
	//Operators

	Matrix& Matrix::operator=(Matrix other) { //Assignment operator
		std::swap(*this, other);
		return *this;
	}

	std::ostream& operator<<(std::ostream& out, const Matrix& m) { //Output operator
		for (size_t i = 0; i < m.m_rows; ++i) {
			for (size_t j = 0; j < m.m_columns; ++j) {
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

}
