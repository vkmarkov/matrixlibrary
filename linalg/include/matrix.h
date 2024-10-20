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

		//Destructor
		~Matrix() { delete[] m_ptr; }

	public: //Methods
		size_t rows() const noexcept { return m_rows; }
		size_t columns() const noexcept { return m_columns; }
		bool empty() const noexcept { return (m_rows == 0); }
		void reshape(int new_rows, int new_columns);
		double& Matrix::operator ()(size_t row, size_t column);
		const double& Matrix::operator ()(size_t row, size_t column) const;

	public: //Assignment operators
		Matrix& operator=(Matrix m);

		friend std::ostream& operator<<(std::ostream&, const Matrix&);

	private: //Fields
		double* m_ptr = nullptr;
		size_t m_rows = 0;
		size_t m_columns = 0;
	};


	//std osrteam operator<<(std::ostream&, const Matrix&);
}