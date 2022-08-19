// Copyright 2022, University of Freiburg
// Author: Joel Stanciu

#include <vector>
#include <string>
#include "./Parser.h"

// ____________________________________________________________________________
Parser::Parser() {
  objectCount_ = 0;
}

// ____________________________________________________________________________
Parser::~Parser() {
  objectCount_ = 0;
}

// ____________________________________________________________________________
std::vector<float> Parser::parseLineVertex(std::string& input) {
  size_t pos1 = input.find(' ');
  size_t pos2 = input.find(' ', pos1 + 1);
  size_t pos3 = input.find(' ', pos2 + 1);
  float point1 = std::atof(input.data() + pos1);
  float point2 = std::atof(input.data() + pos2);
  float point3 = std::atof(input.data() + pos3);
  std::vector<float> points = { point1, point2, point3, 1 };
  return points;
}

// ____________________________________________________________________________
std::vector<float> Parser::parseLineTexture(std::string& input) {
  size_t pos1 = input.find(' ');
  size_t pos2 = input.find(' ', pos1 + 1);
  float point1 = std::atof(input.data() + pos1);
  float point2 = std::atof(input.data() + pos2);
  std::vector<float> points = { point1, point2 };
  return points;
}

// ____________________________________________________________________________
std::vector<float> Parser::parseLineNormal(std::string& input) {
  size_t pos1 = input.find(' ');
  size_t pos2 = input.find(' ', pos1 + 1);
  size_t pos3 = input.find(' ', pos2 + 1);
  float point1 = std::atof(input.data() + pos1);
  float point2 = std::atof(input.data() + pos2);
  float point3 = std::atof(input.data() + pos3);
  std::vector<float> points = { point1, point2, point3 };
  return points;
}

// ____________________________________________________________________________
void Parser::parseLineFace(std::string& input,
                           std::vector<std::vector<float>>& points,
                           std::vector<std::vector<float>>& textures,
                           std::vector<std::vector<float>>& normals) {
  size_t pos11 = input.find(' ');
  size_t pos12 = input.find('/', pos11 + 1);
  size_t pos13 = input.find('/', pos12 + 1);
  size_t pos21 = input.find(' ', pos13 + 1);
  size_t pos22 = input.find('/', pos21 + 1);
  size_t pos23 = input.find('/', pos22 + 1);
  size_t pos31 = input.find(' ', pos23 + 1);
  size_t pos32 = input.find('/', pos31 + 1);
  size_t pos33 = input.find('/', pos32 + 1);

  size_t index00 = (size_t)std::atof(input.data() + pos11);
  size_t index01 = (size_t)std::atof(input.data() + pos12 + 1);
  size_t index02 = (size_t)std::atof(input.data() + pos13 + 1);
  size_t index10 = (size_t)std::atof(input.data() + pos21);
  size_t index11 = (size_t)std::atof(input.data() + pos22 + 1);
  size_t index12 = (size_t)std::atof(input.data() + pos23 + 1);
  size_t index20 = (size_t)std::atof(input.data() + pos31);
  size_t index21 = (size_t)std::atof(input.data() + pos32 + 1);
  size_t index22 = (size_t)std::atof(input.data() + pos33 + 1);

  std::vector<std::vector<float>> component0 = {
                                                points[index00-1],
                                                textures[index01-1],
                                                normals[index02-1]
                                               };
  std::vector<std::vector<float>> component1 = {
                                                points[index10-1],
                                                textures[index11-1],
                                                normals[index12-1]
                                               };
  std::vector<std::vector<float>> component2 = {
                                                points[index20-1],
                                                textures[index21-1],
                                                normals[index22-1]
                                               };
  std::vector<std::vector<std::vector<float>>> polygon = {
                                                          component0,
                                                          component1,
                                                          component2
                                                         };
  object_.push_back(polygon);
  objectCount_++;
}

// ____________________________________________________________________________
void Parser::parsefile(std::string& filename) {
  std::ifstream pointsFile(filename);
  std::string line;
  std::string vt = "vt";
  std::string vn = "vn";
  size_t found;
  std::vector<std::vector<float>> points;
  std::vector<std::vector<float>> textures;
  std::vector<std::vector<float>> normals;
  while (std::getline(pointsFile, line)) {
    found = line.find('t');
    if (found != std::string::npos) {
      textures.push_back(parseLineTexture(line));
      continue;
    }
    found = line.find('n');
    if (found != std::string::npos) {
      normals.push_back(parseLineNormal(line));
      continue;
    }
    found = line.find('f');
    if (found != std::string::npos) {
      parseLineFace(line, points, textures, normals);
      continue;
    }
    found = line.find('v');
    if (found != std::string::npos) {
      points.push_back(parseLineVertex(line));
      continue;
    }
  }
}

