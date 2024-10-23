#include <iostream>
#include "matrix.h"

int main() {
	linalg::Matrix a(2, 2);
	a(0, 0) = 1;
	a(0, 1) = 2;
	a(1, 0) = 3;
	a(1, 1) = 4;
	linalg::Matrix b = { {1, 3}, {2, 3} };
	linalg::Matrix c = linalg::concatenate(transpose(b), a);
	std::cout << a << b << c;
}