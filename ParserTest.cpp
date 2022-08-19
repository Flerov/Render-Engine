// Copyright 2022, University of Freiburg
// Author: Joel Stanciu

#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <vector>
#include <cstdio>
#include "Parser.h"

// Test function parseLineVertex
TEST(Parser, LineVertex) {
  Parser parser;
  std::string line = "v -2.0 1.0 -1.0";
  std::vector<float> points;
  std::vector<float> result = { -2.0, 1.0, -1.0, 1 };
  points = parser.parseLineVertex(line);
  ASSERT_EQ(result, points);
}

// Test function getObject
TEST(Parser, getObject) {
  Parser parser;
  std::vector<std::vector<std::vector<std::vector<float>>>> object;
  object = parser.getObject();
  ASSERT_EQ(0, object.size());
}

// Test function parseLineTexture
TEST(Parser, LineTexture) {
  Parser parser;
  std::string line = "vt -1.0 1.0";
  std::vector<float> points;
  std::vector<float> result = { -1.0, 1.0 };
  points = parser.parseLineTexture(line);
  ASSERT_EQ(result, points);
}

// Test function parseLineNormal
TEST(Parser, LineNormal) {
  Parser parser;
  std::string line = "vn -0.25 4.0 -1.0";
  std::vector<float> points;
  std::vector<float> result = { -0.25, 4.0, -1.0 };
  points = parser.parseLineNormal(line);
  ASSERT_EQ(result, points);
}

// Test function parseLineFace
TEST(Parser, LineFace) {
  Parser parser;
  std::string lineV = "v -1.0 1.0 -1.0";
  std::string lineVT = "vt -2.0 1.0";
  std::string lineVN = "vn -0.25 1.25 -1.25";
  std::string line = "f 1/1/1 1/1/1 1/1/1";
  std::vector<std::vector<float>> v;
  v.push_back(parser.parseLineVertex(lineV));
  std::vector<std::vector<float>> vt;
  vt.push_back(parser.parseLineTexture(lineVT));
  std::vector<std::vector<float>> vn;
  vn.push_back(parser.parseLineNormal(lineVN));
  std::vector<std::vector<std::vector<std::vector<float>>>> result;
  std::vector<std::vector<std::vector<std::vector<float>>>> check;
  check = {
           {
            { { -1, 1, -1, 1 }, { -2, 1 }, { -0.25, 1.25, -1.25 } },
            { { -1, 1, -1, 1 }, { -2, 1 }, { -0.25, 1.25, -1.25 } },
            { { -1, 1, -1, 1 }, { -2, 1 }, { -0.25, 1.25, -1.25 } }
           }
          };
  parser.parseLineFace(line, v, vt, vn);
  result = parser.getObject();
  ASSERT_EQ(check, result);
}

// Test function parseFile
TEST(Parser, File) {
  Parser parser;
  std::string file("test.obj");
  parser.parsefile(file);
  std::vector<std::vector<std::vector<std::vector<float>>>> object;
  std::vector<std::vector<std::vector<std::vector<float>>>> result;
  result = {
            {
             { { 1, 1, 1, 1 }, { 0, 0.4 },
               { 0.2, 0.9, 0.1 } },
             { { 0.5, -0.1, -1.0, 1 }, { 0.0, 0.6 },
               { 0.5, -0.7, -0.3 } },
             { { 1.1, -0.9, -1, 1 }, { 0.0, 0.6 },
               { 0.8, -0.2, -0.5 } }
            },
            {
             { { 0.5, -0.1, -1.0, 1 }, { 0.0, 0.8 },
               { 0.8, 0.2, 0.4 } },
             { { 1, -1, 1, 1 }, { 0.0, 0.5 },
               { 0.2, 0.9, 0.1 } },
             { { 1, -1, 1, 1 }, { 0.0, 0.75},
               { 0.2, 0.9, 0.1 } }
            },
            {
             { { 1, -1, 1, 1 }, { 0.0, 0.6 },
               { 0.8, 0.2, 0.4 } },
             { { 1.1, -0.9, -1, 1 }, { 0.0, 0.6 },
               { 0.2, 0.9, 0.1 } },
             { { 0.5, -0.1, -1.0, 1 },
               { 0.0, 0.8 }, { 0.8, 0.2, 0.4 } }
            },
            {
             { { 1.1, -0.9, -1, 1 }, { 0.0, 0.5 },
               { 0.8, 0.2, 0.4 } },
             { { 1, -1, 1, 1 }, { 0, 0.4 },
               { 0.5, -0.7, -0.3 } },
             { { 1.1, -0.9, -1, 1 }, { 0.0, 0.5 },
               { 0.8, 0.2, 0.4 } }
            },
            {
             { { 1.1, -0.9, -1, 1 }, { 0.0, 0.6 },
               { 0.8, -0.2, -0.5 } },
               { { 0.5, -0.1, -1.0, 1 },
               { 0, 0.4 }, { 0.8, 0.2, 0.4 } },
             { { 1, -1, 1, 1 }, { 0.0, 0.8 },
               { 0.8, -0.2, -0.5 } }
            }
           };
  object = parser.getObject();
  ASSERT_EQ(result.size(), object.size());
  for (size_t i = 0; i < result.size(); i++) {
    ASSERT_EQ(result[i].size(), object[i].size());
  }
}
