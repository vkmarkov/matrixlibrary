/**
 * @file
 * @brief C++ library for working with matrices
 * @version 0.1.0
 * @date 2024-10-21
 * @authors vmarkov20
 */
#include "matrix.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

const double EPS = 1e-10;

namespace linalg {

/**
 * @brief Construct a matrix with a given number of rows
 * @param[in] rows The number of rows
 * @throws std::runtime_error If the number of rows is negative
 * @details
 * This constructor initializes a matrix with the specified number of rows.
 * It allocates memory for the matrix elements and sets the internal row and column
 * counters. The number of columns is set to 1. If the given number of rows is
 * negative, an exception is thrown.
 */
Matrix::Matrix(size_t rows) {
    if (rows < 0) {
        throw std::runtime_error(
            "The matrix cannot be with a negative number of rows");
    }
    m_rows    = rows;
    m_columns = 1;
    m_ptr     = new double[rows];
}

/**
 * @brief Construct a matrix with a given number of rows and columns
 * @param[in] rows The number of rows
 * @param[in] columns The number of columns
 * @throws std::runtime_error If the number of rows or columns is negative
 * @details
 * This constructor initializes a matrix with the specified number of rows and
 * columns. It allocates memory for the matrix elements and sets the internal row and
 * column counters. If the given number of rows or columns is negative, an exception
 * is thrown.
 */
Matrix::Matrix(size_t rows, size_t columns) {
    if ((rows < 0) || (columns < 0)) {
        throw std::runtime_error(
            "The matrix cannot be with a negative number of rows or columns");
    }
    m_rows    = rows;
    m_columns = columns;
    m_ptr     = new double[rows * columns];
}

/**
 * @brief Copy constructor
 * @param[in] m The matrix to be copied
 *
 * @details
 * This constructor creates a new matrix object as a copy of the given matrix.
 * It allocates memory for the matrix elements and copies the data from the
 * source matrix. The constructor is marked as noexcept, indicating that no
 * exceptions will be thrown during the copy operation.
 */
Matrix::Matrix(const Matrix& m) noexcept {
    m_rows    = m.m_rows;
    m_columns = m.m_columns;
    m_ptr     = new double[m_rows * m_columns];
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        m_ptr[i] = m.m_ptr[i];
    }
}

/**
 * @brief Move constructor
 * @param[in] m The matrix to be moved
 *
 * @details
 * This constructor is used to move the contents of another matrix to the current
 * one. The contents of the other matrix are swapped with the contents of the current
 * matrix. The move constructor is marked as noexcept, which means that no exceptions
 * are thrown during the move operation.
 */
Matrix::Matrix(Matrix&& m) noexcept {
    std::swap(m_ptr, m.m_ptr);
    std::swap(m_rows, m.m_rows);
    std::swap(m_columns, m.m_columns);
}

/**
 * @brief Construct a matrix from a list of doubles
 *
 * @param[in] lst The list of doubles
 *
 * @details
 * This constructor initializes a matrix with the number of rows equal to the size
 * of the list and a single column. Each element of the list becomes an element in
 * the matrix. The matrix is constructed in a way that each element of the list
 * corresponds to a row in the matrix.
 */
Matrix::Matrix(std::initializer_list<double> lst) noexcept {
    m_ptr     = new double[lst.size()];
    m_rows    = lst.size();
    m_columns = 1;
    size_t i  = 0;
    for (double el : lst) {
        m_ptr[i++] = el;
    }
}

/**
 * @brief Construct a matrix from a list of lists of doubles
 * @param[in] lst The list of lists of doubles
 *
 * @throws std::runtime_error If the lists of the list are not of equal size
 *
 * @details
 * The function iterates over all sublists of the given list and checks if they are
 * all of the same size. If not, it throws an exception. Otherwise, it allocates
 * memory for the matrix and copies the elements of the sublists to the matrix.
 */
Matrix::Matrix(std::initializer_list<std::initializer_list<double>> lst) {
    m_ptr     = new double[lst.size() * lst.begin()->size()];
    m_rows    = lst.size();
    m_columns = lst.begin()->size();
    size_t i  = 0;
    for (auto&& row : lst) {
        if (row.size() != lst.begin()->size()) {
            throw std::runtime_error(
                "All rows must have the same number of columns");
        }
        for (double el : row) {
            m_ptr[i++] = el;
        }
    }
}

/**
 * @brief Returns the maximum number of digits in the first column of the matrix
 *
 * @param[in] m The matrix
 * @param[in] out The output stream
 *
 * @return The maximum number of digits
 *
 * @details
 * The function iterates over all elements of the first column of the matrix and
 * measures the length of each element when it is printed to the given output stream.
 * The maximum length of all elements is returned as the result.
 */
size_t max_length_first(const Matrix& m, const std::ostream& out) {
    size_t max_number_of_digits = 0;
    std::stringstream sout;
    sout << std::setiosflags(out.flags()) << std::setprecision(out.precision());
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

/**
 * @brief Returns the maximum number of digits in the second and later columns of the
 * matrix
 *
 * @param[in] m The matrix
 * @param[in] out The output stream
 *
 * @return The maximum number of digits
 *
 * @details
 * The function iterates over all elements of the matrix except the first column and
 * measures the length of each element when it is printed to the given output stream.
 * The maximum length of all elements is returned as the result.
 */
size_t max_length_not_first(const Matrix& m, const std::ostream& out) {
    size_t max_number_of_digits = 0;
    std::stringstream sout;
    sout << std::setiosflags(out.flags()) << std::setprecision(out.precision());
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

/**
 * @brief Compares two double values for equality
 *
 * @param[in] a The first number
 * @param[in] b The second number
 *
 * @return true if the difference between the two numbers is less than EPS
 *
 * @details
 * EPS is a small value used to compare floating point numbers. It is set to 1e-10
 */
bool equal(const double& a, const double& b) {
    return std::fabs(a - b) < EPS;
}

/**
 * @brief Prints the matrix to the output stream
 *
 * @param[in] out The output stream
 * @param[in] m The matrix to print
 *
 * @return The output stream after printing the matrix
 *
 * @details
 * This function prints the matrix in a human-readable format to the output stream.
 * It first checks if the matrix is empty and prints "|empty|". Otherwise, it prints
 * the matrix row-by-row, with elements separated by spaces and rows separated by
 * newline characters. The elements are formatted according to the settings of the
 * output stream. If an element is equal to zero, it is printed as "0". The width of
 * the first element is determined by the maximum number of digits in the first
 * column, and the width of other elements is determined by the maximum number of
 * digits in the other columns. The elements are aligned to the right.
 */
std::ostream& operator<<(std::ostream& out, const Matrix& m) {
    if (m.empty()) {
        out << "|empty|";
        return (out);
    }
    size_t first     = max_length_first(m, out);
    size_t not_first = max_length_not_first(m, out);
    for (size_t i = 0; i < m.rows(); ++i) {
        out << '|';
        if (equal(m(i, 0), 0)) {
            out << std::setw(first) << 0;
        } else {
            out << std::setw(first) << m(i, 0);
        };
        for (size_t j = 1; j < m.columns(); ++j) {
            if (equal(m(i, j), 0)) {
                out << std::setw(not_first + 1) << 0;
            } else {
                out << std::setw(not_first + 1) << m(i, j);
            }
        }
        out << "|\n";
    }
    return (out);
}

/**
 * @brief Accesses the element at the specified position in the matrix
 *
 * @param[in] row The row index
 * @param[in] column The column index
 *
 * @return A reference to the element at the specified position
 *
 * @throws std::out_of_range If the specified position is out of the matrix bounds
 *
 * @details
 * This function provides direct access to the element at the given row and
 * column indices. It checks if the indices are within the matrix bounds and throws
 * an exception if they are out of range. The function returns a reference, which
 * allows modification of the element at the specified position.
 */
double& Matrix::operator()(size_t row, size_t column) {
    if (row >= m_rows || column >= m_columns) {
        throw std::out_of_range("Index out of range");
    }
    return m_ptr[row * m_columns + column];
}

/**
 * @brief Accesses the element at the specified position in the matrix (const
 * version)
 *
 * @param[in] row The row index
 * @param[in] column The column index
 *
 * @return A const reference to the element at the specified position
 *
 * @throws std::out_of_range If the specified position is out of the matrix bounds
 *
 * @details
 * This function provides read-only access to the element at the given row and
 * column indices. It checks if the indices are within bounds and throws an
 * exception if not.
 */
const double& Matrix::operator()(size_t row, size_t column) const {
    if (row >= m_rows || column >= m_columns) {
        throw std::out_of_range("Index out of range");
    }
    return m_ptr[row * m_columns + column];
}

/**
 * @brief Copy assignment operator
 *
 * @param[in] other The matrix to copy
 *
 * @return A reference to the current matrix after assignment
 *
 * @details
 * This method implements the copy-swap idiom, which allows to use this operator
 * as a move assignment operator as well. It swaps the contents of the current matrix
 * with the contents of the other matrix, and then returns a reference to the current
 * matrix.
 */
Matrix& Matrix::operator=(Matrix other) noexcept {
    std::swap(this->m_ptr, other.m_ptr);
    std::swap(this->m_rows, other.m_rows);
    std::swap(this->m_columns, other.m_columns);
    return *this;
}

/**
 * @brief Adds another matrix to the current matrix
 *
 * @param[in] m The matrix to add
 *
 * @return A reference to the current matrix after addition
 *
 * @throws std::runtime_error If the sizes of the matrices are not equal
 *
 * @details
 * This function performs element-wise addition of another matrix to the current
 * matrix. It checks if the sizes of the matrices are equal, and throws an exception
 * if not. The result replaces the original matrix.
 */
Matrix& Matrix::operator+=(const Matrix& m) {
    if (m.rows() != m_rows || m.columns() != m_columns) {
        throw std::runtime_error("Matrix sizes are not equal");
    }
    for (size_t i = 0; i < m_rows; ++i) {
        for (size_t j = 0; j < m_columns; ++j) {
            (*this)(i, j) += m(i, j);
        }
    }
    return *this;
}

/**
 * @brief Sums two matrices
 *
 * @param[in] m1 The first matrix
 * @param[in] m2 The second matrix
 *
 * @throws std::runtime_error If the matrices have different sizes
 *
 * @return The sum of the two matrices
 *
 * @details
 * This function adds two matrices element-wise. The result is a new matrix, the
 * original matrices are unchanged.
 */
Matrix operator+(const Matrix& m1, const Matrix& m2) {
    Matrix res = m1;
    res += m2;
    return res;
}

/**
 * @brief Scales a matrix by a scalar
 *
 * @param[in] c The scalar to scale by
 *
 * @return The scaled matrix
 *
 * @details
 * The result is a new matrix that is the result of scaling the input matrix by the
 * given scalar. The original matrix is not modified.
 */
Matrix& Matrix::operator*=(const double c) noexcept {
    for (size_t i = 0; i < m_rows; ++i) {
        for (size_t j = 0; j < m_columns; ++j) {
            (*this)(i, j) = (*this)(i, j) * c;
        }
    }
    return (*this);
}

/**
 * @brief Scales a matrix by a scalar
 *
 * @param[in] c The scalar to scale by
 *
 * @return The scaled matrix
 *
 * @details
 * The result is a new matrix that is the result of scaling the input matrix by the
 * given scalar. The original matrix is not modified.
 */
Matrix operator*(const Matrix& m, const double c) noexcept {
    Matrix res = m;
    res *= c;
    return res;
}

/**
 * @brief Scales a matrix by a scalar
 *
 * @param[in] c The scalar to scale by
 * @param[in] m The matrix to scale
 *
 * @return The scaled matrix
 *
 * @details
 * This function multiplies the matrix m by the scalar c.
 * It is equivalent to calling m * c.
 */
Matrix operator*(const double c, const Matrix& m) noexcept {
    return m * c;
}

/**
 * @brief Subtracts one matrix from another
 *
 * @param[in] m The matrix to subtract from the current matrix
 *
 * @return The result of the subtraction
 *
 * @throws std::runtime_error If the sizes of the matrices are not equal
 *
 * @details
 * This method subtracts the matrix m from the current matrix.
 * It checks if the sizes of the matrices are equal, and throws an exception if not.
 * Then it subtracts the elements of the matrix m from the current matrix.
 */
Matrix& Matrix::operator-=(const Matrix& m) {
    if (m_rows != m.rows() || m_columns != m.columns()) {
        throw std::runtime_error("Matrix sizes are not equal");
    }
    *this += m * (-1);
    return *this;
};

/**
 * @brief Subtracts one matrix from another
 *
 * @param[in] m1 The first matrix
 * @param[in] m2 The second matrix
 *
 * @return The result of the subtraction
 *
 * @throws std::runtime_error If the sizes of the matrices are not equal
 *
 * @details
 * The function subtracts the second matrix from the first matrix and returns
 * the resulting matrix. It first checks if the sizes of the matrices are equal.
 * If they are not, it throws an exception.
 */
Matrix operator-(const Matrix& m1, const Matrix& m2) {
    Matrix res = m1;
    res -= m2;
    return res;
}

/**
 * @brief Multiplies the matrix by another matrix
 *
 * @param[in] m The matrix to multiply with
 * @return A reference to the resulting matrix
 *
 * @throws std::runtime_error If the number of columns of the current matrix is not
 * equal to the number of rows of the matrix to multiply with
 *
 * @details
 * This function performs matrix multiplication. The resulting matrix will have the
 * same number of rows as the current matrix and the same number of columns as the
 * matrix being multiplied. The original matrix is replaced with the result.
 */
Matrix& Matrix::operator*=(const Matrix& m) {
    if (columns() != m.rows()) {
        throw std::runtime_error("The sizes of the matrices are different");
    }
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

/**
 * @brief Multiply two matrices
 *
 * @param[in] m1 The first matrix
 * @param[in] m2 The second matrix
 *
 * @return The result of the multiplication
 *
 * @throws std::runtime_error If the number of columns of the first matrix is not
 * equal to the number of rows of the second matrix
 *
 * @details
 * The function multiplies two matrices. The function first checks if the number of
 * columns of the first matrix is equal to the number of rows of the second matrix.
 * If the sizes are different, the function throws an exception. Otherwise, the
 * function multiplies the matrices and returns the result.
 */
Matrix operator*(const Matrix& m1, const Matrix& m2) {
    Matrix res = m1;
    res *= m2;
    return res;
}

/**
 * @brief Checks if two matrices are equal
 *
 * @param[in] m1 The first matrix
 * @param[in] m2 The second matrix
 *
 * @return true if the matrices are equal, false otherwise
 *
 * @details
 * The function checks if the two matrices are equal. If the number of rows or
 * columns of the matrices is different, the function returns false. Otherwise, the
 * function compares each element of the matrices. If any of the elements are not
 * equal, the function returns false. If all the elements are equal, the function
 * returns true.
 */
bool operator==(const Matrix& m1, const Matrix& m2) {
    if ((m1.rows() != m2.rows()) || (m1.columns() != m2.columns())) {
        return false;
    }
    for (size_t i = 0; i < m1.rows(); ++i) {
        for (size_t j = 0; j < m1.columns(); ++j) {
            if (!equal(m1(i, j), m2(i, j))) {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Checks if two matrices are not equal
 *
 * @param[in] m1 The first matrix
 * @param[in] m2 The second matrix
 *
 * @return true if the matrices are not equal, false otherwise
 *
 * @details
 * The function checks if the two matrices are not equal. This function is the
 * opposite of the operator==. If the operator== returns false, this function returns
 * true and vice versa.
 */
bool operator!=(const Matrix& m1, const Matrix& m2) {
    return !(m1 == m2);
}

/**
 * @brief Reshapes the matrix
 *
 * @param[in] rows The new number of rows
 * @param[in] columns The new number of columns
 *
 * @throws std::runtime_error If the number of elements in the new shape is not equal
 * to the number of elements in the original shape
 *
 * @details
 * The function reshapes the matrix. The number of elements in the new shape must be
 * the same as the number of elements in the original shape.
 */
void linalg::Matrix::reshape(size_t rows, size_t columns) { // Empty
    if (empty()) {
        return;
    }
    if (rows * columns != m_rows * m_columns) {
        throw std::runtime_error(
            "Number of elements in reshaped matrix must be the same");
    }
    m_rows    = rows;
    m_columns = columns;
}

/**
 * @brief Calculates the norm of the matrix
 *
 * @return The norm of the matrix
 *
 * @throws std::runtime_error If the matrix is empty
 *
 * @details
 * The norm of a matrix is the square root of the sum of the squares of all elements.
 * This method is const, as it does not modify the matrix.
 */
double Matrix::norm() const { // Norm
    if (empty()) {
        throw std::runtime_error("Matrix is empty");
    }
    double res = 0;
    for (size_t i = 0; i < m_rows; ++i) {
        for (size_t j = 0; j < m_columns; ++j) {
            res += m_ptr[i * m_columns + j] * m_ptr[i * m_columns + j];
        }
    }
    return sqrt(res);
}

/**
 * @brief Calculates the trace of the matrix
 *
 * @return The trace of the matrix
 *
 * @throws std::runtime_error If the matrix is empty or not square
 *
 * @details
 * The trace of a matrix is the sum of the elements on the main diagonal.
 * This method is const, as it does not modify the matrix.
 */
double Matrix::trace() const { // Trace
    if (empty()) {
        throw std::runtime_error("Matrix is empty");
    }
    if (m_rows != m_columns) {
        throw std::runtime_error("Matrix is not square");
    }
    double res = 0;
    for (int i = 0; i < m_rows; ++i) {
        res += m_ptr[i * m_columns + i];
    }
    return res;
}

/**
 * @brief Gaussian elimination
 *
 * @param rref If true, the result will be in reduced row echelon form (RREF)
 * @return The result of Gaussian elimination
 *
 * @details
 * The function performs Gaussian elimination on the matrix. If the parameter rref is
 * true, the result will be in reduced row echelon form (RREF).
 */
Matrix Matrix::Gauss(bool rref) const { // Gauss
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
        if (equal(res(i, i), 0)) {
            continue;
        }
        if (rref) { // Reduced Row Echelon Form (����������� ����������� �����
                    // �������)
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

/**
 * @brief Calculates the determinant of the matrix
 *
 * @throws std::runtime_error If the matrix is empty or not square
 *
 * @return The determinant of the matrix
 *
 * @details
 * The function creates a temporary matrix to avoid modifying the original matrix.
 * The determinant is calculated by multiplying the elements on the main diagonal of
 * the matrix after Gaussian elimination.
 */
double Matrix::det() const {
    if (empty()) {
        throw std::runtime_error("Matrix is empty"); // ������ ��� ���������� throw
    }
    if (rows() != columns()) {
        throw std::runtime_error("The matrix should be square");
    }
    // Create a temporary matrix to avoid modifying the original matrix
    Matrix d   = *this; // ���� -> ��� this (this->
    Matrix m   = d.Gauss(false);
    double opr = 1;
    for (size_t i = 0; i < m.columns(); i++) {
        opr *= m(i, i);
    }
    return opr;
}

/**
 * @brief Calculates the minor of the matrix at the given position
 *
 * @param[in] rows The row of the minor
 * @param[in] columns The column of the minor
 *
 * @throws std::runtime_error If the position is outside of the matrix
 *
 * @return The minor of the matrix
 *
 * @details
 * The minor is calculated by creating a temporary matrix that excludes the row and
 * column of the given position. The determinant of this temporary matrix is then
 * calculated and returned.
 */
double Matrix::minor(size_t rows, size_t columns) const {
    if ((rows >= m_rows) || (columns >= m_columns)) {
        throw std::runtime_error("Position is outside the matrix");
    }
    Matrix res(m_rows - 1, m_columns - 1);
    for (size_t i = 0; i < m_rows; ++i) {
        for (size_t j = 0; j < m_columns; ++j) {
            if (i < rows) {
                if (j < columns) {
                    res(i, j) = (*this)(i, j);
                } else if (j > columns) {
                    res(i, j - 1) = (*this)(i, j);
                }
            } else if (i > rows) {
                if (j < columns) {
                    res(i - 1, j) = (*this)(i, j);
                } else if (j > columns) {
                    res(i - 1, j - 1) = (*this)(i, j);
                }
            }
        }
    }
    return res.det();
}

/**
 * @brief Concatenates two matrices horizontally
 *
 * @param[in] m1 the first matrix
 * @param[in] m2 the second matrix
 *
 * @throws std::runtime_error if the number of rows of matrices are not equal
 *
 * @return the resulting matrix
 *
 * @details
 * If both matrices are empty, the result is an empty matrix.
 * If only one of the matrices is empty, the result is the other matrix.
 */
Matrix concatenate(const Matrix& m1, const Matrix& m2) { // Concatenate
    if (m1.empty()) {
        return m2;
    }
    if (m2.empty()) {
        return m1;
    }
    if (m1.rows() != m2.rows()) {
        throw std::runtime_error("The matrices must have the same number of rows");
    }
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
    return (res);
}

/**
 * @brief Returns the transposed matrix
 *
 * @param[in] m Input matrix
 * @return The transposed matrix
 *
 * @details
 * The transposed matrix is a matrix that has the same elements as the original one,
 * but the elements are rearranged so that the rows of the original matrix become the
 * columns of the transposed matrix, and the columns of the original matrix become
 * the rows of the transposed matrix.
 */
Matrix transpose(const Matrix& m) {
    Matrix res(m.columns(), m.rows());
    for (size_t i = 0; i < res.rows(); ++i) {
        for (size_t j = 0; j < res.columns(); ++j) {
            res(i, j) = m(j, i);
        }
    }
    return res;
}

/**
 * @brief Creates a unit matrix of size n x n
 *
 * @param[in] n The size of the unit matrix
 * @return A unit matrix with ones on the diagonal and zeros elsewhere
 *
 * @details
 * A unit matrix, also known as an identity matrix, is a square matrix
 * in which all the elements of the principal diagonal are ones and all other
 * elements are zeros.
 */
Matrix uni(size_t n) {
    Matrix res(n, n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (i == j) {
                res(i, j) = 1;
            } else {
                res(i, j) = 0;
            }
        }
    }
    return res;
}

/**
 * @brief Calculates the inverse matrix
 *
 * @param m Input matrix
 * @return The inverse matrix
 * @throws std::runtime_error If the matrix is empty, not square, or determinant is
 * zero
 * 
 * @deprecated This implementation uses an older method of matrix inversion. 
 * Consider using the new method `invert` for better performance.
 * 
 * @details
 * This function computes the inverse of a given square matrix. It first checks if
 * the matrix is square and has a non-zero determinant. If these conditions are met,
 * it calculates the inverse using the formula involving minors, cofactors, and the
 * determinant.
 */
const Matrix invert_old(const Matrix& m) {
    if ((m.rows() != m.columns()) || (fabs(m.det() - 0) < EPS)) {
        throw std::runtime_error("There is no inverse for the matrix");
    }
    linalg::Matrix res(m.rows(), m.columns());
    double det = m.det();
    // Calculate the inverse using the formula involving minors and cofactors
    for (size_t i = 0; i < m.rows(); ++i) {
        for (size_t j = 0; j < m.columns(); ++j) {
            // Compute the cofactor and divide by determinant
            res(i, j) = pow(-1, (i + j)) * m.minor(i, j) / det;
        }
    }
    // Transpose the result to get the inverse
    return transpose(res);
}

/**
 * @brief Inverts a square matrix.
 *
 *
 * @param [in] m The matrix to be inverted. Must be square and non-degenerate.
 * @return A new matrix that is the inverse of the input matrix.
 * @throws std::runtime_error If the matrix is degenerate, empty, or not square.
 * 
 * @details
 *  * This function takes a square matrix and returns its inverse. If the matrix is degenerate
 * (i.e., its determinant is zero), an exception is thrown. Similarly, if the matrix is empty or not square,
 * the function throws an exception.
 *
 * The function internally uses Gaussian elimination to compute the inverse. It concatenates the input
 * matrix with an identity matrix, applies Gaussian elimination, and extracts the inverse matrix from the result.
 */
Matrix invert(const Matrix& m) {
    if (m.det() == 0) 
        throw std::runtime_error("Matrix is degenerate");
    if (m.empty()) 
        throw std::runtime_error("Matrix is empty");
    if (m.rows() != m.columns()) 
        throw std::runtime_error("Matrix is not square");
    Matrix temp = uni(m.rows());
    temp = concatenate(m, temp);
    temp = temp.Gauss(true);
    Matrix inverse(m.rows(), m.columns());
    for (size_t i = 0; i < m.columns(); ++i) {
        for (size_t j = 0; j < m.rows(); ++j) {
            inverse(i, j) = temp(i, j + m.columns());
        }
    }
    return inverse;
}

/**
 * @brief Calculates the power of the matrix
 *
 * @param[in] m Input matrix
 * @param[in] deg Degree of the power
 * @return The result of the power of the matrix
 * @throws std::runtime_error If the matrix is empty or the dimensions are different
 *
 * @details
 * This function computes the power of a given matrix. It first checks if the matrix
 * is empty or if the dimensions are different, and if so, throws an exception. If
 * the degree of the power is 0, it returns the unit matrix. If the degree is
 * negative, it returns the inverse of the matrix. Otherwise, it multiplies the
 * matrix by itself deg times.
 */

 /**
  * @brief Calculates the power of the matrix
  *
  * @param[in] m The matrix to be raised to a power. Must be square.
  * @param[in] p The exponent. Can be a positive or negative integer.
  * @return A new matrix that is the result of raising the input matrix to the power `p`.
  * @throws std::runtime_error If the matrix is non-invertible when `p` is negative.
  * 
  * @details This function raises a matrix `m` to an integer power `p`. If `p` is zero,
  * the function returns the identity matrix. For positive powers, the matrix
  * is multiplied by itself `p` times. For negative powers, the function returns
  * the inverse of the matrix raised to the absolute value of `p`.
  */
Matrix power(const Matrix& m, int p) {
    //if (p < 0) { throw std::runtime_error("Power < 0"); };
    if (p == 0) { return uni(m.rows()); }
    Matrix res = m;
    for (int i = 0; i < std::abs(p) - 1; ++i) {
        res *= m;
    }
    if (p < 0) { res = invert(res); }
    return res;
}

} // namespace linalg