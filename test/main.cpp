#include <iostream>
#include "matrix.h"

int main() {
	linalg::Matrix a(2, 2);
	a(0, 0) = 1;
	a(0, 1) = 2;
	a(1, 0) = 3;
	a(1, 1) = 4;
	linalg::Matrix b = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	linalg::Matrix c = linalg::power(b, 2);
	std::cout << b << c;
}