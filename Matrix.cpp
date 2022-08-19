// Copyright 2022, University of Freiburg
// Author: Joel Stanciu (joelstanciu@outlook.de)

#include <cstdio>
#include <vector>
#include <utility>
#include "./Matrix.h"

// ____________________________________________________________________________
// Creates the Identiy Matrix of a given dimension
Matrix::Matrix(size_t dimension) {
  dimension_ = dimension;
  std::vector<float> current;
  for (size_t i = 0; i < dimension_; i++) {
    for (size_t k = 0; k < dimension_; k++) {
      current.push_back(0);
    }
    current[i] = 1;
    matrix_.push_back(current);
    current.clear();
  }
}

// ____________________________________________________________________________
Matrix::~Matrix() {
  return;
}

// ____________________________________________________________________________
void Matrix::reset() {
  matrix_.clear();
  for (size_t i = 0; i < dimension_; i++) {
    std::vector<float> current;
    for (size_t k = 0; k < dimension_; k++) {
      current.push_back(0);
    }
    current[i] = 1;
    matrix_.push_back(current);
  }
}

// ____________________________________________________________________________
const Matrix& Matrix::operator=(std::vector<std::vector<float>> matrix) {
  dimension_ = matrix.size();
  matrix_.clear();
  matrix_ = std::move(matrix);
  return *this;
}

// ____________________________________________________________________________
std::vector<std::vector<float>>& Matrix::getAsVector() {
  return matrix_;
}

// ____________________________________________________________________________
Matrix& Matrix::operator*(Matrix matrix) {
  std::vector<std::vector<float>> rs;
  std::vector<std::vector<float>> mv = matrix.getAsVector();
  std::vector<float> placeholder;
  for (size_t n = 0; n < matrix_.size(); n++) {
    rs.push_back(placeholder);
    for (size_t i = 0; i < mv.size(); i++) {
      rs[n].push_back(0);
      for (size_t k = 0; k < mv.size(); k++) {
        rs[n][i] += matrix_[n][k] * mv[k][i];
      }
    }
  }
  matrix_ = std::move(rs);
  return *this;
}

// ____________________________________________________________________________
void Matrix::scale(std::vector<float> scale) {
  for (size_t i = 0; i < scale.size(); i++) {
    for (size_t k = 0; k < matrix_.size(); k++) {
      matrix_[i][k] *= scale[i];
    }
  }
}

// ____________________________________________________________________________
void Matrix::translate(std::vector<float> t) {
  size_t index = matrix_.size()-1;
  for (size_t n = 0; n < matrix_.size(); n++) {
    for (size_t i = 0; i < t.size(); i++) {
      matrix_[index][n] += matrix_[i][n] * t[i];
    }
  }
}

// ____________________________________________________________________________
std::vector<float> Matrix::vector_multiplication(
     const std::vector<std::vector<float>>& matrix,
     const std::vector<float>& vector) {
  std::vector<float> result = { 0, 0, 0, 0 };
  for (size_t i = 0; i < vector.size(); i++) {
    for (size_t k = 0; k < vector.size(); k++) {
      result[i] += matrix[k][i] * vector[k];
    }
  }
  return result;
}

// ____________________________________________________________________________
std::vector<float> Matrix::transformVertex(std::vector<float> vertex,
                   std::vector<std::vector<float>> MVPMatrix) {
  std::vector<float> result;
  result = std::move(Matrix::vector_multiplication(MVPMatrix, vertex));
  result[0] /= result[3];
  result[1] /= result[3];
  result[2] /= result[3];
  return result;
}

// ____________________________________________________________________________
Matrix& Matrix::rotate(const std::vector<float> v_3, float angle) {
  if (matrix_.size() != 4) {
    return *this;
  }
  float c = cos(angle);
  float s = sin(angle);
  float oneminusc = 1.0f - c;
  float xy = v_3[0] * v_3[1];
  float yz = v_3[1] * v_3[2];
  float xz = v_3[0] * v_3[2];

  float xs = v_3[0] * s;
  float ys = v_3[1] * s;
  float zs = v_3[2] * s;

  float f00 = v_3[0] * v_3[0] * oneminusc + c;
  float f01 = xy * oneminusc + zs;
  float f02 = xz * oneminusc - ys;
  float f10 = xy * oneminusc - zs;
  float f11 = v_3[1] * v_3[1] * oneminusc + c;
  float f12 = yz * oneminusc + xs;
  float f20 = xz * oneminusc + ys;
  float f21 = yz * oneminusc - xs;
  float f22 = v_3[2] * v_3[2] * oneminusc + c;

  float t00 = matrix_[0][0] * f00 + matrix_[1][0] * f01 + matrix_[2][0] * f02;
  float t01 = matrix_[0][1] * f00 + matrix_[1][1] * f01 + matrix_[2][1] * f02;
  float t02 = matrix_[0][2] * f00 + matrix_[1][2] * f01 + matrix_[2][2] * f02;
  float t03 = matrix_[0][3] * f00 + matrix_[1][3] * f01 + matrix_[2][3] * f02;

  float t10 = matrix_[0][0] * f10 + matrix_[1][0] * f11 + matrix_[2][0] * f12;
  float t11 = matrix_[0][1] * f10 + matrix_[1][1] * f11 + matrix_[2][1] * f12;
  float t12 = matrix_[0][2] * f10 + matrix_[1][2] * f11 + matrix_[2][2] * f12;
  float t13 = matrix_[0][3] * f10 + matrix_[1][3] * f11 + matrix_[2][3] * f12;

  matrix_[2][0] = matrix_[0][0] * f20 + matrix_[1][0] * f21 +
                                        matrix_[2][0] * f22;
  matrix_[2][1] = matrix_[0][1] * f20 + matrix_[1][1] * f21 +
                                        matrix_[2][1] * f22;
  matrix_[2][2] = matrix_[0][2] * f20 + matrix_[1][2] * f21 +
                                        matrix_[2][2] * f22;
  matrix_[2][3] = matrix_[0][3] * f20 + matrix_[1][3] * f21 +
                                        matrix_[2][3] * f22;

  matrix_[0][0] = t00;
  matrix_[0][1] = t01;
  matrix_[0][2] = t02;
  matrix_[0][3] = t03;
  matrix_[1][0] = t10;
  matrix_[1][1] = t11;
  matrix_[1][2] = t12;
  matrix_[1][3] = t13;

  return *this;
}
