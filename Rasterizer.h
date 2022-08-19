// Copyright 2022, University of Freiburg
// Author: Joel Stanciu (joelstanciu@outlook.de)

#ifndef RASTERIZER_H_
#define RASTERIZER_H_

#include <ncurses.h>
#include <climits>
#include <vector>
#include "Framebuffer.h"
#include "ObjectManager.h"

#define MAX(a, b) (((a) > (b))? (a) : (b))
#define MIN(a, b) (((a) < (b))? (a) : (b))


class Rasterizer {
 public:
// ____________________________________________________________________________
// Constructor which initializer Frambuffer by the given screen dimensions and
// uses a object represented by ObjectManager to calculate the object
  Rasterizer(size_t width, size_t height,
  ObjectManager* object);
// ____________________________________________________________________________
// Destructor
  ~Rasterizer();
// ____________________________________________________________________________
// Performs calculations to initialize the framebuffer with all the data
// representing points inside of the segment of the object, represented
// by three vectors
  void run(size_t index, std::vector<float>& a, // NOLINT
           std::vector<float>& b, // NOLINT
           std::vector<float>& c); // NOLINT
// ____________________________________________________________________________
// Returns the barrycentric coordinates of two points, based on three vectors
  std::vector<float> barrycentricCoordinates(size_t pX, size_t pY,
     std::vector<float>& v_A, std::vector<float>& v_B, // NOLINT
     std::vector<float>& v_C); // NOLINT
// ____________________________________________________________________________
// Returns whether the point is inside of the triangle
  bool pointInTriangle(std::vector<float>& bCC); // NOLINT
// ____________________________________________________________________________
// Calls the reset function for the framebuffer
  void clearFrames();
// ____________________________________________________________________________
// Prints the data of the framebuffer to the screen, and calculates the
// corresponding color to a pixel, for each pixel on the screen
  void print();
// ____________________________________________________________________________
// Getter which returns the private member framebuffer_ (only used in tests)
  Framebuffer* getFramebuffer() {
    return framebuffer_;
  }
// ____________________________________________________________________________
// Getter which returns the private member object_
  ObjectManager* getObject() {
    return object_;
  }
// ____________________________________________________________________________
 private:
  size_t width_;
  size_t height_;
  ObjectManager* object_;
  Framebuffer* framebuffer_;
};

#endif  // RASTERIZER_H_

