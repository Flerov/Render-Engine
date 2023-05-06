# Render-Engine
Car                        |  Car
:-------------------------:|:-------------------------:
<img src="https://github.com/Flerov/Render-Engine/blob/images/Car1.png" height="400" width="400" > | <img src="https://github.com/Flerov/Render-Engine/blob/images/Car2.png" height="400" width="400" >
Car                        |  Car
:-------------------------:|:-------------------------:
<img src="https://github.com/Flerov/Render-Engine/blob/images/Car3.png" height="400" width="400" > | <img src="https://github.com/Flerov/Render-Engine/blob/images/Car4.png" height="400" width="400" >
Monkey                     |  Monkey
:-------------------------:|:-------------------------:
<img src="https://github.com/Flerov/Render-Engine/blob/images/Ape1.png" height="400" width="400" > | <img src="https://github.com/Flerov/Render-Engine/blob/images/Ape2.png" height="400" width="400" >
Monkey                     |  Ring
:-------------------------:|:-------------------------:
<img src="https://github.com/Flerov/Render-Engine/blob/images/Ape3.png" height="400" width="400" > | <img src="https://github.com/Flerov/Render-Engine/blob/images/Ring1.png" height="400" width="400" >
Ring                       |  Ring
:-------------------------:|:-------------------------:
<img src="https://github.com/Flerov/Render-Engine/blob/images/Ring2.png" height="400" width="400" > | <img src="https://github.com/Flerov/Render-Engine/blob/images/Ring3.png" height="400" width="400" >
<img src="https://github.com/Flerov/Render-Engine/blob/images/Ring4.png" height="400" width="400" >

Compute a triangulated Model (from Blender) into 3D-Projected Space on Terminal
Dependencies: ignore the test and you only need the 'ncruses' library. With the tests you'll need GTest on top. Have fun
## Compilation:
> make compile
## Run Tests:
Dependency for tests: Google/GTest. Requirements: GTest (Install Guide: https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/)
> sudo apt-get install libgtest-dev | and then to run the tests: 
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
