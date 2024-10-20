#pragma once
#include <initializer_list>
#include <iostream>

namespace linalg {

	class Matrix {
	public: //Constructors
		Matrix() noexcept {}
		Matrix(size_t rows);
		Matrix(size_t rows, size_t columns);
		Matrix(const Matrix& m);

		//Destructor
		~Matrix() { delete[] m_ptr; }

	public: //Methods
		size_t rows() const noexcept { return m_rows; }
		size_t columns() const noexcept { return m_columns; }
		bool empty() const noexcept { return (m_rows == 0); }
		void reshape(int new_rows, int new_columns);

	private:
		double* m_ptr = nullptr;
		size_t m_rows = 0;
		size_t m_columns = 0;
	};



}