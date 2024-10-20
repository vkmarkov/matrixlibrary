#include "matrix.h"
#include <iostream>

namespace linalg {

	// Constructors
	Matrix::Matrix(size_t rows) {
		if (rows <= 0)
			throw std::invalid_argument("The number of rows of the matrix must be positive");
		m_rows = rows;
		m_ptr = new double[rows];
	}

	Matrix::Matrix(size_t rows, size_t columns) {
		if (rows <= 0 || columns <= 0) throw std::invalid_argument("The number of rows and columns of the matrix must be positive");
		m_rows = rows;
		m_columns = columns;
		m_ptr = new double[rows * columns];
	}

	Matrix::Matrix(const Matrix& m) {
		m_rows = m.m_rows;
		m_columns = m.m_columns;
		m_ptr = new double[m_rows * m_columns];
		for (size_t i = 0; i < m_rows * m_columns; ++i) {
			m_ptr[i] = m.m_ptr[i];
		}
	}

	//Methods
	void linalg::Matrix::reshape(int rows, int columns) {
		if (empty()) throw std::runtime_error("Matrix is empty");
		if (rows <= 0 || columns <= 0) throw std::runtime_error("Invalid value");
		if (rows * columns != m_rows * m_columns) {
			throw std::runtime_error("Number of elements in reshaped matrix must be the same");
		}
		m_rows = rows;
		m_columns = columns;
	}


	
}
