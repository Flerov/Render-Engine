// Copyright 2022, University of Freiburg
// Author: Joel Stanciu

#include <gtest/gtest.h>
#include <climits>
#include "Framebuffer.h"

// Test Constructor
TEST(Framebuffer, Constructor) {
  Framebuffer buffer(10, 54);
  ASSERT_EQ(10, buffer.getWidth());
  ASSERT_EQ(54, buffer.getHeight());
}

// Test function initFrame
TEST(Framebuffer, Frame) {
  Framebuffer buffer(1, 1);
  buffer.initFrame(0, 0, -5, 250);
  ASSERT_EQ(FLT_MAX, buffer.getDepth(0, 1));
  ASSERT_EQ(INT_MAX, buffer.getColor(0, 1));
  ASSERT_EQ(-5, buffer.getDepth(0, 0));
  ASSERT_EQ(250, buffer.getColor(0, 0));
  buffer.initFrame(0, 0, 10, 250);
  ASSERT_EQ(-5, buffer.getDepth(0, 0));
  ASSERT_EQ(250, buffer.getColor(0, 0));
  buffer.initFrame(0, 0, -50, 30);
  ASSERT_EQ(-50, buffer.getDepth(0, 0));
  ASSERT_EQ(30, buffer.getColor(0, 0));
  buffer.initFrame(5, 5, -5, 250);
  ASSERT_EQ(FLT_MAX, buffer.getDepth(5, 5));
  ASSERT_EQ(INT_MAX, buffer.getColor(5, 5));
}

// Test function reset
TEST(Framebuffer, Reset) {
  size_t width = 100;
  size_t height = 100;
  Framebuffer buffer(width, height);
  size_t depth = 0;
  size_t color = 0;
  for (size_t i = 0; i < width; i++) {
    for (size_t k = 0; k < height; k++) {
      buffer.initFrame(i, k, depth, color);
      depth++;
      color++;
    }
  }
  buffer.reset();
  for (size_t i = 0; i < width; i++) {
    for (size_t k = 0; k < height; k++) {
      ASSERT_EQ(FLT_MAX, buffer.getDepth(i, k));
      ASSERT_EQ(INT_MAX, buffer.getColor(i, k));
    }
  }
}
