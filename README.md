# 3D objects generator
_Still in progress_ 

I started this project to have 3d objects for my Amiga 500 vector graphics renderer.

There are two apps:

- generator
- viewer 

run.sh is example script which generates several objects and show them in the viewer

Needed to build these libraries (in the brackets there are minimal versions I've tested):

- SDL2 (2.0.18)
- SDL2 image (2.8.2)
- SDL2 ttf (2.0.18)
- boost (1.71)
- cmake (3.16)
- g++ (C++17)

## Main object types that can be created:

1. Cube
- params (--a): size (default 50)

2. CubeExt - cube made of component objects located on each face 
- component name used on each face (--c)
- component params (--p), _depends on used component_
: size (default 50), rest of params depends on used components

_--a option can be avoided and values can written immediately after type name)_

3. Thorus 
- params (--a): circle amount, ring amount, circle radius, circle offset
- sinus params (--s): circle step x, circle amp x, circle step y, circle amp y, circle step z, circle amp z, ring step x, ring amp x, ring step y, ring amp y, ring step z, ring amp z

4. Composite - currently the most flexible object that can be made of 6 different components, moved and rotated
- component name (--c0, --c1, --c2, --c3, --c4, --c5)
- component params (--p0, --p1, --p2, --p3, --p4, --p5), _depends on used component_
- translation and rotation (--f0, --f1, --f2, --f3, --f4, --f5)

## Components are to be used to build main object (CubeExt or Composite):
1. Square
2. Rectangle
3. Square with hole part1 (squareholepart1)
4. Square with hole part2 (squareholepart2)
5. Pyramid
6. Taper
7. Cylinder made of squares (cylinder)
8. Cylinder made of triangles (cylindertriangles)

**Please look into run.sh file to see how examples are defined.**

![](example.png)
