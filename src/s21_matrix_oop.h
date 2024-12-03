#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>

namespace s21_matrix {

#define S21_NAN 0.0000001

class S21Matrix {
 private:
  int rows_{0}, cols_{0};
  double **matrix_{nullptr};

 public:
  ///    конструкторы матриц
  S21Matrix() noexcept;
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  ///     Оперции над матрицами
  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);  // different matrix dimensions.
  void SubMatrix(const S21Matrix &other);  // different matrix dimensions.
  void MulNumber(const double num);
  void MulMatrix(
      const S21Matrix &other);  // The number of columns of
                                // the first matrix is not equal to the
                                // number of rows of the second matrix.
  S21Matrix Transpose();
  S21Matrix CalcComplements();  // The matrix is not square.
  double Determinant();         // The matrix is not square.
  S21Matrix InverseMatrix();    // Matrix determinant is 0.

  ///     Операторы соответствующие операциям
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(double num);
  S21Matrix &operator=(const S21Matrix &other) noexcept;
  S21Matrix &operator=(S21Matrix &&other) noexcept;
  bool operator==(S21Matrix &other) noexcept;
  void operator+=(const S21Matrix &other);
  void operator-=(const S21Matrix &other);
  void operator*=(const S21Matrix &other);
  void operator*=(double num) noexcept;
  double &operator()(int rows, int cols);

  ///     Вспомогательные функции
  void MemoryAllocation();
  void MemoryFree();
  void CopyValues(int rows, int cols, const S21Matrix &other);
  void Record_Value(int rows, int cols, double x);
  void SetupMarix(int rows, int cols, double x);
  void SetRows(int rows);
  void SetCols(int cols);
  int GaussTransform();
  int ZeroDown(int m, int *s);
  int ChekLine();
  double MinorCalculation(int m, int n, const S21Matrix &other);
};
}  // namespace s21_matrix

#endif