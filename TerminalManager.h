// Copyright 2022, University of Freiburg
// Author: Joel Stanciu

#ifndef TERMINALMANAGER_H_
#define TERMINALMANAGER_H_

#include <chrono>
#include <thread>
#include <ncurses.h>
#include <utility>
#include <vector>
#include "ObjectManager.h"
#include "RasterizerManager.h"
#include "Rasterizer.h"
#include "Matrix.h"
#include "Camera.h"

// Initialize the Terminal
void initTerminal() {
  initscr();
  raw();
  noecho();
  curs_set(0);
  cbreak();
  start_color();
}

// calculate and run the objects
void runTerminal(ObjectManager object) {
  // Initialize camera
  Camera camera;
  // Initialize rasterizer
  Rasterizer raster(COLS, LINES, &object);
  // set the starting angle
  float zoom = 0;
  // sets important matrixes to perform calculation based on camera
  Matrix MVPMatrix(4);
  Matrix finalMatrix(4);
  Matrix m_Transform(4);
  // placeolders which get filled with data in the loop
  std::vector<float> v_A;
  std::vector<float> v_B;
  std::vector<float> v_C;
  std::vector<std::vector<float>> fmv;
  std::vector<std::vector<float>> transforms = object.getVectorTransforms();
  std::vector<std::vector<float>> scales = object.getVectorScales();
  std::vector<std::vector<float>> translates = object.getVectorTranslates();

  // define the settings for the camera
  camera.setProjection(1.31f, LINES / (COLS * 2), .2f, 400.f);
  //camera.setProjection(60.0f, LINES / (COLS * 2), 0.1f, 1000.0f);
  // calculate the view matrix, based on the camera settings
  camera.setViewMatrix();
  MVPMatrix = camera.getViewMatrix();

  // target fps: 30=33.33 | 60=16.67
  const double targetFrameTime = 20.33; // 16.67;
  //const double targetFrameTime = 16.67;
  // set the desired rotation for the camera
  // dirty temporary config reader for quick adjustments
  std::vector<float> camRotation = { 0, 0, 0 };
  camRotation[0] += 0.03;
  camRotation[1] += 0.08;
  camRotation[2] += 0.03;
  //
  while (true) {
    auto frameStart = std::chrono::high_resolution_clock::now();
    zoom = 0.2;
    camera.setRotation(camRotation);
    camera.setViewMatrix();
    MVPMatrix = camera.getViewMatrix();
    // iterate over all transforms and apply them to the rotation matrix
    for (auto curr : transforms) {
      m_Transform.rotate(curr, zoom);
    }
    // iterate over all translates and apply them to the rotation matrix
    for (auto curr : translates) {
      m_Transform.translate(curr);
    }
    // calculate the final matrix by multiplication
    finalMatrix = m_Transform * MVPMatrix;
    // iterate over all scales and apply them to the finalmatrix
    for (auto curr : scales) {
      finalMatrix.scale(curr);
    }
    fmv = finalMatrix.getAsVector();
    // apply calculations to the object in the last attributes field
    object.setMatrixRotation(m_Transform.getAsVector());
    object.setMatrixFinal(fmv);
    // itterate over all attributes (except the last one)
    // apply calculus to all vertexes in all three block of an attribute
    // based on the final matrix, in vector list representation
    // and feed it to the rasterizer to apply rotation and camera view
    for (size_t i = 0; i < object.size()-1; i++) {
      v_A = std::move(Matrix::transformVertex(object[i][0][0], fmv));
      v_B = std::move(Matrix::transformVertex(object[i][1][0], fmv));
      v_C = std::move(Matrix::transformVertex(object[i][2][0], fmv));
      raster.run(i, v_A, v_B, v_C);
    }
    // print the calculated object
    raster.print();
    refresh();
    erase();
    
    auto frameEnd = std::chrono::high_resolution_clock::now();
    auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart).count();
    if (frameTime < targetFrameTime) {
      std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(targetFrameTime - frameTime)));
    }
    m_Transform.reset();
    raster.clearFrames();
  }
  getch();
  clear();
  endwin();
}

#endif  // TERMINALMANAGER_H_
