# 3D objects generator
_Still in progress_ 

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

### Main object types that can be created:

1. Cube
- params (--a): size (default 50)

_--a option can be avoided and values can written immediately after type name_

2. CubeExt - cube made of component objects located on each face 
- component name used on each face (--c)
- component params (--p): _depends on used component_
- face params (--f): translation-x translation-y translation-z (default 0 0 0)

3. Thorus 
- params (--a): circle-amount ring-amount circle-radius circle-offset
- sinus params (--s): circle-step-x circle-amp-x circle-step-y circle-amp-y circle-step-z circle-amp-z ring-step-x ring-amp-x ring step-y ring-amp-y ring-step-z ring-amp-z

_--s contains value of double type_

4. Composite - currently the most flexible object that can be made of 6 different components, moved and rotated
- component name (--c0, --c1, --c2, --c3, --c4, --c5)
- component params (--p0, --p1, --p2, --p3, --p4, --p5): _depends on used component_
- translation and rotation (--f0, --f1, --f2, --f3, --f4, --f5): translation-x translation-y translation-z degree-x degree-y degree-z

_Value in f and p can be negative_

### Components which can be used in CubeExt and Composite:
1. Square
--p size (default: 50)
2. Rectangle
--p size-x size-y (default: 50 50)
3. Square with hole part1 (squareholepart1)
--p size1 size2 (default: 50 20)
4. Square with hole part2 (squareholepart2)
--p size1 size2 (default: 50 20)
5. Pyramid
--p size height (default: 50 20)
6. Taper
--p circle-amount circle-radius height (default: 3 50 50)
7. Cylinder made of squares (cylinder)
--p circle-amount cirlce-radius height (default: 3 50 50)
8. Cylinder made of triangles (cylindertriangles)
--p circle-amount cirlce-radius height (default: 3 50 50)

**Please look into run.sh file to see how examples are defined.**

![](example.png)
