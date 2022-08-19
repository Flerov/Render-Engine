// Copyright 2022, University of Freiburg
// Author: Joel Stanciu (joelstanciu@outlook.de)

#ifndef MATRIX_H_
#define MATRIX_H_

#include <math.h>
#include <vector>
#include <utility>

class Matrix {
 public:
// ____________________________________________________________________________
// Construtor
  Matrix() {  }
// ____________________________________________________________________________
// Constructor. Initializes an vector field representing a matrix of
// the given dimension as the identity matrix of that dimension
  explicit Matrix(size_t dimension);
// ____________________________________________________________________________
// Destructor
  ~Matrix();
// ____________________________________________________________________________
// Operator overload. Assigns a given vector field, representing a matrix
// to the current matrix
  const Matrix& operator=(std::vector<std::vector<float>> matrix);
// ____________________________________________________________________________
// Operator overload. Calculates the multiplication of two matrix'
// assigns the result of the calculation to the current matrix.
// And returns the current matrix
  Matrix& operator*(Matrix matrix);
// ____________________________________________________________________________
// Caluclation to scale the matrix by the given vector
  void scale(std::vector<float> scale);
// ____________________________________________________________________________
// Calculate the translate the current matrix by the given vector
  void translate(std::vector<float> t);
// ____________________________________________________________________________
// Getter which return the dimension of the matrix
  size_t getDimension() { return dimension_; }
// ____________________________________________________________________________
// Set the current matrix to its identity matrix
  void reset();
// ____________________________________________________________________________
// Static function which calculate the transformation of a vertex in space
// represented by a vector and the given matrix by the given calculus
  static std::vector<float> transformVertex(std::vector<float> vertex,
                   std::vector<std::vector<float>> MVPMatrix);
// ____________________________________________________________________________
// Returns the matrix as a vector list of vectors which represents the matrix
  std::vector<std::vector<float>>& getAsVector();
// ____________________________________________________________________________
// Static function which calculates the multiplicational outcome of a
// given matrix and a given vector by the given calculus
  static std::vector<float> vector_multiplication(
     const std::vector<std::vector<float>>& matrix,
     const std::vector<float>& vector);
// ____________________________________________________________________________
// Calculates the rotation of the matrix by a given vector,
// which describes the angle of rotation, and a given angle
// by the given calculus
  Matrix& rotate(const std::vector<float> v_3, float angle);
// ____________________________________________________________________________
 private:
  std::vector<std::vector<float>> matrix_;
  size_t dimension_;
};

#endif  // MATRIX_H_
