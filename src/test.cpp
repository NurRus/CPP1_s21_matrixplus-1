#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

using namespace std;
using namespace s21_matrix;

struct CPP_Matrix_Test : public ::testing::Test {
  S21Matrix m;
  S21Matrix n;
};

// testing EqMatrix(...)
TEST_F(CPP_Matrix_Test, test_1) {
  m.SetupMarix(3, 4, 1);
  n.SetupMarix(3, 4, 1);
  bool res = n.EqMatrix(m);
  ASSERT_EQ(res, true);
}

TEST_F(CPP_Matrix_Test, test_2) {
  m.SetupMarix(3, 4, 1);
  bool res = n.EqMatrix(m);
  ASSERT_EQ(res, false);
}

TEST_F(CPP_Matrix_Test, test_3) {
  m.SetupMarix(3, 4, 1);
  n.SetupMarix(3 + 1, 4, 1);
  bool res = n.EqMatrix(m);
  ASSERT_EQ(res, false);
}

TEST_F(CPP_Matrix_Test, test_4) {
  m.SetupMarix(3, 4, 1);
  n.SetupMarix(3, 4 + 1, 1);
  bool res = n.EqMatrix(m);
  ASSERT_EQ(res, false);
}

TEST_F(CPP_Matrix_Test, test_5) {
  m.SetupMarix(3, 4, 1);
  n.SetupMarix(3, 4, 1);
  n(0, 0) = 1.0000001;
  bool res = n.EqMatrix(m);
  ASSERT_EQ(res, false);
}

TEST_F(CPP_Matrix_Test, test_6) {
  m.SetupMarix(3, 4, 1);
  n.SetupMarix(3, 4, 1);
  n(0, 0) = 1.00000009;
  bool res = n.EqMatrix(m);
  ASSERT_EQ(res, true);
}

// SumMatrix(...) and SubMatrix(...)
TEST_F(CPP_Matrix_Test, test_7) {
  m.SetupMarix(3, 4, 1);
  n.SetupMarix(3, 4, 2);
  S21Matrix t;
  t = m + n;
  m.SumMatrix(n);
  bool res = m.EqMatrix(t);
  ASSERT_EQ(res, true);
}

TEST_F(CPP_Matrix_Test, test_8) {
  m.SetupMarix(3, 4, 1);
  n.SetupMarix(3, 4, 2);
  S21Matrix t;
  t = n - m;
  n.SubMatrix(m);
  bool res = n.EqMatrix(t);
  ASSERT_EQ(res, true);
}

TEST_F(CPP_Matrix_Test, test_9) {
  m.SetupMarix(2, 2, 1);
  n = m * 2;
  m.MulNumber(2);
  bool res = n.EqMatrix(m);
  ASSERT_EQ(res, true);
}

TEST_F(CPP_Matrix_Test, test_10) {
  m.SetupMarix(2, 2, 1);
  m.MulNumber(2);
  cout << endl;
  n.SetRows(2);
  n.SetCols(2);
  n(0, 0) = 1 * 2;
  n(0, 1) = 2 * 2;
  n(1, 0) = 3 * 2;
  n(1, 1) = 5 * 2;
  bool res = n.EqMatrix(m);
  ASSERT_EQ(res, true);
}

// MulMatrix (...)
TEST_F(CPP_Matrix_Test, test_11) {
  m.SetupMarix(2, 3, 1);
  n.SetupMarix(3, 2, 1);
  m.MulMatrix(n);
  S21Matrix t(2, 2);
  t(0, 0) = 35;
  t(0, 1) = 52;
  t(1, 0) = 96;
  t(1, 1) = 145;
  bool res = m.EqMatrix(t);
  ASSERT_EQ(res, true);
}

TEST_F(CPP_Matrix_Test, test_12) {
  m.SetupMarix(2, 3, 1);
  n.SetupMarix(3, 2, 1);
  S21Matrix t;
  t = m * n;
  m.MulMatrix(n);
  bool res = m.EqMatrix(t);
  ASSERT_EQ(res, true);
}

TEST_F(CPP_Matrix_Test, test_13) {
  m.SetupMarix(2, 3, 1);
  n.SetupMarix(3, 2, 1);
  S21Matrix t1;
  t1 = m * n;
  S21Matrix t2(2, 2);
  t2(0, 0) = 35;
  t2(0, 1) = 52;
  t2(1, 0) = 96;
  t2(1, 1) = 145;
  bool res = t1.EqMatrix(t2);
  ASSERT_EQ(res, true);
}

// operaor =

TEST_F(CPP_Matrix_Test, test_14) {
  m.SetupMarix(2, 3, 1);
  cout << endl;
  n = m;
  bool res = m.EqMatrix(n);
  ASSERT_EQ(res, true);
}

// operaor +=

TEST_F(CPP_Matrix_Test, test_15) {
  m.SetupMarix(2, 3, 1);
  m += m;
  S21Matrix t(2, 3);
  t(0, 0) = 2;
  t(0, 1) = 4;
  t(0, 2) = 8;
  t(1, 0) = 10;
  t(1, 1) = 14;
  t(1, 2) = 20;
  bool res = m.EqMatrix(t);
  ASSERT_EQ(res, true);
}

// operaor -=

TEST_F(CPP_Matrix_Test, test_16) {
  m.SetupMarix(2, 3, 1);
  m -= m;
  S21Matrix t(2, 3);
  t(0, 0) = 0;
  t(0, 1) = 0;
  t(0, 2) = 0;
  t(1, 0) = 0;
  t(1, 1) = 0;
  t(1, 2) = 0;
  bool res = m.EqMatrix(t);
  ASSERT_EQ(res, true);
}

// operaor *= (matrix)

TEST_F(CPP_Matrix_Test, test_17) {
  m.SetupMarix(2, 3, 1);
  n.SetupMarix(3, 2, 1);
  m *= n;
  S21Matrix t(2, 2);
  t(0, 0) = 35;
  t(0, 1) = 52;
  t(1, 0) = 96;
  t(1, 1) = 145;
  bool res = m.EqMatrix(t);
  ASSERT_EQ(res, true);
}

// operaor *= (double)
TEST_F(CPP_Matrix_Test, test_18) {
  m.SetupMarix(2, 3, 1);
  m *= 2;
  S21Matrix t(2, 3);
  t(0, 0) = 2;
  t(0, 1) = 4;
  t(0, 2) = 8;
  t(1, 0) = 10;
  t(1, 1) = 14;
  t(1, 2) = 20;
  bool res = m.EqMatrix(t);
  ASSERT_EQ(res, true);
}

// Transpose()
TEST_F(CPP_Matrix_Test, test_19) {
  m.SetupMarix(2, 3, 1);
  m.Transpose();
  S21Matrix t(3, 2);
  t(0, 0) = 1;
  t(0, 1) = 5;
  t(1, 0) = 2;
  t(1, 1) = 7;
  t(2, 0) = 4;
  t(2, 1) = 10;
  bool res = m.EqMatrix(t);
  ASSERT_EQ(res, true);
}

// Determinant()
TEST_F(CPP_Matrix_Test, test_20) {
  m.SetupMarix(3, 3, 1);
  double x = m.Determinant();
  ASSERT_EQ(x, -3);
}

TEST_F(CPP_Matrix_Test, test_21) {
  m.SetupMarix(1, 1, -535);
  double x = m.Determinant();
  ASSERT_EQ(x, -535);
}

TEST_F(CPP_Matrix_Test, test_22) {
  m.SetupMarix(2, 2, 0);
  m(0, 0) = 0;
  m(0, 1) = 0;
  m(1, 0) = 3;
  m(1, 1) = 343;
  double x = m.Determinant();
  ASSERT_EQ(x, 0);
}

TEST_F(CPP_Matrix_Test, test_23) {
  m.SetupMarix(3, 3, 0);
  double x = m.Determinant();
  ASSERT_EQ(x, -3);
}

// CalcComplements()
TEST_F(CPP_Matrix_Test, test_24) {
  m.SetupMarix(3, 3, 1);
  n = m.CalcComplements();
  S21Matrix t(3, 3);
  t(0, 0) = -17;
  t(0, 1) = 25;
  t(0, 2) = -9;
  t(1, 0) = 22;
  t(1, 1) = -29;
  t(1, 2) = 9;
  t(2, 0) = -8;
  t(2, 1) = 10;
  t(2, 2) = -3;
  bool res = t.EqMatrix(n);
  ASSERT_EQ(res, true);
}

TEST_F(CPP_Matrix_Test, test_25) {
  m.SetupMarix(1, 1, 575);
  n = m.CalcComplements();
  S21Matrix t(1, 1);
  t(0, 0) = 1;
  bool res = t.EqMatrix(n);
  ASSERT_EQ(res, true);
}

// InverseMatrix()
TEST_F(CPP_Matrix_Test, test_26) {
  m.SetupMarix(3, 3, 1);
  S21Matrix inv;
  inv = m;
  n = inv.InverseMatrix();
  S21Matrix t(3, 3);
  t(0, 0) = 1;
  t(0, 1) = 0;
  t(0, 2) = 0;
  t(1, 0) = 0;
  t(1, 1) = 1;
  t(1, 2) = 0;
  t(2, 0) = 0;
  t(2, 1) = 0;
  t(2, 2) = 1;
  S21Matrix p;
  p = m * n;
  bool res = (t == p);
  ASSERT_EQ(res, true);
}

// Error
TEST_F(CPP_Matrix_Test, test27) {
  bool res = false;
  try {
    n.SumMatrix(m);
  } catch (const exception& err) {
    res = true;
  }
  ASSERT_EQ(res, true);
}

TEST_F(CPP_Matrix_Test, test28) {
  bool res = false;
  try {
    n.SubMatrix(m);
  } catch (const exception& err) {
    res = true;
  }
  ASSERT_EQ(res, true);
}

TEST_F(CPP_Matrix_Test, test29) {
  bool res = false;
  try {
    n.MulMatrix(m);
  } catch (const exception& err) {
    res = true;
  }
  ASSERT_EQ(res, true);
}

TEST_F(CPP_Matrix_Test, test30) {
  bool res = false;
  try {
    m.CalcComplements();
  } catch (const exception& err) {
    res = true;
  }
  ASSERT_EQ(res, true);
}

TEST_F(CPP_Matrix_Test, test31) {
  bool res = false;
  try {
    m.Determinant();
  } catch (const exception& err) {
    res = true;
  }
  ASSERT_EQ(res, true);
}

TEST_F(CPP_Matrix_Test, test32) {
  bool res = false;
  try {
    S21Matrix t(-1, 2);
  } catch (const exception& err) {
    res = true;
  }
  ASSERT_EQ(res, true);
}

TEST_F(CPP_Matrix_Test, test33) {
  bool res = false;
  try {
    S21Matrix m(move(m));
  } catch (const exception& err) {
    res = true;
  }
  ASSERT_EQ(res, true);
}

TEST_F(CPP_Matrix_Test, test34) {
  bool res = false;
  try {
    m.MulNumber(4.3);
  } catch (const exception& err) {
    res = true;
  }
  ASSERT_EQ(res, true);
}

TEST_F(CPP_Matrix_Test, test35) {
  bool res = false;
  try {
    m.Transpose();
  } catch (const exception& err) {
    res = true;
  }
  ASSERT_EQ(res, true);
}

TEST_F(CPP_Matrix_Test, test36) {
  bool res = false;
  try {
    S21Matrix t(2, 2);
    t(0, 0) = 1;
    t(0, 1) = 1;
    t(1, 0) = 1;
    t(1, 1) = 1;
    t.InverseMatrix();
  } catch (const exception& err) {
    res = true;
  }
  ASSERT_EQ(res, true);
}

TEST_F(CPP_Matrix_Test, test37) {
  bool res = false;
  try {
    S21Matrix t(2, 2);
    t(0, 0) = 1;
    t(0, 1) = 1;
    t(1, 0) = 1;
    t(1, 2) = 1;
  } catch (const exception& err) {
    res = true;
  }
  ASSERT_EQ(res, true);
}

TEST_F(CPP_Matrix_Test, test38) {
  bool res = false;
  try {
    S21Matrix t(2, 2);
    t(0, 0) = 1;
    t(0, 1) = 1;
    t(1, 0) = 1;
    t(1, 1) = 1;
    t.SetCols(-1);
  } catch (const exception& err) {
    res = true;
  }
  ASSERT_EQ(res, true);
}

TEST_F(CPP_Matrix_Test, test39) {
  bool res = false;
  try {
    S21Matrix t(2, 2);
    t(0, 0) = 1;
    t(0, 1) = 1;
    t(1, 0) = 1;
    t(1, 1) = 1;
    t.SetRows(-1);
  } catch (const exception& err) {
    res = true;
  }
  ASSERT_EQ(res, true);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
