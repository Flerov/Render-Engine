// Copyright 2022, University of Freiburg
// Author: Joel Stanciu

#ifndef RASTERIZERMANAGER_H_
#define RASTERIZERMANAGER_H_

#include "Rasterizer.h"
#include "ObjectManager.h"
#include "Parser.h"
#include <string>
#include <vector>

// Initialized the object by parsing the given .obj file
// In this function setting can be changed.
// Transform: Rotation axis
// Light: Light position
// Translate: Translates
// Scale: scales
ObjectManager initObject(std::string filename) {
  Parser parser;
  parser.parsefile(filename);
  std::vector<std::vector<std::vector<std::vector<float>>>> object_ =
    parser.getObject();
  ObjectManager object(object_);

  std::vector<float> lightpos   = { 1, 5, 5, 0 };
  // Die Achsen bitte nur einzelnt angeben
  // oder ansonsten den angle in RendererMain.cpp zu radians convertieren
  std::vector<float> transform1 = { 1, 0, 0, 0 };
  // std::vector<float> transform2 = { 0, 1, 0, 0 };
  std::vector<float> transform3 = { 0, 0, 1, 0 };
  // std::vector<float> transform4 = { 0, 0, 0, 1 };
  std::vector<float> translate  = { 0, 1, 0 };
  // std::vector<float> scale      = { 0.1, -0.1, 0.1 }; // für dog.obj
  std::vector<float> scale      = { 0.5, -0.5, 0.5 };
  object.addLight(lightpos);
  object.addTransform(transform1);
  // object.addTransform(transform2);
  object.addTransform(transform3);
  // object.addTransform(transform4);
  // object.addTranslate(translate);
  object.addScale(scale);
  return object;
}

#endif  // RASTERIZERMANAGER_H_
