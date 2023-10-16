// Copyright 2022, University of Freiburg
// Author: Joel Stanciu

#include <cstdio>
#include <vector>
#include <utility>
#include "./Camera.h"

// ____________________________________________________________________________
Camera::Camera() {
  fieldOfView_ = 0;
  aspectRatio_ = 0;
  nearPlane_ = 0;
  farPlane_ = 0;
  position_ = { 0, 0, 0 };
  rotation_ = { 0, 1, 0 };
  viewMatrix_ = Matrix(4);
  projectionMatrix_ = Matrix(4);
  setViewMatrix();
}

// ____________________________________________________________________________
void Camera::setPosition(std::vector<float> position) {
  position_ = std::move(position);
}

// ____________________________________________________________________________
void Camera::setRotation(std::vector<float> rotation) {
  rotation_ = std::move(rotation);
}

// ____________________________________________________________________________
void Camera::setProjection(float fov, float aspectRatio,
                 float nearPlane, float farPlane) {
  //projectionMatrix_.reset();
  float tanhfov = static_cast<float>(tanf(fov/2));
  std::vector<std::vector<float>> mv = projectionMatrix_.getAsVector();
  mv[0][0] = 1 / (aspectRatio * tanhfov);
  mv[1][1] = 1 / tanhfov;
  mv[2][2] = -(nearPlane + farPlane) / (farPlane - nearPlane);
  mv[2][3] = -1;
  mv[3][2] = -(2 * farPlane * nearPlane) / (farPlane - nearPlane);
  projectionMatrix_ = mv;
}

// ____________________________________________________________________________
void Camera::setViewMatrix() {
  //viewMatrix_.reset();
  //projectionMatrix_.reset();
  std::vector<float> e_1 = { 1, 0, 0 };
  std::vector<float> e_2 = { 0, 1, 0 };
  std::vector<float> e_3 = { 0, 0, 1 };
  viewMatrix_.rotate(e_1, rotation_[0]);
  viewMatrix_.rotate(e_2, rotation_[1]);
  viewMatrix_.rotate(e_3, rotation_[2]);
  viewMatrix_.translate(position_);
}
