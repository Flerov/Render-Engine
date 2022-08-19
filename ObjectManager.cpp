// Copyright 2022, University of Freiburg
// Author: Joel Stanciu

#include <vector>
#include "./ObjectManager.h"

// ____________________________________________________________________________
ObjectManager::ObjectManager(
  std::vector<std::vector<std::vector<std::vector<float>>>>& object) {
  std::vector<std::vector<std::vector<float>>> attributes;
  std::vector<std::vector<float>> rotation_matrix_placeholder;
  std::vector<std::vector<float>> final_matrix_placeholder;
  std::vector<std::vector<float>> light_positions_placeholder;
  std::vector<std::vector<float>> transforms_placeholder;
  std::vector<std::vector<float>> translates_placeholder;
  std::vector<std::vector<float>> scales_placeholder;
  std::vector<std::vector<float>> mvp_matrix_placeholder;
  attributes.push_back(rotation_matrix_placeholder);
  attributes.push_back(final_matrix_placeholder);
  attributes.push_back(light_positions_placeholder);
  attributes.push_back(transforms_placeholder);
  attributes.push_back(translates_placeholder);
  attributes.push_back(scales_placeholder);
  attributes.push_back(mvp_matrix_placeholder);
  object.push_back(attributes);
  object_ = object;
}

// ____________________________________________________________________________
void ObjectManager::update(
  std::vector<std::vector<std::vector<std::vector<float>>>>& object) {
  object_ = object;
}
