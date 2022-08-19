# Render-Engine
Compute a triangulated Model (from Blender) into 3D-Projected Space on Terminal

.obj objects are best exported from Blender.
This only works if you add 'Triangulate' as a modifier.
Then you have to remove all annotations from Blender.
(mostly the first 3 lines, and 2 lines when changing from 'vt','vn' or 'vn','f', i.e. texture to normal, normal to face).

Usage: ./RendererMain filename
The following files are available
'cube.obj' - standard cube from Blender
'monkey.obj' - standard monkey from Blender
'ring.obj' - ring (in my opinion the coolest, because of the depth effect)
'dog.obj' - dog
'car.obj' - car
More models you can create yourself :D ... or download them from the internet and adapt them as described above.
The file can then also contain information about several objects, so it should also work with a scene of models.
But then customising becomes difficult, which is why I didn't test it (so try the last suggestion at your own risk^^)!

Adjustments in RasterizerManager.h:
* adjust rotation axes
* adjust light
* adjust scale (to enjoy the model dog.obj set the scale vector like this { 0.1, 0.1, 0.1 } :) )
* adjust translates (here the points are normalized, so use only values between 0-1 :) )
* The colours can also be adjusted, the shading is then automatic to the given R/G/B values.
  in the constructor of the file Rasterizer.cpp :)
