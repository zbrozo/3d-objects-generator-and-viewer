# 3D objects generator

I started this project to have 3d objects for my Amiga 500 vector graphics renderer.

There are two apps:

- generator
- viewer 

run.sh is example script which generates several objects and show them in the viewer

Needed to build these libraries (in the brackets there are versions I've tested):

- SDL2 (2.0.18)
- SDL2 image (2.8.2)
- SDL2 ttf (2.0.18)
- boost (1.71)
- cmake (3.16)
- g++ (C++17)

## Generator usage manual

Objects can be created by defining main object type (using --n option) and component objects to process. 
Default one is "composite" object. Please look below for details.

Please look into run.sh file to see how they are defined.

### Main object types that can be created:

1. Cube
- params: size

2. CubeExt - cube made of component objects located on each face 
- component name used on each face (--c)
- component params (--p): _depends on used component_
- face params (--t): translation-x translation-y translation-z (default 0 0 0)

3. Thorus 
- params: circle-amount ring-amount circle-radius circle-offset [circle-amount2] [circle-rotation-start-degree] [circle-rotation-step-degree]

- sinus params (--s): [circle-step-x] [circle-amp-x] [circle-step-y] [circle-amp-y] [circle-step-z] [circle-amp-z] [ring-step-x] [ring-amp-x] [ring step-y] [ring-amp-y] [ring-step-z] [ring-amp-z]

- prefer triangle faces over rectanges or other kind (--3): no values

_--s contains value of double type_

4. Composite - currently the most flexible object that can be made of 6 different components, moved and rotated
- component name (--c0, --c1, --c2, --c3, --c4, --c5): _if component is not defined in this app then an object file with given name is searched_
- component creation params (--p0, --p1, --p2, --p3, --p4, --p5): _depends on created component, see --p in components
- component transformation params (--t0, --t1, --t2, --t3, --t4, --t5): available params are: 
    - rotation degrees (rx, ry, rz)
    - translation (tx, ty, tz)

_Values in p and t can be negative_

5. Tetrahedron
- params: circle-radius height

6. RegularTetrahedron
- params: circle-radius

7. FractalTetrahedron 
- params: circle-radius

### Components which can be used in CubeExt and Composite:
1. Square, name: square
--p side-length

2. Rectangle, name: rectangle
--p side1-length side2-length

3. Trapeze, name: trapeze
--p top-length bottom-length height

4. Pyramid, name: pyramid
--p side-length height

5. Cone, name: cone
--p amount radius height

6. Cylinder made of squares, name: cylinder
--p circle-amount circle-radius height

7. Cylinder made of triangles, name: triangledcylinder
--p circle-amount cirlce-radius height

8. Star, name: star
--p amount radius

### Build on MS Windows
Install MSYS2, use MSYS2 UCRT64 shell:
```
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain 
pacman -S ucrt64/mingw-w64-ucrt-x86_64-cmake
pacman -S ucrt64/mingw-w64-ucrt-x86_64-SDL2
pacman -S ucrt64/mingw-w64-ucrt-x86_64-SDL2_image
pacman -S ucrt64/mingw-w64-ucrt-x86_64-SDL2_ttf
pacman -S ucrt64/mingw-w64-ucrt-x86_64-boost
```

![](example.png)
