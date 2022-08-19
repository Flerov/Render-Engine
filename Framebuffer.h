// Copyright 2022, University of Freiburg
// Author: Joel Stanciu (joelstanciu@outlook.de)

#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_

#include <cstddef>
#include <climits>
#include <cfloat>
#include <vector>

#include <utility>

/*
  This class represents a data structure which contains
  important information about the a pixels 2D Space, in the Terminal,
  which are contained inside of a 3D calculated Object
  
*/
class Framebuffer {
 public:
// ____________________________________________________________________________
// Constructor
  Framebuffer(size_t width, size_t height);
// ____________________________________________________________________________
// Destructor
  ~Framebuffer();
// ____________________________________________________________________________
// Initializes a Frame into the data structure, containing its correspondend
// depth and color value. A new Frame gets only placed inside of the
// data structure when its depth is greater then the previus/standard frame
// inside of this structure. By this the impression of 3Dimensionality
// is being produced while constantly iterating over all pixels without
// destroying relevant information on the depth
  void initFrame(size_t pX, size_t pY, float depth, size_t color);
// ____________________________________________________________________________
// Getter for the Depth value at the given x and y Point on the screen
  float getDepth(size_t pX, size_t pY);
// ____________________________________________________________________________
// Getter for the Color value at the given x and y Point on the screen
  size_t getColor(size_t pX, size_t pY);
// ____________________________________________________________________________
// Resets the data structure to its standard value
// By that each depth value will be set to FLOAT_MAX
// and each color value will be set to INT_MAX
  void reset();
// ____________________________________________________________________________
// Getter for the Width representing a dimension of the size of the data
// structure. Most likely the Width of the Terminal
  size_t getWidth() {
    return width_;
  }
// ____________________________________________________________________________
// Getter for the Height representing a demnsion of the size of the data
// strucutre. Most likely the Height of the Teriminal
  size_t getHeight() {
    return height_;
  }
// ____________________________________________________________________________
 private:
  size_t width_;
  size_t height_;
  std::vector<std::vector<float>> depth_;
  std::vector<std::vector<size_t>> color_;
  std::vector<std::vector<float>> depth_uninitialized_;
  std::vector<std::vector<size_t>> color_uninitialized_;
};

#endif  // FRAMEBUFFER_H_
