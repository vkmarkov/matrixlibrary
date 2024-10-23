/**
 * @file
 * @brief C++ library for working with matrices
 * @version 0.1.0
 * @date 2024-10-21
 * @authors vmarkov20
 */
#include "matrix.h"
#include <iostream>
#include <iomanip>
#include <sstream>

const double EPS = 1e-10;

namespace linalg {

	// Constructors
	Matrix::Matrix(size_t rows) {
		if (rows < 0)
			throw std::runtime_error("The matrix cannot be with a negative number of rows");
		m_rows = rows;
		m_columns = 1;
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
		for (auto&& row : lst) {
			if (row.size() != lst.begin()->size()) {
				throw std::runtime_error("All rows must have the same number of columns");
			}
			for (double el : row) {
				m_ptr[i++] = el;
			}
		}
	}

	//Operators
	
	size_t max_length_first(const Matrix& m, const std::ostream& out) { //maximum length of an element in 1st column
		size_t max_number_of_digits = 0;
		std::stringstream sout;
		sout << std::setiosflags(out.flags()) << std::setprecision(out.precision()); // flags and precision from out
		for (size_t i = 0; i < m.rows(); ++i) {
			sout << m(i, 0);
			size_t length = sout.str().size();
			if (max_number_of_digits < length) {
				max_number_of_digits = length;
			}
			sout.str("");
		}
		return max_number_of_digits;
	}

	size_t max_length_not_first(const Matrix& m, const std::ostream& out) { //maximum element length in the remaining columns
		size_t max_number_of_digits = 0;
		std::stringstream sout;
		sout << std::setiosflags(out.flags()) << std::setprecision(out.precision()) /*<< std::setf(std::ios::scientific)*/; // flags and precision from out
		for (size_t i = 0; i < m.rows(); ++i) {
			for (size_t j = 1; j < m.columns(); ++j) {
				sout << m(i, j);
				size_t length = sout.str().size();
				if (max_number_of_digits < length) {
					max_number_of_digits = length;
				}
				sout.str("");
			}
		}
		return max_number_of_digits;
	}

	bool equal(const double& a, const double& b) { return std::fabs(a - b) < EPS; }

	std::ostream& operator <<(std::ostream& out, const Matrix& m) {//Output operator
		if (m.empty()) {
			out << "|empty|";
			return(out);
		}
		size_t first = max_length_first(m, out);
		size_t not_first = max_length_not_first(m, out);
		for (size_t i = 0; i < m.rows(); ++i) {
			out << '|';
			if (equal(m(i, 0), 0)) 
				out << std::setw(first) << 0; 
			else {
				out << std::setw(first) << m(i, 0);
			};
			for (size_t j = 1; j < m.columns(); ++j) {
				if (equal(m(i, j), 0)) { out << std::setw(not_first + 1) << 0; }
				else {
					out << std::setw(not_first + 1) << m(i, j);
				}
			}
			out << "|\n";
		}
		return(out);
	}

	
	double& Matrix::operator()(size_t row, size_t column) { // Index operator for non-constant with 2 parameter
		if (row >= m_rows || column >= m_columns) {
			throw std::out_of_range("Index out of range");
		}
		return m_ptr[row * m_columns + column];
	}

	const double& Matrix::operator()(size_t row, size_t column) const { //for constant with 2 parameter 
		if (row >= m_rows || column >= m_columns) {
			throw std::out_of_range("Index out of range");
		}
		return m_ptr[row * m_columns + column];
	}

	Matrix& Matrix::operator=(Matrix other) noexcept { //Assignment operator
		std::swap(this->m_ptr, other.m_ptr);
		std::swap(this->m_rows, other.m_rows);
		std::swap(this->m_columns, other.m_columns);
		return *this;
	}

	//Arifmetic operators
	/**
	* @brief Summ
	*
	* @param[in] Matrix the matrix
	*/
	Matrix& Matrix::operator+=(const Matrix& m) {
		if (m.rows() != m_rows || m.columns() != m_columns)
			throw std::runtime_error("Matrix's size is incorrect");
		for (size_t i = 0; i < m_rows; ++i) {
			for (size_t j = 0; j < m_columns; ++j) {
				(*this)(i, j) = (*this)(i, j) + m(i, j);
			}
		}
		return *this;
	}

	Matrix operator+(const Matrix& m1, const Matrix& m2) {
		Matrix res = m1;
		res += m2;
		return res;
	}

	Matrix& Matrix::operator*=(const double c) noexcept {
		for (size_t i = 0; i < m_rows; ++i) {
			for (size_t j = 0; j < m_columns; ++j) {
				(*this)(i, j) = (*this)(i, j) * c;
			}
		}
		return (*this);
	}

	Matrix operator*(const Matrix& m, const double c) noexcept {
		Matrix res = m;
		res *= c;
		return res;
	}

	Matrix operator*(const double c, const Matrix& m) noexcept { 
		return m * c;
	}

	Matrix& Matrix::operator-=(const Matrix& m) {
		if (m_rows != m.rows() || m_columns != m.columns()) 
			throw std::runtime_error("Matrix sizes are not equal");
		*this += m * (-1);
			return *this;
	};

	Matrix operator-(const Matrix& m1, const Matrix& m2) {
		Matrix res = m1;
		res -= m2;
		return res;
	}

	Matrix& Matrix::operator*=(const Matrix& m) {
		if (columns() != m.rows())
			throw std::runtime_error("The sizes of the matrices are different");
		Matrix res(rows(), m.columns());
		for (size_t i = 0; i < res.rows(); ++i) {
			for (size_t j = 0; j < res.columns(); ++j) {
				res(i, j) = 0;
				for (size_t k = 0; k < m_columns; ++k) {
					res(i, j) += (*this)(i, k) * m(k, j);
				}
			}
		}
		*this = std::move(res);
		return *this;
	}

	Matrix operator*(const Matrix& m1, const Matrix& m2) {
		Matrix res = m1;
		res *= m2;
		return res;
	}

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

	/**
	* @brief
	* 
	* @param m1
	*/
	bool operator!=(const Matrix& m1, const Matrix& m2) { return !(m1 == m2); }

	//Methods

	void linalg::Matrix::reshape(size_t rows, size_t columns) { //Empty
		if (empty())
			return;
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
			if (equal(res(i, i), 0)) 
				continue;   
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

	double Matrix::det() const { //Det
		if (empty()) 
			throw std::runtime_error("Matrix is empty"); //вопрос как вызывается throw
		if (rows() != columns()) 
			throw std::runtime_error("The matrix should be square");
		Matrix d = *this; //либо -> для this (this->
		Matrix m = d.Gauss(false);
		double opr = 1;
		for (size_t i = 0; i < m.columns(); i++) {
			opr *= m(i, i);
		}
		return opr;
	}

	double Matrix::minor(size_t rows, size_t columns) const { //Minor 
		if ((rows >= m_rows) || (columns >= m_columns)) {
			throw std::runtime_error("Position is outside the matrix");
		}
		Matrix res(m_rows - 1, m_columns - 1);
		for (size_t i = 0; i < m_rows; ++i) {
			for (size_t j = 0; j < m_columns; ++j) {
				if (i < rows) {
					if (j < columns)
						res(i, j) = (*this)(i, j);
					else if (j > columns)
						res(i, j - 1) = (*this)(i, j);
				}
				else if (i > rows) {
					if (j < columns)
						res(i - 1, j) = (*this)(i, j);
					else if (j > columns)
						res(i - 1, j - 1) = (*this)(i, j);
				}
			}
		}
		return res.det();
	}

	//Functions for matrices
	Matrix concatenate(const Matrix& m1, const Matrix& m2) { //Concatenate
		if (m1.rows() != m2.rows()) 
			throw std::runtime_error("The matrices must have the same number of rows");
		if (m1.empty()) 
			return m2; 
		if (m2.empty()) 
			return m1; 
		Matrix res(m1.rows(), m1.columns() + m2.columns());
		for (size_t i = 0; i < m1.rows(); ++i) {
			size_t t = 0;
			for (size_t j = 0; j < m1.columns(); ++j) {
				res(i, t) = m1(i, j);
				t++;
			}
			for (size_t j = 0; j < m2.columns(); ++j) {
				res(i, t) = m2(i, j);
				t++;
			}
		}
		return(res);
	}

	Matrix transpose(const Matrix& m) { //Transpose
		Matrix res(m.columns(), m.rows());
		for (size_t i = 0; i < res.rows(); ++i) {
			for (size_t j = 0; j < res.columns(); ++j) {
				res(i, j) = m(j, i);
			}
		}
		return res;
	}

	Matrix uni(size_t n) { //Unit matrix
		Matrix res(n, n);
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < n; ++j) {
				if (i == j) 
					res(i, j) = 1;
				else  
					res(i, j) = 0;
			}
		}
		return res;
	}

	const Matrix invert(const Matrix& m) { //Invert
		if ((m.rows() != m.columns()) || (fabs(m.det() - 0) < 1e-10)) {
			throw std::runtime_error("There is no inverse for the matrix");
		}
		linalg::Matrix res(m.rows(), m.columns());
		double det = m.det();
		for (size_t i = 0; i < m.rows(); ++i) {
			for (size_t j = 0; j < m.columns(); ++j) {
				res(i, j) = pow(-1, (i + j)) * m.minor(i, j) / det;
			}
		}
		return transpose(res);
	}

	Matrix power(const Matrix& m, int deg) { //Power
		if (m.empty())
			return m;
		if (m.rows() != m.columns())
			throw std::runtime_error("Different dimensions");
		Matrix res;
		if (deg == 0)
			res = uni(m.rows());
		else if (deg < 0)
			res = invert(m);
		else
			res = m;
		Matrix t = res;
		for (int i = 1; i < abs(deg); ++i)
			res *= t;
		return res;
	}
	


}