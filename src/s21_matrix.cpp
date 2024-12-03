#include "s21_matrix_oop.h"

using namespace std;

namespace s21_matrix {

// Конструкторы

S21Matrix::S21Matrix() noexcept {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 0 || cols < 0) {
    throw out_of_range("Incorrect input, matrices should have the same size !");
  }
  MemoryAllocation();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  MemoryAllocation();
  CopyValues(rows_, cols_, other);
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  if (this == &other) {
    throw out_of_range("Transferring the matrix to itself !");
  }
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  MemoryFree();
  rows_ = 0;
  cols_ = 0;
}

// Операции

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool result = true;
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    int i = 0;
    while (i < rows_ && result) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > S21_NAN) {
          result = false;
        }
      }
      i++;
    }
  } else {
    result = false;
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_ ||
      other.matrix_ == nullptr) {
    throw out_of_range("Different matrix dimensions!");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_ ||
      other.matrix_ == nullptr) {
    throw out_of_range("Different matrix dimensions!");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (matrix_ == nullptr) {
    throw out_of_range("Matrix does not exist!");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = num * matrix_[i][j];
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_ || other.matrix_ == nullptr) {
    throw out_of_range("Different matrix dimensions!");
  }
  S21Matrix temp(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      temp.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++) {
        temp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  SetCols(other.cols_);
  CopyValues(rows_, other.cols_, temp);
}

S21Matrix S21Matrix::Transpose() {
  if (matrix_ == nullptr) {
    throw out_of_range("Matrix does not exist!");
  }
  S21Matrix temp(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      temp.matrix_[j][i] = matrix_[i][j];
    }
  }
  MemoryFree();
  rows_ = temp.rows_;
  cols_ = temp.cols_;
  MemoryAllocation();
  CopyValues(rows_, cols_, temp);
  return *this;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_ || matrix_ == nullptr) {
    throw out_of_range("The matrix is not square!");
  }
  double det = 1;
  if (rows_ == 1) {
    det = matrix_[0][0];
  } else if (ChekLine() == 1) {
    det = 0;
  } else if (rows_ > 1) {
    S21Matrix temp(rows_, cols_);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        temp.matrix_[i][j] = matrix_[i][j];
      }
    }

    int sign = temp.GaussTransform();

    for (int j = 0; j < temp.cols_; j++) {
      det = det * temp.matrix_[j][j];
    }
    det = det * sign;
  }

  return det;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_ || matrix_ == nullptr) {
    throw out_of_range("The matrix is not square!");
  }
  if (rows_ == 1) {
    matrix_[0][0] = 1;
  } else {
    S21Matrix temp(rows_, cols_);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        temp.matrix_[i][j] = matrix_[i][j];
      }
    }

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = MinorCalculation(i, j, temp);
      }
    }
  }

  return *this;
}

S21Matrix S21Matrix::InverseMatrix() {
  double A = Determinant();
  if (A == 0) {
    throw out_of_range("Еhe determinant of the matrix is zero!");
  }
  S21Matrix comp;
  comp = CalcComplements();
  comp.Transpose();
  comp *= 1 / A;
  return comp;
}

// Операторы

S21Matrix &S21Matrix::operator=(const S21Matrix &other) noexcept {
  SetCols(other.cols_);
  SetRows(other.rows_);
  CopyValues(other.rows_, other.cols_, other);
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  swap(rows_, other.rows_);
  swap(cols_, other.cols_);
  swap(matrix_, other.matrix_);
  return *this;
}

bool S21Matrix::operator==(S21Matrix &other) noexcept {
  bool result = true;
  if (!EqMatrix(other)) result = false;
  return result;
}

double &S21Matrix::operator()(int rows, int cols) {
  if (rows >= rows_ || cols >= cols_) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[rows][cols];
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix tmp(rows_, cols_);
  tmp.CopyValues(rows_, cols_, *this);
  tmp.SumMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix tmp(rows_, cols_);
  tmp.CopyValues(rows_, cols_, *this);
  tmp.SubMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator*(double num) {
  S21Matrix tmp(rows_, cols_);
  tmp.CopyValues(rows_, cols_, *this);
  tmp.MulNumber(num);
  return tmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix tmp(rows_, cols_);
  tmp.CopyValues(rows_, cols_, *this);
  tmp.MulMatrix(other);
  return tmp;
}

void S21Matrix::operator+=(const S21Matrix &other) { SumMatrix(other); }

void S21Matrix::operator-=(const S21Matrix &other) { SubMatrix(other); }

void S21Matrix::operator*=(const S21Matrix &other) { MulMatrix(other); }

void S21Matrix::operator*=(double num) noexcept { MulNumber(num); }

// Вспомогательные функции

void S21Matrix::MemoryAllocation() {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

void S21Matrix::MemoryFree() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

void S21Matrix::CopyValues(int rows, int cols, const S21Matrix &other) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::Record_Value(int rows, int cols, double x) {
  matrix_[rows][cols] = x;
}

void S21Matrix::SetRows(int rows) {
  if (rows <= 0) {
    throw out_of_range("Incorrect input, matrices should have the same size");
  }
  if (rows_ != rows) {
    S21Matrix tmp(move(*this));
    int buf_rows = tmp.rows_;
    if (tmp.rows_ > rows) buf_rows = rows;
    cols_ = tmp.cols_;
    rows_ = rows;
    MemoryAllocation();
    CopyValues(buf_rows, cols_, tmp);
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols <= 0) {
    throw out_of_range("Incorrect input, matrices should have the same size");
  }
  if (cols_ != cols) {
    S21Matrix tmp(move(*this));
    int buf_cols = tmp.cols_;
    if (tmp.cols_ > cols) buf_cols = cols;
    rows_ = tmp.rows_;
    cols_ = cols;
    MemoryAllocation();
    CopyValues(rows_, buf_cols, tmp);
  }
}

void S21Matrix::SetupMarix(int rows, int cols, double x) {
  SetRows(rows);
  SetCols(cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      x = x + j + i;
      Record_Value(i, j, x);
    }
  }
}

int S21Matrix::GaussTransform() {
  int sign = 1;
  int i = 0;
  double coeff;

  while (i < rows_ - 1 && ChekLine() == 0 && ZeroDown(i, &sign) == 0) {
    for (int n = i + 1; n < rows_; n++) {
      coeff = matrix_[n][i] / matrix_[i][i];
      for (int j = i; j < cols_; j++) {
        matrix_[n][j] = matrix_[n][j] - matrix_[i][j] * coeff;
      }
    }
    i++;
  }

  return sign;
}

int S21Matrix::ZeroDown(int m, int *s) {
  int result = 0;
  if (matrix_[m][m] == 0) {
    int k = m + 1;
    while (k < rows_ && matrix_[k][m] == 0) k++;
    if (k == rows_) result = 1;
    if (k < rows_) {
      double buffer;
      for (int j = 0; j < cols_; j++) {
        buffer = matrix_[m][j];
        matrix_[m][j] = matrix_[k][j];
        matrix_[k][j] = buffer;
      }
      *s = *s * (-1);
    }
  }
  return result;
}

int S21Matrix::ChekLine() {
  int result = 0;
  int i = 0;
  int j = 0;

  while (i < rows_ && result == 0) {
    result = 1;
    for (j = 0; j < cols_; j++) {
      if (matrix_[i][j] != 0) result = 0;
    }
    i++;
  }

  j = 0;

  while (j < cols_ && result == 0) {
    result = 1;
    for (i = 0; i < rows_; i++) {
      if (matrix_[i][j] != 0) result = 0;
    }
    j++;
  }

  return result;
}

double S21Matrix::MinorCalculation(int m, int n, const S21Matrix &other) {
  double result = 0;
  S21Matrix minor(other.rows_ - 1, other.cols_ - 1);
  int k = 0;
  int l = 0;

  for (int i = 0; i < other.rows_; i++) {
    if (i == m) i++;
    if (i < other.rows_) {
      for (int j = 0; j < other.cols_; j++) {
        if (j == n) j++;
        if (j < other.cols_) {
          minor.matrix_[k][l] = other.matrix_[i][j];
          l++;
        }
      }
      l = 0;
      k++;
    }
  }

  result = pow(-1, m + n) * minor.Determinant();

  return result;
}

}  // namespace s21_matrix
