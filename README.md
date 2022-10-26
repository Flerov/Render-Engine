# Render-Engine
Compute a triangulated Model (from Blender) into 3D-Projected Space on Terminal

## Compilation:
> make compile
## Run Tests:
Dependency for tests: Google/GTest. Requirements: GTest (Install Guide: https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/)
> sudo apt-get install libgtest-dev
> make test
## Usage:
> ./RendererMain filename

The following files are available
'cube.obj' - standard cube from Blender
'monkey.obj' - standard monkey from Blender
'ring.obj' - ring (in my opinion the coolest, because of the depth effect)
'dog.obj' - dog
'car.obj' - car

Adjustments in RasterizerManager.h:
* adjust rotation axes
* adjust light
* adjust scale (to enjoy the model dog.obj set the scale vector like this { 0.1, 0.1, 0.1 } :) )
* adjust translates (here the points are normalized, so use only values between 0-1 :) )
* The colours can also be adjusted, the shading is then automatic to the given R/G/B values.
  in the constructor of the file Rasterizer.cpp :)
