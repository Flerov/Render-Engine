// Copyright 2022, University of Freiburg
// Author: Joel Stanciu

#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "./Matrix.h"

// Test Constructor
TEST(Matrix, Constructor) {
  // ... for Matrix of dimension 3
  Matrix matrix(3);
  std::vector<std::vector<float>> matrix3x3 = matrix.getAsVector();
  for (std::vector<float> row : matrix3x3) {
    size_t row_result = 0;
    for (float curr : row) {
      row_result += curr;
    }
    ASSERT_EQ(1, row_result);
  }
  // ... for Matrix of dimension 6
  Matrix matrix2(6);
  std::vector<std::vector<float>> matrix6x6 = matrix2.getAsVector();
  for (std::vector<float> row : matrix6x6) {
    size_t row_result = 0;
    for (float curr : row) {
      row_result += curr;
    }
    ASSERT_EQ(1, row_result);
  }
}

// Test function getAsVector()
TEST(Matrix, Vector) {
  Matrix matrix(2);
  std::vector<std::vector<float>> check = { { 1, 0 }, { 0, 1 } };
  ASSERT_EQ(check, matrix.getAsVector());
  Matrix matrix2(4);
  check = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0}, { 0, 0, 0, 1} };
  ASSERT_EQ(check, matrix2.getAsVector());
}

// Test assignment operator overload
TEST(Matrix, assignment) {
  Matrix matrix(3);
  Matrix matrix2(6);
  std::vector<std::vector<float>> matrix6x6 = matrix2.getAsVector();
  matrix = matrix6x6;
  matrix6x6 = matrix.getAsVector();
  size_t result = 0;
  for (std::vector<float> row : matrix6x6) {
    for (float curr : row) {
      result += curr;
    }
  }
  ASSERT_EQ(6, result);
}

// Test multiplication operator overload
TEST(Matrix, multiplication) {
  Matrix matrix1(2);
  Matrix matrix2(2);
  Matrix result(2);
  std::vector<std::vector<float>> data1 = matrix1.getAsVector();
  std::vector<std::vector<float>> data2 = matrix2.getAsVector();
  std::vector<std::vector<float>> vector_result;

  matrix1 * matrix2;
  vector_result = matrix1.getAsVector();
  ASSERT_EQ(1, vector_result[0][0]);
  ASSERT_EQ(0, vector_result[0][1]);
  ASSERT_EQ(0, vector_result[1][0]);
  ASSERT_EQ(1, vector_result[1][1]);

  data1[0][0] = 2;
  data1[0][1] = 2;
  data2[1][0] = 3;
  matrix1 = data1;
  matrix2 = data2;
  matrix1 * matrix2;
  vector_result = matrix1.getAsVector();
  ASSERT_EQ(8, vector_result[0][0]);
  ASSERT_EQ(2, vector_result[0][1]);
  ASSERT_EQ(3, vector_result[1][0]);
  ASSERT_EQ(1, vector_result[1][1]);
}

// Test function scale
TEST(Matrix, scale) {
  Matrix matrix(1);
  std::vector<float> scaler = { 5 };
  matrix.scale(scaler);
  ASSERT_EQ(5, matrix.getAsVector()[0][0]);
  Matrix matrix2(3);
  scaler = { 0.25, 0.25, 0.25 };
  matrix2.scale(scaler);
  std::vector<std::vector<float>> result = matrix2.getAsVector();
  size_t identity_index = 0;
  for (size_t i = 0; i < result.size(); i++) {
    for (size_t k = 0; k < result.size(); k++) {
      if (i == identity_index && k == identity_index) {
        ASSERT_EQ(0.25, result[i][k]);
        identity_index += 1;
      } else {
        ASSERT_EQ(0, result[i][k]);
      }
    }
  }
}

// Test function translate
TEST(Matrix, translate) {
  Matrix matrix(1);
  std::vector<float> translate = { -5 };
  matrix.translate(translate);
  ASSERT_EQ(-4, matrix.getAsVector()[0][0]);
  Matrix matrix2(3);
  translate = { 2, -3, -1 };
  matrix2.translate(translate);
  std::vector<std::vector<float>> result = matrix2.getAsVector();
  ASSERT_EQ(1, result[0][0]);
  ASSERT_EQ(0, result[0][1]);
  ASSERT_EQ(0, result[0][2]);
  ASSERT_EQ(0, result[1][0]);
  ASSERT_EQ(1, result[1][1]);
  ASSERT_EQ(0, result[1][2]);
  ASSERT_EQ(0, result[2][0]);
  ASSERT_EQ(0, result[2][1]);
  ASSERT_EQ(0, result[2][2]);
}

// Test function rotate
TEST(Matrix, rotate) {
  Matrix matrix(4);
  std::vector<float> rotationPoint = { 0, 0, 1, 0 };
  float angle = 1.5708 * 180/M_PI;
  matrix.rotate(rotationPoint, angle);
  std::vector<std::vector<float>> result = matrix.getAsVector();
  ASSERT_FLOAT_EQ(-0.44826457, result[0][0]);
  ASSERT_FLOAT_EQ(0.893901, result[0][1]);
  ASSERT_EQ(0, result[0][2]);
  ASSERT_EQ(0, result[0][3]);
  ASSERT_FLOAT_EQ(-0.893901, result[1][0]);
  ASSERT_FLOAT_EQ(-0.44826457, result[1][1]);
  ASSERT_EQ(0, result[1][2]);
  ASSERT_EQ(0, result[1][3]);
  ASSERT_EQ(0, result[2][0]);
  ASSERT_EQ(0, result[2][1]);
  ASSERT_EQ(1, result[2][2]);
  ASSERT_EQ(0, result[2][3]);
  ASSERT_EQ(0, result[3][0]);
  ASSERT_EQ(0, result[3][1]);
  ASSERT_EQ(0, result[3][2]);
  ASSERT_EQ(1, result[3][3]);

  Matrix matrix_fail(3);
  Matrix check(3);
  matrix_fail.rotate(rotationPoint, angle);
  ASSERT_EQ(check.getAsVector(), check.getAsVector());
}

// Test function transformVertex
TEST(Matrix, TransformVertex) {
  Matrix mvpTestMatrix(4);
  std::vector<std::vector<float>> mvp = mvpTestMatrix.getAsVector();
  std::vector<float> vertex = { -1, 1, 1, 1 };
  std::vector<float> result;
  std::vector<float> expected = { -1, 1, 1, 1 };
  result = Matrix::transformVertex(vertex, mvp);
  ASSERT_EQ(expected, result);
  mvp = { { 0.5, 0.6, -0.2, 0.0 },
          { 0.2, -0.1, -0.025, 0.45 },
          { 0.01, 0.11, 0.5, 0.3 },
          { 0, -0.2, 0.8, 0.3 } };
  expected = { -0.27619052, -0.752381, 1.404762, 1.05 };
  result = Matrix::transformVertex(vertex, mvp);
  ASSERT_EQ(expected.size(), result.size());
  for (size_t i = 0; i < expected.size(); i++) {
    ASSERT_FLOAT_EQ(expected[i], result[i]);
  }
}
