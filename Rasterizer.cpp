// Copyright 2022, University of Freiburg
// Author: Joel Stanciu (joelstanciu@outlook.de)

#include <math.h>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include "./Rasterizer.h"
#include "Matrix.h"

static constexpr size_t systemColors = 16;

// ____________________________________________________________________________
Rasterizer::Rasterizer(
    size_t width, size_t height,
    ObjectManager* object) {
    width_ = width;
    height_ = height;
    object_ = object;
    framebuffer_ = new Framebuffer(width_, height_);
    for (int color = systemColors; color < COLORS; ++color) {
      int max = 900;
      int intensity = max * color / (COLORS - systemColors);
      intensity = MAX(500, intensity);
      // Hier farben anpassen. 'intensity' kann gerne a R/G/B gesetzt werden
      // Beispiele in den Kommentaren:
      init_color(color, 0, intensity, 843);
      // init_color(color, 50, 142, intensity);
      //init_color(color, 80, 60, 310);
      init_pair(color, color, 0);
    }
    init_pair(0, COLOR_MAGENTA, COLOR_BLUE);
}

// ____________________________________________________________________________
Rasterizer::~Rasterizer() {
    width_ = 0;
    height_ = 0;
}

// ____________________________________________________________________________
void Rasterizer::run(size_t index, std::vector<float>& vv_A,
                     std::vector<float>& vv_B, std::vector<float>& vv_C
                    ) {
  float minX, minY;
  float maxX, maxY;
  size_t width_h = width_ / 2;
  size_t height_h = height_ / 2;
  std::vector<float> v_A = {vv_A[0] * width_h + width_h,
                            vv_A[1] * height_h + height_h};
  std::vector<float> v_B = {vv_B[0] * width_h + width_h,
                            vv_B[1] * height_h + height_h};
  std::vector<float> v_C = {vv_C[0] * width_h + width_h,
                            vv_C[1] * height_h + height_h};

  minX = MAX(0, MIN(v_A[0], MIN(v_B[0], v_C[0])));
  minY = MAX(0, MIN(v_A[1], MIN(v_B[1], v_C[1])));
  maxX = MIN(width_, MAX(v_A[0], MAX(v_B[0], v_C[0])));
  maxY = MIN(height_, MAX(v_A[1], MAX(v_B[1], v_C[1])));

  std::vector<float> bCC;

  std::vector<std::vector<float>> transform = object_->getMatrixRotation();
  std::vector<std::vector<float>> finalmatrix = object_->getMatrixFinal();
  std::vector<float> lightpos = { 1, 5, 5, 0 };

  std::vector<float> worldlightpos = {
      lightpos[0] * width_h + width_h,
      lightpos[1] * height_h + height_h};
  mvprintw(worldlightpos[0], worldlightpos[1], "@");

  std::vector<float> normal = object_->getVectorNormal(index);
  normal = Matrix::vector_multiplication(transform, normal);

  float diffuse = normal[0] * lightpos[0] + normal[1] * lightpos[1] +
                  normal[2] * lightpos[2];
  if (diffuse < 0) diffuse = 0;

  for (size_t i = minX; i <= maxX; i++) {
    for (size_t k = minY; k <= maxY; k++) {
      bCC = barrycentricCoordinates(i, k, v_A, v_B, v_C);
      if (pointInTriangle(bCC)) {
        float depth = bCC[0] * vv_A[2] + bCC[1] * vv_B[2] + bCC[2] * vv_C[2];
        depth = 1 - depth;
        framebuffer_->initFrame(i, k, depth, static_cast<size_t>(diffuse*100));
      }
    }
  }
}

// ____________________________________________________________________________
std::vector<float> Rasterizer::barrycentricCoordinates(
    size_t pX, size_t pY, std::vector<float>& v_A, std::vector<float>& v_B,
    std::vector<float>& v_C) {
    std::vector<float> bCC = {0, 0, 0};
    bCC[0] = ((v_B[1] - v_C[1]) * (pX - v_C[0]) +
              (v_C[0] - v_B[0]) * (pY - v_C[1])) /
             ((v_B[1] - v_C[1]) * (v_A[0] - v_C[0]) +
              (v_C[0] - v_B[0]) * (v_A[1] - v_C[1]));
    bCC[1] = ((v_C[1] - v_A[1]) * (pX - v_C[0]) +
              (v_A[0] - v_C[0]) * (pY - v_C[1])) /
             ((v_B[1] - v_C[1]) * (v_A[0] - v_C[0]) +
              (v_C[0] - v_B[0]) * (v_A[1] - v_C[1]));
    bCC[2] = 1.0f - bCC[0] - bCC[1];
    return bCC;
}

// ____________________________________________________________________________
bool Rasterizer::pointInTriangle(std::vector<float>& bCC) {
    size_t one = (bCC[0] < -0.001);
    size_t two = (bCC[1] < -0.001);
    size_t three = (bCC[2] < -0.001);
    return ((one == two) && (one == three));
}

// ____________________________________________________________________________
void Rasterizer::clearFrames() {
  framebuffer_->reset();
}

// ____________________________________________________________________________
void Rasterizer::print() {
  size_t color = INT_MAX;
  for (size_t i = 0; i < static_cast<size_t>(LINES); i++) {
    for (size_t k = 0; k < static_cast<size_t>(COLS); k++) {
      color = framebuffer_->getColor(k, i);
      if (color != INT_MAX) {
        // calculate color code
        color = MIN(MAX(color, 16), 255);
        attron(COLOR_PAIR(color));
        if (color < 20) mvprintw(i, k, ".");
        if (color < 30) mvprintw(i, k, "-");
        if (color < 40) mvprintw(i, k, "+");
        if (color < 50) mvprintw(i, k, ":");
        if (color < 60) mvprintw(i, k, "%");
        if (color < 70) mvprintw(i, k, "#");
        if (color >= 70) mvprintw(i, k, "@");
        attroff(COLOR_PAIR(color));
      } else {
        continue;
      }
    }
  }
}
