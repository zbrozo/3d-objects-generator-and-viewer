cmake --build build

mkdir -p ./objects

cd ./objects

### simple cube
../generator --n 80 --o cube1 --t cube 70

../generator --o tmp1 --c0 square --p0 140 --s0 tz=70
../generator --n 80 --o cube1_1 --c0 tmp1 --c1 tmp1 --s1 rx=90 --c2 tmp1 --s2 rx=-90 --c3 tmp1 --s3 rx=180 --c4 tmp1 --s4 ry=90 --c5 tmp1 --s5 ry=-90

### cube with a hole in each face
#../generator --n 80 --o cube2 --t cube-ext --c SquareHolePart1 SquareHolePart2 --p 70 30 30 --f 0 0 70 30 30 

../generator --o tmp1 --c0 rectangle --p0 60 40 --s0 rx=90
../generator --o tmp1 --c0 tmp1 --s0 ty=30 --c1 tmp1 --s1 rz=180 ty=-30 --c2 tmp1 --s2 rz=90 tx=-30 --c3 tmp1 --s3 rz=-90 tx=30
../generator --o tmp2 --c0 trapeze --p0 140 60 40 --s0 ty=50
../generator --o tmp2 --c0 tmp2 --c1 tmp2 --s1 rz=90 --c2 tmp2 --s2 rz=-90 --c3 tmp2 --s3 rz=180
../generator --o tmp1 --c0 tmp1 --s0 tz=50 # 30+20
../generator --o tmp2 --c0 tmp2 --s0 tz=70 # 30+40
../generator --o tmp1 --c0 tmp1 --c1 tmp1 --s1 rx=90 --c2 tmp1 --s2 rx=-90 --c3 tmp1 --s3 rx=180 --c4 tmp1 --s4 ry=90 --c5 tmp1 --s5 ry=-90
../generator --o tmp2 --c0 tmp2 --c1 tmp2 --s1 rx=90 --c2 tmp2 --s2 rx=-90 --c3 tmp2 --s3 rx=180 --c4 tmp2 --s4 ry=90 --c5 tmp2 --s5 ry=-90
../generator --n 80 --o cube2_1 --c0 tmp1 --c1 tmp2

../generator --o tmp1 --c0 rectangle --p0 80 30 --s0 rx=90
../generator --o tmp1 --c0 tmp1 --s0 ty=40 --c1 tmp1 --s1 rz=180 ty=-40 --c2 tmp1 --s2 rz=90 tx=-40 --c3 tmp1 --s3 rz=-90 tx=40
../generator --o tmp2 --c0 trapeze --p0 140 80 30 --s0 ty=55 # 40+15
../generator --o tmp2 --c0 tmp2 --c1 tmp2 --s1 rz=90 --c2 tmp2 --s2 rz=-90 --c3 tmp2 --s3 rz=180
../generator --o tmp1 --c0 tmp1 --s0 tz=55 # 40+15
../generator --o tmp2 --c0 tmp2 --s0 tz=70 # 40+30
../generator --o tmp1 --c0 tmp1 --c1 tmp1 --s1 rx=90 --c2 tmp1 --s2 rx=-90 --c3 tmp1 --s3 rx=180 --c4 tmp1 --s4 ry=90 --c5 tmp1 --s5 ry=-90
../generator --o tmp2 --c0 tmp2 --c1 tmp2 --s1 rx=90 --c2 tmp2 --s2 rx=-90 --c3 tmp2 --s3 rx=180 --c4 tmp2 --s4 ry=90 --c5 tmp2 --s5 ry=-90
../generator --n 80 --o cube2_2 --c0 tmp1 --c1 tmp2

../generator --o tmp1 --c0 rectangle --p0 100 20 --s0 rx=90
../generator --o tmp1 --c0 tmp1 --s0 ty=50 --c1 tmp1 --s1 rz=180 ty=-50 --c2 tmp1 --s2 rz=90 tx=-50 --c3 tmp1 --s3 rz=-90 tx=50
../generator --o tmp2 --c0 trapeze --p0 140 100 20 --s0 ty=60 # 50+10
../generator --o tmp2 --c0 tmp2 --c1 tmp2 --s1 rz=90 --c2 tmp2 --s2 rz=-90 --c3 tmp2 --s3 rz=180
../generator --o tmp1 --c0 tmp1 --s0 tz=60 # 50+10
../generator --o tmp2 --c0 tmp2 --s0 tz=70 # 50+20
../generator --o tmp1 --c0 tmp1 --c1 tmp1 --s1 rx=90 --c2 tmp1 --s2 rx=-90 --c3 tmp1 --s3 rx=180 --c4 tmp1 --s4 ry=90 --c5 tmp1 --s5 ry=-90
../generator --o tmp2 --c0 tmp2 --c1 tmp2 --s1 rx=90 --c2 tmp2 --s2 rx=-90 --c3 tmp2 --s3 rx=180 --c4 tmp2 --s4 ry=90 --c5 tmp2 --s5 ry=-90
../generator --n 80 --o cube2_3 --c0 tmp1 --c1 tmp2

### 

../generator --n 64 --o cube3 --t cube-ext --c Pyramid --p 70 --f 0 0 70
../generator --n 80 --o cube4 --t cube-ext --c Pyramid --p 40 70 --f 0 0 40

### cube with one hole
../generator --o tmp1 --c0 square --p0 80 --s0 ry=90 tx=-40 --c1 square --p1 80 --s1 ry=-90 tx=40 --c2 square --p2 80 --s2 rx=90 ty=40 --c3 square --p3 80 --s3 rx=-90 ty=-40
../generator --o tmp2 --c0 trapeze --p0 80 100 10 --s0 rz=180 ty=45 tz=40 --c1 trapeze --p1 80 100 10 --s1 ty=-45 tz=40 --c2 trapeze --p2 80 100 10 --s2 rz=90 tx=45 tz=40 --c3 trapeze --p3 80 100 10 --s3 rz=-90 tx=-45 tz=40
../generator --o tmp3 --c0 rectangle --p0 100 80 --s0 rz=-90
../generator --o tmp3 --c0 tmp3 --s0 ry=90 tx=50 --c1 tmp3 --s1 ry=-90 tx=-50
../generator --n 80 --o cube5 --c0 tmp1 --c1 tmp2 --c2 tmp2 --s2 ry=180 --c3 tmp3 --c4 tmp3 --s4 rz=90

### thorus
../generator --o thorus1 --t thorus 4 3 
../generator --o thorus2 --t thorus 4 4
../generator --o thorus3 --t thorus 6 8 40 

../generator --n 60 --o thorus4 --t thorus 6 12 30 70 --s 0 0 3 15 2 15
../generator --n 60 --o thorus5 --t thorus 6 16 30 70 --s 0 0 4 15 4 15
../generator --3 --o thorus6 --t thorus 6 12 30 70 --s 0 0 3 10 2 10
../generator --3 --o thorus7 --t thorus 6 16 30 70 --s 0 0 4 10 4 10

../generator --3 --o thorus8 --t thorus 6 16 20 80 --s 0 0 0 0 0 0 0 0 16 10 16 10
###
../generator --o cone1 --t composite --c0 Cone --p0 3 50 50 --c1 Cone --p1 3 50 -50
../generator --o cone2 --t composite --c0 Cone --p0 6 50 50 --c1 Cone --p1 6 50 -50
../generator --o cone3 --t composite --c0 Cone --p0 3 50 50 --f0 0 0 0 0 0 0 0 0 0 --c1 Cone --p1 3 50 50 --f1 0 0 0 0 0 0 100 0 0

../generator --o tmp --t tetrahedron 80 60
../generator --n 80 --o tetrahedron1 --c0 tmp --s0 tz=-70

../generator --n 80 --o tetrahedron2 --t regulartetrahedron 80
../generator --n 80 --o tetrahedron3 --t fractaltetrahedron 50
    
../generator --n 80 --o composite1 --c0 Pyramid --p0 50 50 --c1 Pyramid --p1 50 50 --s1 ry=180
../generator --n 80 --o composite2 --c0 Pyramid --p0 50 50 --s0 tz=20 --c1 Pyramid --p1 50 50 --s1 tz=20 ry=180 --c2 Rectangle --p2 40 100 --s2 tz=50 ry=90 --c3 Rectangle --p3 40 100 --s3 tz=50 ry=270 --c4 Rectangle --p4 100 40 --s4 tz=50 rx=90 --c5 Rectangle --p5 100 40 --s5 tz=50 rx=270
../generator --n 80 --o composite3 --c0 Cone --p0 6 50 50 --s0 tz=25 --c1 Cone --p1 6 50 -50 --s1 tz=-25 --c2 Cylinder --p2 6 50 50 --s2 tz=25
../generator --n 80 --o composite4 --c0 Cone --p0 6 50 30 --s0 tz=25 --c1 Cone --p1 6 50 -30 --s1 tz=-25 rz=30 --c2 TriangulatedCylinder --p2 6 50 50 --s2 tz=25

../generator --o tmp --t cube 40
../generator --n 80 --o composite6 --c0 csign --p0 4 100 80 0 0 10 --s0 tx=-10 --c1 csign --p1 4 100 80 0 0 10 --s1 ry=180 tx=10 --c2 csign --p2 4 100 80 0 0 10 --s2 ry=90 tz=10 --c3 csign --p3 4 100 80 0 0 10 --s3 ry=-90 tz=-10 --c4 tmp

../generator --n 60 --o composite7 --c0 csign --p0 5 80 50 0 0 20 --s0 tx=10 --c1 csign --p1 5 80 50 0 0 20 --s1 rx=90 ry=180 tx=10

# scoopex sign :)
../generator --o tmp1 --t pentagram 14
../generator --o tmp2 --t thorus 4 10 15 90
../generator --n 60 --o scoopex --c0 tmp1 --c1 tmp2

cd ..
echo "Start viewer"
./viewer objects scoopex cube2_1 cube2_2 cube2_3 composite4 composite7 tetrahedron3 composite6 composite7
#thorus4 thorus5 thorus6 thorus7 composite4 tetrahedron1 tetrahedron3
