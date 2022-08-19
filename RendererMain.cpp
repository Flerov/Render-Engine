// Copyright 2022, University of Freiburg
// Author: Joel Stanciu

#include "TerminalManager.h"
#include "RasterizerManager.h"
#include "ObjectManager.h"
#include <iostream>
#include <vector>
#include <string>

// Main function which calls the parses and runs the programm
int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Usage: ./RendererMain [file]\n" << std::endl;
    return 0;
  }
  initTerminal();
  std::string filename = argv[1];
  ObjectManager object = initObject(filename);
  runTerminal(object);
}
