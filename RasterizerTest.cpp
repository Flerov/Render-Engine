// Copyright 2022, University of Freiburg
// Author: Joel Stanciu

#include <ncurses.h>
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>
#include "Rasterizer.h"
#include "ObjectManager.h"
#include "Parser.h"
#include "Camera.h"

TEST(Rasterizer, Constructor) {
  // Setup start
  Parser parser;
  std::string filename = "test.obj";
  std::vector<std::vector<std::vector<std::vector<float>>>> data;
  parser.parsefile(filename);
  data = parser.getObject();
  ObjectManager object(data);
  // ... end

  Rasterizer raster(100, 100, &object);
  std::vector<float> a = { -1, 1, 0 };
  std::vector<float> b = { -1, -1, 0 };
  std::vector<float> c = { 1, 0, 0 };
  std::vector<float> result;
  std::vector<float> expect = { 0.25, 0.25, 0.5 };
  result = raster.barrycentricCoordinates(-0.5, 0.5, a, b, c);
  ASSERT_EQ(expect, result);
  bool pIT = raster.pointInTriangle(result);
  ASSERT_TRUE(pIT);
  result = raster.barrycentricCoordinates(1, 1, a, b, c);
  pIT = raster.pointInTriangle(result);
  ASSERT_FALSE(pIT);
  ObjectManager* parsedObject = raster.getObject();
  Matrix rot(4);
  Matrix fin(4);
  std::vector<std::vector<float>> rotationmatrix = rot.getAsVector();
  std::vector<std::vector<float>> finalmatrix = fin.getAsVector();
  parsedObject->setMatrixRotation(rotationmatrix);
  parsedObject->setMatrixFinal(finalmatrix);
  // Since all functions that are getting used inside of run and print
  // have been tested previously these functions are, because of the
  // correctness of the other, being assumed to work since
  // the filled and parsed data is only getting printed onto the screen

  // clearFrames function gets testet in FramebufferTest
}
