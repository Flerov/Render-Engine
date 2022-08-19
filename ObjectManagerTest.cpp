// Copyright 2022, University of Freiburg
// Author: Joel Stanciu

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "ObjectManager.h"
#include "Parser.h"
#include "Matrix.h"

TEST(ObjectManager, OM) {
  Parser parser;
  std::string filename = "test.obj";
  parser.parsefile(filename);
  std::vector<std::vector<std::vector<std::vector<float>>>> objectVector;
  objectVector = parser.getObject();
  ObjectManager object(objectVector);
  // Check size function
  ASSERT_EQ(objectVector.size(), object.size());
  // Check setter function
  //   check addLight
  size_t oldLightSize = object[object.size()-1][2].size();
  std::vector<float> light = { 0.5, 0.5, 0.5 };
  size_t posLight = object.addLight(light);
  size_t newLightSize = object[object.size()-1][2].size();
  ASSERT_EQ(oldLightSize+1, newLightSize);
  //   check addTransform
  size_t oldTransformSize = object[object.size()-1][3].size();
  std::vector<float> transform = { 0, 0, 1, 0 };
  size_t posTransform = object.addTransform(transform);
  size_t newTransformSize = object[object.size()-1][3].size();
  ASSERT_EQ(oldTransformSize+1, newTransformSize);
  //   check addTranslate
  size_t oldTranslateSize = object[object.size()-1][5].size();
  std::vector<float> translate = { -1, 2, 1 };
  object.addTranslate(translate);
  size_t newTranslateSize = object[object.size()-1][5].size();
  ASSERT_EQ(oldTranslateSize+1, newTranslateSize);
  //   check addScale
  size_t oldScaleSize = object[object.size()-1][4].size();
  std::vector<float> scale = { 0.1, 0.1, 0.1 };
  object.addScale(scale);
  size_t newScaleSize = object[object.size()-1][4].size();
  ASSERT_EQ(oldScaleSize+1, newScaleSize);

  //   set setLight from newly added light above
  std::vector<float> changedLight = { 0.1, 0.1, 0.1 };
  object.setLight(changedLight, posLight);
  ASSERT_EQ(changedLight[0], object[object.size()-1][2][posLight][0]);
  ASSERT_EQ(changedLight[1], object[object.size()-1][2][posLight][1]);
  ASSERT_EQ(changedLight[2], object[object.size()-1][2][posLight][2]);
  //   set setTransform from newly added transform above
  std::vector<float> changedTransform = { 1, 0, 0, 0 };
  object.setTransform(changedTransform, posTransform);
  ASSERT_EQ(changedTransform[0], object[object.size()-1][3][posTransform][0]);
  ASSERT_EQ(changedTransform[1], object[object.size()-1][3][posTransform][1]);
  ASSERT_EQ(changedTransform[2], object[object.size()-1][3][posTransform][2]);
  //   set setMatrixFinal
  Matrix fm(4);
  std::vector<std::vector<float>> finalmatrix = fm.getAsVector();
  object.setMatrixFinal(finalmatrix);
  ASSERT_EQ(finalmatrix, object[object.size()-1][1]);
  //   set setMatrixRotation
  Matrix rm(4);
  std::vector<std::vector<float>> rotationmatrix = rm.getAsVector();
  object.setMatrixRotation(rotationmatrix);
  ASSERT_EQ(rotationmatrix, object[object.size()-1][0]);
  //   set setMatrixMvp
  Matrix mvpm(4);
  std::vector<std::vector<float>> mvpmatrix = mvpm.getAsVector();
  object.setMatrixMvp(mvpmatrix);
  ASSERT_EQ(mvpmatrix, object[object.size()-1][6]);
  // check removeTransform function by adding a second transform to list
  // and then removing the same one
  std::vector<float> secondTransform = { 0, 0, 0.4, 1 };
  posTransform = object.addTransform(secondTransform);
  object.removeTransform(posTransform);
  ASSERT_EQ(oldTransformSize, object[object.size()-1][3].size()-1);
  // Check function update by adding an attribute
  std::vector<std::vector<std::vector<float>>> attribute;
  attribute = objectVector[2];
  objectVector.push_back(attribute);
  object.update(objectVector);
  ASSERT_EQ(objectVector.size(), object.size());
}
