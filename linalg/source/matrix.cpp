#include "matrix.h"
#include <iostream>

namespace linalg {

	// Constructors
	Matrix::Matrix(size_t rows) {
		if (rows < 0)
			throw std::runtime_error("The matrix cannot be with a negative number of rows");
		m_rows = rows;
		m_ptr = new double[rows];
	}

	Matrix::Matrix(size_t rows, size_t columns) {
		if ((rows < 0) || (columns < 0))
			throw std::runtime_error("The matrix cannot be with a negative number of rows or columns");
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
	
	Matrix& Matrix::operator+=(const Matrix& m) {
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

	Matrix& Matrix::operator-=(const Matrix& m) {
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

	Matrix& Matrix::operator*=(const Matrix& m) {
		*this = *this * m;
		return *this;
	}

	static bool equal(const double& a, const double& b) { return std::fabs(a - b) < 1e-10; }

	bool operator==(const Matrix& m1, const Matrix& m2) {
		if ((m1.rows() != m2.rows()) || (m1.columns() != m2.columns())) 
			return false;
		for (size_t i = 0; i < m1.rows(); ++i) {
			for (size_t j = 0; j < m1.columns(); ++j) {
				if (!equal(m1(i, j), m2(i, j))) return false; 
			}
		}
		return true;
	}

	bool operator !=(const Matrix& m1, const Matrix& m2) { return !(m1 == m2); }


	//Methods

	void linalg::Matrix::reshape(int rows, int columns) {
		if (rows * columns != m_rows * m_columns)
			throw std::runtime_error("Number of elements in reshaped matrix must be the same");
		m_rows = rows;
		m_columns = columns;
	}

	//Methods for matrices

	double Matrix::norm() const { //Norm
		if (empty()) 
			throw std::runtime_error("Matrix is empty");
		double res = 0;
		for (size_t i = 0; i < m_rows; ++i) {
			for (size_t j = 0; j < m_columns; ++j) {
				res += m_ptr[i * m_columns + j] * m_ptr[i * m_columns + j];
			}
		}
		return sqrt(res);
	}

	double Matrix::trace() const { //Trace
		if (empty())
			throw std::runtime_error("Matrix is empty");
		if (m_rows != m_columns)
			throw std::runtime_error("Matrix is not square");
		double res = 0;
		for (int i = 0; i < m_rows; ++i) {
			res += m_ptr[i * m_columns + i];
		}
		return res;
	}

	Matrix Matrix::Gauss(bool rref) const { //Gauss
		Matrix res = *this;
		for (size_t i = 0; i < res.m_rows && i < res.m_columns; ++i) { 
			size_t max_row = i;
			for (size_t j = i + 1; j < res.m_rows; ++j) {
				if (std::fabs(res(j, i)) > std::fabs(res(max_row, i))) {
					max_row = j;
				}
			}
			if (max_row != i) {
				for (size_t j = 0; j < res.m_columns; ++j) {
					std::swap(res(i, j), res(max_row, j));
					res(i, j) *= -1;
				}
			}
			if (res(i, i) == 0) {
				continue;   
			}
			if (rref) { //Reduced Row Echelon Form (уменьшенная ступенчатая форма матрицы)
				double coef = res(i, i);
				for (size_t j = i; j < res.m_columns; ++j) {
					res(i, j) /= coef;
				}
			}   
			for (size_t j = rref ? 0 : i + 1; j < res.m_rows; ++j) {
				if (i != j) {
					double coef = res(j, i) / res(i, i);
					for (size_t k = 0; k < res.m_columns; k++) {
						res(j, k) -= res(i, k) * coef;
					}
				}
			}
		}
		return res;
	}

	double Matrix::det() const {
		if (empty()) 
			throw std::runtime_error("Matrix is empty"); //вопрос как вызывается throw
		if (rows() != columns()) 
			throw std::runtime_error("The matrix should be square");
		Matrix d = *this; //либо -> для yhis
		Matrix m = d.Gauss(false);
		double opr = 1;
		for (size_t i = 0; i < m.columns(); i++) {
			opr *= m(i, i);
		}
		return opr;
	}


}