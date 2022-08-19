// Copyright 2022, University of Freiburg
// Author: Joel Stanciu

#include <gtest/gtest.h>
#include <vector>
#include "Camera.h"

// Test setProjection to initialize the camera
// Includes the test of funciton setViewMatrix
// becuase that function get called in the constructor
TEST(Camera, Projection) {
  Camera camera;
  float fieldOvView = 0.5;
  float aspectRatio = 1.25;
  float nearPlane = 100;
  float farPlane = 800;
  camera.setProjection(fieldOvView, aspectRatio, nearPlane, farPlane);
  std::vector<float> standardPosition = camera.getPosition();
  std::vector<float> standardRotation = camera.getRotation();
  std::vector<std::vector<float>> standardViewMatrix =
                                  camera.getViewMatrix().getAsVector();
  std::vector<std::vector<float>> standardProjectionMatrix =
                                  camera.getProjectionMatrix().getAsVector();
  Matrix expectedViewMatrix(4);
  std::vector<std::vector<float>> expectedProjectionMatrix;
  expectedProjectionMatrix = { { 3.133054, 0, 0, 0 },
                               { 0, 3.9163175, 0, 0 },
                               { 0, 0, -1.2857143, -1 },
                               { 0, 0, -228.57143, 1 } };
  std::vector<float> expectedPositionVector = { 0, 0, 0 };
  std::vector<float> expectedRotationVector = { 0, 0, 0 };
  ASSERT_EQ(expectedPositionVector, standardPosition);
  ASSERT_EQ(expectedRotationVector, standardRotation);
  ASSERT_EQ(expectedViewMatrix.getAsVector(), standardViewMatrix);
  for (size_t i = 0; i < expectedProjectionMatrix.size(); i++) {
    for (size_t k = 0; k < expectedProjectionMatrix.size(); k++) {
      ASSERT_FLOAT_EQ(expectedProjectionMatrix[i][k],
                      standardProjectionMatrix[i][k]);
    }
  }
}

// Test function setPosition
TEST(Camera, Position) {
  Camera camera;
  std::vector<float> pos = { 1, 1, 1 };
  std::vector<float> expected = { 1, 1, 1 };
  std::vector<float> result;
  camera.setPosition(pos);
  ASSERT_EQ(expected, camera.getPosition());
}

// Test function setRotation
TEST(Camera, Rotation) {
  Camera camera;
  std::vector<float> rot = { -1, 0.5, 1 };
  std::vector<float> expected = { -1, 0.5, 1 };
  std::vector<float> result;
  camera.setRotation(rot);
  ASSERT_EQ(expected, camera.getRotation());
}
