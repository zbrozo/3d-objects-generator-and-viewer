cmake --build build

mkdir -p ./objects
mkdir -p ./objects_small

if [[ "$1" == "" ]]; then
    cd ./objects_small

    # small objects
    ../generator --n 0 --o cube1 --t cube 70
    ../generator --n 64 --o cube2 --t cube-ext --c SquareHolePart1 SquareHolePart2 --p 70 30 30 --f 0 0 70 30 30
    ../generator --n 64 --o cube3 --t cube-ext --c Pyramid --p 70 --f 0 0 70
    ../generator --n 64 --o cube4 --t cube-ext --c Pyramid --p 40 70 --f 0 0 40
    ../generator --o thorus1 --t thorus 4 3 
    ../generator --o thorus2 --t thorus 4 4
    ../generator --o thorus3 --t thorus 6 8 40 

    ../generator --n 60 --o thorus4 --t thorus 6 12 30 70 --s 0 0 3 15 2 15
    ../generator --n 60 --o thorus5 --t thorus 6 16 30 70 --s 0 0 4 15 4 15
    ../generator --3 --o thorus6 --t thorus 6 12 30 70 --s 0 0 3 10 2 10
    ../generator --3 --o thorus7 --t thorus 6 16 30 70 --s 0 0 4 10 4 10
    
    ../generator --3 --o thorus8 --t thorus 6 16 20 80 --s 0 0 0 0 0 0 0 0 16 10 16 10
    
    ../generator --o cone1 --t composite --c0 Cone --p0 3 50 50 --c1 Cone --p1 3 50 -50
    ../generator --o cone2 --t composite --c0 Cone --p0 6 50 50 --c1 Cone --p1 6 50 -50
    ../generator --o cone3 --t composite --c0 Cone --p0 3 50 50 --f0 0 0 0 0 0 0 0 0 0 --c1 Cone --p1 3 50 50 --f1 0 0 0 0 0 0 100 0 0
    ../generator --o tmp --t tetrahedron 80 70
    ../generator --o tetrahedron1 --t composite --c0 tmp --f0 0 0 -40
    ../generator --o tetrahedron2 --t regulartetrahedron 80
    ../generator --n 64 --o tetrahedron3 --t fractaltetrahedron 50
    
    ../generator --o composite1 --t composite --c0 Pyramid --p0 50 50 --f0 0 0 0 0 0 0 --c1 Pyramid --p1 50 50 --f1 0 0 0 0 180 0
    ../generator --o composite2 --t composite --c0 Pyramid --p0 50 50 --f0 0 0 20 0 0 0 --c1 Pyramid --p1 50 50 --f1 0 0 20 0 180 0 --c2 Rectangle --p2 20 50 --f2 0 0 50 0 90 0 --c3 Rectangle --p3 20 50 --f3 0 0 50 0 270 0 --c4 Rectangle --p4 50 20 --f4 0 0 50 90 0 0 --c5 Rectangle --p5 50 20 --f5 0 0 50 270 0 0
    ../generator --o composite3 --t composite --c0 Cone --p0 6 50 50 --f0 0 0 25 --c1 Cone --p1 6 50 -50 --f1 0 0 -25 --c2 Cylinder --p2 6 50 50 --f2 0 0 25
    ../generator --o composite4 --t composite --c0 Cone --p0 6 50 50 --f0 0 0 25 --c1 Cone --p1 6 50 -50 --f1 0 0 -25 0 0 30 --c2 CylinderTriangles --p2 6 50 50 --f2 0 0 25
    ../generator --o composite5 --t composite --c0 cube1 --f0 0 0 0 0 0 0 -100 0 0 --c1 cube1 --f1 0 0 0 0 0 0 100 0 0 --c2 cube1 --f2 0 0 0 0 0 0 0 -100 0 --c3 cube1 --f3 0 0 0 0 0 0 0 100 0
    ../generator --n 64 --o tmp --t cube 40
    ../generator --n 64 --o composite6 --t composite --c0 csign --p0 4 100 80 0 0 10 --f0 0 0 0 0 0 0 -10 0 0 --c1 csign --p1 4 100 80 0 0 10 --f1 0 0 0 0 180 0 10 0 0 --c2 csign --p2 4 100 80 0 0 10 --f2 0 0 0 0 90 0 0 0 10 --c3 csign --p3 4 100 80 0 0 10 --f3 0 0 0 0 -90 0 0 0 -10 --c4 tmp --f4 0 0 0 0 0 0 0 0 0
    ../generator --o composite7 --t composite --c0 csign --p0 5 80 50 0 0 20 --f0 0 0 0 0 0 0 10 0 0 --c1 csign --p1 5 80 50 0 0 20 --f1 0 0 0 90 180 0 10 0 0

#    ../generator --o square --t composite --c0 square --p0 50
    
    cd ..
    echo "Start viewer"
    ./viewer objects_small cube1 cube4 composite6 composite7 thorus4 thorus5 thorus6 thorus7 composite4 tetrahedron1 tetrahedron3
else
    cd ./objects

    # normal objects
    ../generator --v --o cube1 --t cube --a 100
    ../generator --v --o cube2 --t cube-ext --c SquareHolePart1 SquareHolePart2 --p 100 --f 0 0 100
    ../generator --v --o cube3 --t cube-ext --c Pyramid --p 100 --f 0 0 100
    ../generator --v --o thorus1 --t thorus 20 40 30 100
    ../generator --v --o thorus2 --t thorus 20 40 30 100 --s 0 0 6 10 0 0
    ../generator --v --o thorus3 --t thorus 20 20 30 100 --s 0 0 1 5 0 0 0.2 10 1.5 20 0.2 10
    ../generator --v --o taper1 --t composite --c0 Cone --p0 3 100 100 --c1 Cone --p1 3 100 -100
    ../generator --v --o taper2 --t composite --c0 Cone --p0 6 100 100 --c1 Cone --p1 6 100 -100
    ../generator --v --o composite1 --t composite --c0 Pyramid --p0 100 100 --f0 0 0 0 0 0 0 --c1 Pyramid --p1 100 100 --f1 0 0 0 0 180 0
    ../generator --v --o composite2 --t composite --c0 Pyramid --p0 100 100 --f0 0 0 20 0 0 0 --c1 Pyramid --p1 100 100 --f1 0 0 20 0 180 0 --c2 Rectangle --p2 20 100 --f2 0 0 100 0 90 0 --c3 Rectangle --p3 20 100 --f3 0 0 100 0 270 0 --c4 Rectangle --p4 100 20 --f4 0 0 100 90 0 0 --c5 Rectangle --p5 100 20 --f5 0 0 100 270 0 0
    ../generator --v --o composite3 --t composite --c0 Cone --p0 6 100 100 --f0 0 0 50 --c1 Cone --p1 6 100 -100 --f1 0 0 -50 --c2 Cylinder --p2 6 100 100 --f2 0 0 50
    ../generator --v --o composite4 --t composite --c0 Cone --p0 6 100 50 --f0 0 0 50 --c1 Cone --p1 6 100 -50 --f1 0 0 -50 0 0 30 --c2 CylinderTriangles --p2 6 100 100 --f2 0 0 50

    cd ..
    echo "Start viewer"
    ./viewer objects cube1 cube2 cube3 thorus1 thorus2 thorus3 taper1 taper2 composite1 composite2 composite3 composite4
fi
