// Copyright 2022, University of Freiburg
// Author: Joel Stanciu

#ifndef CAMERA_H_
#define CAMERA_H_

#include <cmath>
#include <vector>
#include "Matrix.h"

/*
  This class represents a Camera Object, which is used as a Camera in the
  dimensions of the Terminal. It acts as a viewport from which further
  calculations for representing an Object in 3Dimensional Space are
  dependent on. It also affects the view of an rotated object in space
*/
class Camera {
 public:
// ____________________________________________________________________________
// Constructor
  Camera();
// ____________________________________________________________________________
// Getter for private member projectionMatrix_
  Matrix& getProjectionMatrix() { return projectionMatrix_; }
// ____________________________________________________________________________
// Getter for private memver viewMatrix_
  Matrix& getViewMatrix() { return viewMatrix_; }
// ____________________________________________________________________________
// Getter for the Projection View Matrix which gets calculated
// by multiplying the Projection Matrix with the View Matrix
  Matrix& getProjectionViewMatrix() {
                    return projectionMatrix_ * viewMatrix_; }
// ____________________________________________________________________________
// Getter for the private member position_ (only used in tests)
  std::vector<float>& getPosition() { return position_; }
// ____________________________________________________________________________
// Getter for the private member rotation_ (only used in tests)
  std::vector<float>& getRotation() { return rotation_; }
// ____________________________________________________________________________
// Getter for the private member fieldOfView_ (only used in tests)
  float getFieldOfView() { return fieldOfView_; }
// ____________________________________________________________________________
// Getter for the private member aspectRatio_ (only used in tests)
  float getAspectRatio() { return aspectRatio_; }
// ____________________________________________________________________________
// Getter for the private member nearPlane_ (only used in tests)
  float getNearPlane() { return nearPlane_; }
// ____________________________________________________________________________
// Getter for the private member farPlane_ (only used in tests)
  float getFarPlane() { return farPlane_; }
// ____________________________________________________________________________
// Setter for the private member position_ (only used in tests)
  void setPosition(std::vector<float> position);
// ____________________________________________________________________________
// Setter for the private member rotation_ (only used in tests)
  void setRotation(std::vector<float> rotation);
// ____________________________________________________________________________
// Setter for the Projection described for further calculations of the
// rotation relative to the camera's setting (setting variables
// as private members)
  void setProjection(float fov, float aspectRatio,
                   float nearPlane, float farPlane);
// ____________________________________________________________________________
// Setter for the viewmatrix, describing the cameras settings as a matrix
  void setViewMatrix();
// ____________________________________________________________________________
 private:
  float fieldOfView_, aspectRatio_, nearPlane_, farPlane_;
  std::vector<float> position_;
  std::vector<float> rotation_;
  Matrix viewMatrix_;
  Matrix projectionMatrix_;
};

#endif  // CAMERA_H_
