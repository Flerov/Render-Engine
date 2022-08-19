// Copyright 2022, University of Freiburg
// Author: Joel Stanciu (joelstanciu@outlook.de)

#ifndef PARSER_H_
#define PARSER_H_

#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>

/*
  This class parses an .obj file and their different line types
  Which are getting structured into a 4-Dimensional list
  of vectors. (Structure gets explained in ObjectManager,
  since that class should help with easier usage)
*/
class Parser {
 public:
// ____________________________________________________________________________
// Constructor
  Parser();
// ____________________________________________________________________________
// Destructor
  ~Parser();
// ____________________________________________________________________________
// Parses a given file name
  void parsefile(std::string& filename); // NOLINT
// ____________________________________________________________________________
// Parses a line which contains information about a Vertex
  std::vector<float> parseLineVertex(std::string& input); // NOLINT
// ____________________________________________________________________________
// Parses a line which contains information about a Texture
  std::vector<float> parseLineTexture(std::string& input); // NOLINT
// ____________________________________________________________________________
// Parses a line which contains information about a Normals
  std::vector<float> parseLineNormal(std::string& input); // NOLINT
// ____________________________________________________________________________
// Parses a line which contains information about a Face
  void parseLineFace(std::string& input, // NOLINT
                     std::vector<std::vector<float>>& points, // NOLINT
                     std::vector<std::vector<float>>& textures, // NOLINT
                     std::vector<std::vector<float>>& normals); // NOLINT
// ____________________________________________________________________________
// Getter which returns the private member object_
  std::vector<std::vector<std::vector<std::vector<float>>>> getObject() {
    return object_;
  }
// ____________________________________________________________________________
// Getter which returns the Count of Attributes inside of the
// private member object_
  size_t getobjectCount() { return objectCount_; }
// ____________________________________________________________________________
 private:
  std::vector<std::vector<std::vector<std::vector<float>>>> object_;
  size_t objectCount_;
};

#endif  // PARSER_H_
