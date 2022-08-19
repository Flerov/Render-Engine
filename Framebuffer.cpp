// Copyright 2022, University of Freiburg
// Author: Joel Stanciu (joelstanciu@outlook.de)

#include <vector>
#include "./Framebuffer.h"

// ____________________________________________________________________________
Framebuffer::Framebuffer(size_t width, size_t height) {
  width_ = width;
  height_ = height;
  for (size_t i = 0; i <= width_; i++) {
    std::vector<float> tmp_depth;
    std::vector<size_t> tmp_color;
    depth_uninitialized_.push_back(tmp_depth);
    color_uninitialized_.push_back(tmp_color);
    for (size_t k = 0; k <= height_; k++) {
      depth_uninitialized_[i].push_back(FLT_MAX);
      color_uninitialized_[i].push_back(INT_MAX);
    }
  }
  depth_ = depth_uninitialized_;
  color_ = color_uninitialized_;
}

// ____________________________________________________________________________
void Framebuffer::reset() {
  depth_ = depth_uninitialized_;
  color_ = color_uninitialized_;
}

// ____________________________________________________________________________
Framebuffer::~Framebuffer() {
}

// ____________________________________________________________________________
void Framebuffer::initFrame(size_t pX, size_t pY, float depth, size_t color) {
  if (pX > width_ || pY > height_) {
    return;
  }
  if (depth < depth_[pX][pY]) {
    color_[pX][pY] = color;
    depth_[pX][pY] = depth;
  }
}

// ____________________________________________________________________________
float Framebuffer::getDepth(size_t pX, size_t pY) {
  if (pX > width_ || pY > height_) {
    return FLT_MAX;
  }
  return depth_[pX][pY];
}

// ____________________________________________________________________________
size_t Framebuffer::getColor(size_t pX, size_t pY) {
  if (pX > width_ || pY > height_) {
    return INT_MAX;
  }
  return color_[pX][pY];
}

