#include "matrix.h"
#include <gtest/gtest.h>

using namespace linalg;
/*
TEST(MatrixConstructor, DefaultConstructor) {
    Matrix matrix;
    EXPECT_EQ(matrix.rows(), 0);
    EXPECT_EQ(matrix.columns(), 0);
}

TEST(MatrixConstructor, ConstructorWithSize) {
    Matrix matrix(5);
    EXPECT_EQ(matrix.rows(), 5);
    EXPECT_EQ(matrix.columns(), 1);
}

TEST(MatrixConstructor, ConstructorWithDimensions) {
    Matrix matrix(4, 6);
    EXPECT_EQ(matrix.rows(), 4);
    EXPECT_EQ(matrix.columns(), 6);
}

TEST(MatrixConstructor, InitializerListConstructor) {
    Matrix matrix = { { 10, 20, 30, 40 },
                      { 50, 60, 70, 80 },
                      { 90, 100, 110, 120 } };
    EXPECT_EQ(matrix.rows(), 3);
    EXPECT_EQ(matrix.columns(), 4);
    for (size_t i = 0; i < matrix.rows(); ++i) {
        for (size_t j = 0; j < matrix.columns(); ++j) {
            EXPECT_EQ(matrix(i, j), i * 40 + (j + 1) * 10);
        }
    }
}

TEST(MatrixConstructor, CopyConstructorCheck) {
    Matrix original = { { 5, 10 }, { 15, 20 }, { 25, 30 } };
    Matrix copy(original);
    EXPECT_EQ(copy.rows(), 3);
    EXPECT_EQ(copy.columns(), 2);
    for (size_t i = 0; i < original.rows(); ++i) {
        for (size_t j = 0; j < original.columns(); ++j) {
            EXPECT_EQ(original(i, j), copy(i, j));
        }
    }
}

TEST(MatrixConstructor, MoveConstructorCheck) {
    Matrix original = {
        { 3, 6, 9 }, { 12, 15, 18 }, { 21, 24, 27 }, { 30, 33, 36 }
    };
    Matrix moved(std::move(original));
    EXPECT_EQ(moved.rows(), 4);
    EXPECT_EQ(moved.columns(), 3);
    for (size_t i = 0; i < moved.rows(); ++i) {
        for (size_t j = 0; j < moved.columns(); ++j) {
            EXPECT_EQ(moved(i, j), (3 * i + j + 1) * 3);
        }
    }
}

TEST(Operator, Equal) {
    Matrix a = { { 5, 6, 7 }, { 8, 9, 10 }, { 11, 12, 13 } };
    Matrix b = { { 5, 6, 7 }, { 8, 9, 10 }, { 11, 12, 13 } };
    EXPECT_TRUE(a == b);
    Matrix c = { { 6, 6, 7 }, { 8, 9, 10 }, { 11, 12, 13 } };
    EXPECT_FALSE(a == c);
    EXPECT_TRUE(a != c);
}

TEST(Operator, Index) {
    Matrix a = { { 10, 20, 30 }, { 40, 50, 60 }, { 70, 80, 90 } };
    EXPECT_EQ(a(1, 2), 60);
    EXPECT_EQ(a(0, 0), 10);
    EXPECT_EQ(a(2, 1), 80);
    EXPECT_EQ(a(1, 0), 40);
}

TEST(Methods, Rows) {
    Matrix a(5, 6);
    EXPECT_EQ(a.rows(), 5);
}

TEST(Methods, Columns) {
    Matrix a(5, 6);
    EXPECT_EQ(a.columns(), 6);
}

TEST(Methods, Empty) {
    Matrix a;
    EXPECT_TRUE(a.empty());
    Matrix b(2, 3);
    EXPECT_FALSE(b.empty());
}
*/
TEST(Methods, Reshape) {
    Matrix a(4, 5);
    a.reshape(1, 0);
    EXPECT_EQ(a.rows(), 4);
    EXPECT_EQ(a.columns(), 5);
}
/*
TEST(Methods, GaussTrue) {
    Matrix a = { { 5, 7, 9 }, { 4, 5, 6 }, { 7, 8, 9 } };
    auto b = a.Gauss(true);
    EXPECT_EQ(b, Matrix({ { 1, 0, -1 }, { 0, 1, 2 }, { 0, 0, 0 } }));
}

TEST(Operations, SelfPlus) {
    Matrix a = { { 2, 3, 4 }, { 5, 6, 7 }, { 8, 9, 10 } };
    a += Matrix({ { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } });
    EXPECT_EQ(a, Matrix({ { 3, 5, 7 }, { 9, 11, 13 }, { 15, 17, 19 } }));
}

TEST(Operations, SelfSub) {
    Matrix a = { { 2, 3, 4 }, { 5, 6, 7 }, { 8, 9, 10 } };
    a -= Matrix({ { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } });
    EXPECT_EQ(a, Matrix({ { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 } }));
}

TEST(Operations, SelfMul) {
    Matrix a = { { 2, 3, 4 }, { 5, 6, 7 }, { 8, 9, 10 } };
    a *= Matrix({ { 1, 0, -1 }, { 2, 1, 0 }, { 3, 2, 1 } });
    EXPECT_EQ(a, Matrix({ { 20, 11, 2 }, { 38, 20, 2 }, { 56, 29, 2 } }));
}

TEST(Operations, SelfMulConst) {
    Matrix a = { { 2, 3, 4 }, { 5, 6, 7 }, { 8, 9, 10 } };
    a *= 2;
    EXPECT_EQ(a, Matrix({ { 4, 6, 8 }, { 10, 12, 14 }, { 16, 18, 20 } }));
}

TEST(Operations, Add) {
    Matrix a = { { 2, 4, 6 }, { 8, 10, 12 }, { 14, 16, 18 } };
    Matrix b = { { 1, 3, 5 }, { 7, 9, 11 }, { 13, 15, 17 } };
    Matrix c = a + b;
    EXPECT_EQ(c, Matrix({ { 3, 7, 11 }, { 15, 19, 23 }, { 27, 31, 35 } }));
}

TEST(Operations, Sub) {
    Matrix a = { { 2, 4, 6 }, { 8, 10, 12 }, { 14, 16, 18 } };
    Matrix b = { { 1, 3, 5 }, { 7, 9, 11 }, { 13, 15, 17 } };
    Matrix c = a - b;
    EXPECT_EQ(c, Matrix({ { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 } }));
}

TEST(Operations, Mul) {
    Matrix a = { { 2, 3, 4 }, { 5, 6, 7 }, { 8, 9, 10 } };
    Matrix b = { { 1, 0, -1 }, { 2, 1, 0 }, { 3, 2, 1 } };
    Matrix c = a * b;
    EXPECT_EQ(c, Matrix({ { 20, 11, 2 }, { 38, 20, 2 }, { 56, 29, 2 } }));
}

TEST(Operations, MulConst) {
    Matrix a = { { 2, 3, 4 }, { 5, 6, 7 }, { 8, 9, 10 } };
    double b = 2.5;
    Matrix c = a * b;
    EXPECT_EQ(c, Matrix({ { 5, 7.5, 10 }, { 12.5, 15, 17.5 }, { 20, 22.5, 25 } }));
    Matrix d = b * a;
    EXPECT_EQ(d, Matrix({ { 5, 7.5, 10 }, { 12.5, 15, 17.5 }, { 20, 22.5, 25 } }));
}

TEST(Functions, Uni) {
    Matrix a = uni(4);
    EXPECT_EQ(a.rows(), 4);
    EXPECT_EQ(a.columns(), 4);
    EXPECT_EQ(a, Matrix({ {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} }));
}

TEST(Functions, Transpose) {
    Matrix a = { { 2, 4, 6 }, { 8, 10, 12 }, { 14, 16, 18 }, { 20, 22, 24 } };
    Matrix b = transpose(a);
    EXPECT_EQ(b, Matrix({ { 2, 8, 14, 20 }, { 4, 10, 16, 22 }, { 6, 12, 18, 24 } }));
}

TEST(Functions, Invert) {
    Matrix a = { { 1, 1, 1 }, { 2, 2, 3 }, { 2, 1, 1 } };

    Matrix b = invert(a);
    Matrix right_ans = { { -1, 0, 1 }, { 4, -1, -1 }, { -2, 1, 0 } };

    EXPECT_EQ(b, right_ans);
}

TEST(Functions, Concatenate) {
    Matrix a = { { 2, 4, 6 }, { 8, 10, 12 }, { 14, 16, 18 } };
    Matrix b = { { 1, 3, 5 }, { 7, 9, 11 }, { 13, 15, 17 } };
    Matrix c = concatenate(a, b);
    Matrix right_ans = { { 2, 4, 6, 1, 3, 5 },
                         { 8, 10, 12, 7, 9, 11 },
                         { 14, 16, 18, 13, 15, 17 } };
    EXPECT_EQ(c, right_ans);
}

TEST(Functions, Power) {
    Matrix a = { { 2, 0, 6 }, { 4, 5, 2 }, { 3, 8, 7 } };
    Matrix b = power(a, 2);
    Matrix right_ans = { { 22, 48, 54 }, { 34, 41, 48 }, { 59, 96, 83 } };
    EXPECT_EQ(b, right_ans);

    b = power(a, -2);
    right_ans = {
        { -241. / 3920, 3. / 49, 9. / 1960 },
        { 1. / 1960, -17. / 245, 39. / 980 },
        { 169. / 3920, 9. / 245, -73. / 1960 },

    };
    EXPECT_EQ(b, right_ans);

    b = power(a, 0);
    right_ans = Matrix({ { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } });
    EXPECT_EQ(b, right_ans);
}

TEST(Methods, Norm) {
    Matrix a = { { 2, 3, 4 }, { 5, 6, 7 }, { 8, 9, 10 } };
    double b = a.norm();
    double right_ans = 19.59591794226542;
    EXPECT_DOUBLE_EQ(b, right_ans);
}

TEST(Methods, Trace) {
    Matrix a = { { 2, 3, 4 }, { 5, 6, 7 }, { 8, 9, 10 } };
    double b = a.trace();
    double right_ans = 18;
    EXPECT_DOUBLE_EQ(b, right_ans);
}

TEST(Methods, Det) {
    Matrix a = { { 2, 3, 4 }, { 5, 6, 7 }, { 8, 9, 10 } };
    double b = a.det();
    double right_ans = 0;
    EXPECT_DOUBLE_EQ(b, right_ans);

    a = { { 3, 0, 4 }, { 5, 6, 7 }, { 8, 9, 10 } };
    b = a.det();
    right_ans = -21;
    EXPECT_DOUBLE_EQ(b, right_ans);
}
*/