// Copyright 2022, University of Freiburg
// Author: Joel Stanciu

#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include <vector>
#include <utility>

/*
  Note: A representation of the structure as a high dimensional list of vectors
  Is provided at the end of this Header File.

  This class serves for easier use of a parsed .obj file
  It containes structured information about all
  faces parsed from a .obj file (Parser in Parser.h, Parser.cpp)
  And their corresponding vertices, texture and normal values
  By this each element in the first dimension of the underlying list strucutre
  represents an attribute (first dimension).
  In most cases each attribute represents a face, which is made up of
  three blocks of further data.

  Each Block (second dimension)

  (in .obj file this looks like the follow 'f a/b/c d/e/f g/h/i',
  where 'a/b/c' is the first block, 'd/e/f' the second block and
  'g/h/i' the third block. Further, the first entry of a block
  describes a vertex, the second entry of a block descibes a texture,
  the third entry of a block describes a normal, this is given by the strucutre
  of a .obj file)

  is made up of three lists (in the first block
  representing 'a', 'b', 'c' in its own list), each of these entries contains
  information about a vector (third dimension). (The fourth dimension
  contains the information of these vector, for example in 'a' the fourth
  dimension would contain, at position [0] its x coordinate,
  at position [1] its y coordinate,
  at position [2] its z coordinate.
  
  Further at the end of this object the last attribute contains information
  about necessery data, like the vector lists describing all transforms,
  light, scales, translates, the rotation matrix calculated in 
  the current itteration, the final matrix calculated in the current iteration

  Because of this complex data strucutre this class prvides functions to
  access the necessary data for extending the complexity for the calculation
  of the world to add and modify the last attribute.
*/

class ObjectManager {
 public:
// ____________________________________________________________________________
// Constructor
  ObjectManager(
    std::vector<std::vector<std::vector<std::vector<float>>>>& object);
// ____________________________________________________________________________
// Destructor
  ~ObjectManager() {  }
// ____________________________________________________________________________
// Operator overload to return a three dimensional list of vectors at
// the given index
  std::vector<std::vector<std::vector<float>>>& operator[](size_t index) {
    return object_[index];
  }
// ____________________________________________________________________________
// Operator overload to assign a given object represented by a vector list
// to the current object
  void operator=(
  std::vector<std::vector<std::vector<std::vector<float>>>>& object) {
    object_ = std::move(object);
  }
// ____________________________________________________________________________
// Updates the current object with data that changed
  void update(
  std::vector<std::vector<std::vector<std::vector<float>>>>& object);
// ____________________________________________________________________________
// Getter which returns the Rotation Matrix from the last attributes field
  std::vector<std::vector<float>>& getMatrixRotation() {
    return object_[object_.size()-1][0];
  }
// ____________________________________________________________________________
// return the size of the private member object_
  size_t size() {
    return object_.size();
  }
// ____________________________________________________________________________
// Getter which return the Final Matrix from the last attributes field
  std::vector<std::vector<float>>& getMatrixFinal() {
    return object_[object_.size()-1][1];
  }
// ____________________________________________________________________________
// Getter which returns the Light from the last attrbiutes field (l .a .f)
  std::vector<float>& getLight() {
    return object_[object_.size()-1][2][0];
  }
// ____________________________________________________________________________
// Getter which returns the  list of Transforms (l .a .f)
  std::vector<std::vector<float>>& getVectorTransforms() {
    return object_[object_.size()-1][3];
  }
// ____________________________________________________________________________
// Getter which returns the list of Normas (l .a .f)
  std::vector<float>& getVectorNormal(size_t index) {
    return object_[index][0][2];
  }
// ____________________________________________________________________________
// Getter which returns the list of Scales (l .a .f)
  std::vector<std::vector<float>>& getVectorScales() {
    return object_[object_.size()-1][4];
  }
// ____________________________________________________________________________
// Getter which returns the list of Translates (l .a .f)
  std::vector<std::vector<float>>& getVectorTranslates() {
    return object_[object_.size()-1][5];
  }
// ____________________________________________________________________________
// Getter which returns the MVP Matrix (l .a .f)
  std::vector<std::vector<float>>& getMatrixMvp() {
    return object_[object_.size()-1][6];
  }
// ____________________________________________________________________________
// Adds a light vector (l .a .f)
  size_t addLight(std::vector<float>& light) { // NOLINT
    object_[object_.size()-1][2].push_back(light);
    return object_[object_.size()-1][2].size()-1;
  }
// ____________________________________________________________________________
// Adds a transform vector (l .a .f)
  size_t addTransform(std::vector<float>& transform) { // NOLINT
    object_[object_.size()-1][3].push_back(transform);
    return object_[object_.size()-1][3].size()-1;
  }
// ____________________________________________________________________________
// Adds a scaler vector (l .a .f)
  size_t addScale(std::vector<float>& scale) { // NOLINT
    object_[object_.size()-1][4].push_back(scale);
    return object_[object_.size()-1][4].size()-1;
  }
// ____________________________________________________________________________
// Adds a translate vector (l .a .f)
  size_t addTranslate(std::vector<float>& translate) { // NOLINT
    object_[object_.size()-1][5].push_back(translate);
    return object_[object_.size()-1][5].size()-1;
  }
// ____________________________________________________________________________
// Removes a transform at from the given position (l .a .f)
  void removeTransform(size_t pos) {
    if (pos >= object_[object_.size()-1][3].size()) {
      return;
    }
    object_[object_.size()-1][3].erase(
      object_[object_.size()-1][3].begin()+pos);
  }
// ____________________________________________________________________________
// Replaces the light vector at the given position
  void setLight(
     std::vector<float>& light, size_t pos) { // NOLINT
    if (pos >= object_[object_.size()-1][2].size()) {
      return;
    }
    object_[object_.size()-1][2][pos] = light;
  }
// ____________________________________________________________________________
// Replaces the transform vector at the given position
  void setTransform(
     std::vector<float>& transform, size_t pos) { // NOLINT
    if (pos >= object_[object_.size()-1][3].size()) {
      return;
    }
    object_[object_.size()-1][3][pos] = transform;
  }
// ____________________________________________________________________________
// Sets/Replaces the final matrix
  void setMatrixFinal(
     std::vector<std::vector<float>>& finalmatrix) { // NOLINT
    object_[object_.size()-1][1] = finalmatrix;
  }
// ____________________________________________________________________________
// Sets/Replaces the rotation matrix
  void setMatrixRotation(
     std::vector<std::vector<float>>& rotationmatrix) { // NOLINT
    object_[object_.size()-1][0] = rotationmatrix;
  }
// ____________________________________________________________________________
// Sets/Replaces the mvp matrix
  void setMatrixMvp(std::vector<std::vector<float>>& mvp) { // NOLINT
    object_[object_.size()-1][6] = mvp;
  }
// ____________________________________________________________________________
 private:
  // The list object_ is made up of attributes.
  // Each attribute is made up of data representing the attribute
  // Most data represanting a attriubute is the data to represent
  // the connection of Triangles, their texture coordinates and their
  // normals, which represent a face in a obj file.
  // Another attribute contains:
  // * data representing transform vectors
  // * data representing light position as vectors
  // * the calculated transformation matrix
  // * the calculated world matrix ('rotation matrix' * 'MVPMatrix')
  std::vector<std::vector<std::vector<std::vector<float>>>> object_;
  // Explenation of object_ filled with data described aboth :
  // [
  //   { (vectors), (textures), (normals) },
  //   { (v1,v2,v3), (t1, t2), (n1, n2, n3) },
  //   { (v1,v2,v3), (t1, t2), (n1, n2, n3) },
  //   { ((1.0, 5.3, 3.2), (2.1, 4.3), (-1.0, 0.0, 1.0) },
  //    ...
  //   { final matrix },
  //   { transform matrix },
  //   { transforms },
  //   { light position },
  // ]
};

#endif  // OBJECTMANAGER_H_
