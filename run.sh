cmake --build build

mkdir -p ./objects

cd ./objects

### simple cube
../generator --l 80 --o cube1 --n cube 70

../generator --o tmp1 --c0 square --p0 140 --t0 tz=70
../generator --l 80 --o cube1_1 --c0 tmp1 --c1 tmp1 --t1 rx=90 --c2 tmp1 --t2 rx=-90 --c3 tmp1 --t3 rx=180 --c4 tmp1 --t4 ry=90 --c5 tmp1 --t5 ry=-90

### cube with a hole in each face
../generator --o tmp1 --c0 rectangle --p0 60 40 --t0 rx=90
../generator --o tmp1 --c0 tmp1 --t0 ty=30 --c1 tmp1 --t1 rz=180 ty=-30 --c2 tmp1 --t2 rz=90 tx=-30 --c3 tmp1 --t3 rz=-90 tx=30
../generator --o tmp2 --c0 trapeze --p0 140 60 40 --t0 ty=50
../generator --o tmp2 --c0 tmp2 --c1 tmp2 --t1 rz=90 --c2 tmp2 --t2 rz=-90 --c3 tmp2 --t3 rz=180
../generator --o tmp1 --c0 tmp1 --t0 tz=50 # 30+20
../generator --o tmp2 --c0 tmp2 --t0 tz=70 # 30+40
../generator --o tmp1 --c0 tmp1 --c1 tmp1 --t1 rx=90 --c2 tmp1 --t2 rx=-90 --c3 tmp1 --t3 rx=180 --c4 tmp1 --t4 ry=90 --c5 tmp1 --t5 ry=-90
../generator --o tmp2 --c0 tmp2 --c1 tmp2 --t1 rx=90 --c2 tmp2 --t2 rx=-90 --c3 tmp2 --t3 rx=180 --c4 tmp2 --t4 ry=90 --c5 tmp2 --t5 ry=-90
../generator --l 80 --o cube2_1 --c0 tmp1 --c1 tmp2

../generator --o tmp1 --c0 rectangle --p0 80 30 --t0 rx=90
../generator --o tmp1 --c0 tmp1 --t0 ty=40 --c1 tmp1 --t1 rz=180 ty=-40 --c2 tmp1 --t2 rz=90 tx=-40 --c3 tmp1 --t3 rz=-90 tx=40
../generator --o tmp2 --c0 trapeze --p0 140 80 30 --t0 ty=55 # 40+15
../generator --o tmp2 --c0 tmp2 --c1 tmp2 --t1 rz=90 --c2 tmp2 --t2 rz=-90 --c3 tmp2 --t3 rz=180
../generator --o tmp1 --c0 tmp1 --t0 tz=55 # 40+15
../generator --o tmp2 --c0 tmp2 --t0 tz=70 # 40+30
../generator --o tmp1 --c0 tmp1 --c1 tmp1 --t1 rx=90 --c2 tmp1 --t2 rx=-90 --c3 tmp1 --t3 rx=180 --c4 tmp1 --t4 ry=90 --c5 tmp1 --t5 ry=-90
../generator --o tmp2 --c0 tmp2 --c1 tmp2 --t1 rx=90 --c2 tmp2 --t2 rx=-90 --c3 tmp2 --t3 rx=180 --c4 tmp2 --t4 ry=90 --c5 tmp2 --t5 ry=-90
../generator --l 80 --o cube2_2 --c0 tmp1 --c1 tmp2

../generator --o tmp1 --c0 rectangle --p0 100 20 --t0 rx=90
../generator --o tmp1 --c0 tmp1 --t0 ty=50 --c1 tmp1 --t1 rz=180 ty=-50 --c2 tmp1 --t2 rz=90 tx=-50 --c3 tmp1 --t3 rz=-90 tx=50
../generator --o tmp2 --c0 trapeze --p0 140 100 20 --t0 ty=60 # 50+10
../generator --o tmp2 --c0 tmp2 --c1 tmp2 --t1 rz=90 --c2 tmp2 --t2 rz=-90 --c3 tmp2 --t3 rz=180
../generator --o tmp1 --c0 tmp1 --t0 tz=60 # 50+10
../generator --o tmp2 --c0 tmp2 --t0 tz=70 # 50+20
../generator --o tmp1 --c0 tmp1 --c1 tmp1 --t1 rx=90 --c2 tmp1 --t2 rx=-90 --c3 tmp1 --t3 rx=180 --c4 tmp1 --t4 ry=90 --c5 tmp1 --t5 ry=-90
../generator --o tmp2 --c0 tmp2 --c1 tmp2 --t1 rx=90 --c2 tmp2 --t2 rx=-90 --c3 tmp2 --t3 rx=180 --c4 tmp2 --t4 ry=90 --c5 tmp2 --t5 ry=-90
../generator --l 80 --o cube2_3 --c0 tmp1 --c1 tmp2

### 
../generator --l 64 --o cube3 --n cube-ext --c Pyramid --p 70 30 --t 0 0 70
../generator --l 80 --o cube4 --n cube-ext --c Pyramid --p 40 70 --t 0 0 40

### cube with one hole
../generator --o tmp1 --c0 square --p0 80 --t0 ry=90 tx=-40 --c1 square --p1 80 --t1 ry=-90 tx=40 --c2 square --p2 80 --t2 rx=90 ty=40 --c3 square --p3 80 --t3 rx=-90 ty=-40
../generator --o tmp2 --c0 trapeze --p0 80 100 10 --t0 rz=180 ty=45 tz=40 --c1 trapeze --p1 80 100 10 --t1 ty=-45 tz=40 --c2 trapeze --p2 80 100 10 --t2 rz=90 tx=45 tz=40 --c3 trapeze --p3 80 100 10 --t3 rz=-90 tx=-45 tz=40
../generator --o tmp3 --c0 rectangle --p0 100 80 --t0 rz=-90
../generator --o tmp3 --c0 tmp3 --t0 ry=90 tx=50 --c1 tmp3 --t1 ry=-90 tx=-50
../generator --l 80 --o cube5 --c0 tmp1 --c1 tmp2 --c2 tmp2 --t2 ry=180 --c3 tmp3 --c4 tmp3 --t4 rz=90

### thorus
../generator --o thorus1 --n thorus 4 3 
../generator --o thorus2 --n thorus 4 4
../generator --o thorus3 --n thorus 6 8 40 

../generator --l 60 --o thorus4 --n thorus 6 12 30 70 --s 0 0 3 15 2 15
../generator --l 60 --o thorus5 --n thorus 6 16 30 70 --s 0 0 4 15 4 15
../generator --l 80 --3 --o thorus6 --n thorus 6 12 30 70 --s 0 0 3 10 2 10
../generator --l 80 --3 --o thorus7 --n thorus 6 16 30 70 --s 0 0 4 10 4 10
../generator --l 80 --3 --o thorus8 --n thorus 6 16 20 80 --s 0 0 0 0 0 0 0 0 16 10 16 10
../generator --l 60 --o thorus9 --n thorus 3 6 50 70 6 33 0

###
../generator --l 80 --o cone1 --c0 Cone --p0 3 80 80 --c1 Cone --p1 3 80 -80
../generator --l 80 --o cone2 --c0 Cone --p0 6 80 80 --c1 Cone --p1 6 80 -80
../generator --l 80 --o cone3 --c0 Cone --p0 3 80 80 --c1 Cone --p1 3 80 80 --t1 ry=180 

../generator --l 80 --o tmp --n tetrahedron 80 60
../generator --l 80 --o tetrahedron1 --c0 tmp --t0 tz=-70

../generator --l 80 --o tetrahedron2 --n regulartetrahedron 80
../generator --l 80 --o tetrahedron3 --n fractaltetrahedron 50
    
../generator --l 80 --o composite1 --c0 Pyramid --p0 50 50 --c1 Pyramid --p1 50 50 --t1 ry=180
../generator --l 80 --o composite2 --c0 Pyramid --p0 50 50 --t0 tz=20 --c1 Pyramid --p1 50 50 --t1 tz=20 ry=180 --c2 Rectangle --p2 40 100 --t2 tz=50 ry=90 --c3 Rectangle --p3 40 100 --t3 tz=50 ry=270 --c4 Rectangle --p4 100 40 --t4 tz=50 rx=90 --c5 Rectangle --p5 100 40 --t5 tz=50 rx=270
../generator --l 80 --o composite3 --c0 Cone --p0 6 50 50 --t0 tz=25 --c1 Cone --p1 6 50 -50 --t1 tz=-25 --c2 Cylinder --p2 6 50 50 --t2 tz=25
../generator --l 80 --o composite4 --c0 Cone --p0 6 50 30 --t0 tz=25 --c1 Cone --p1 6 50 -30 --t1 tz=-25 rz=30 --c2 TriangulatedCylinder --p2 6 50 50 --t2 tz=25

../generator --o tmp --n cube 40
../generator --o tmp1 --n thorus 3 6 15 95 3 45 0
../generator --l 80 --o composite6 --c0 tmp1 --t0 tx=-10 --c1 tmp1 --t1 ry=180 tx=10 --c2 tmp1 --t2 ry=90 tz=10 --c3 tmp1 --t3 ry=-90 tz=-10 --c4 tmp

../generator --3 --o tmp1 --n thorus 4 8 20 70 6 0 15
../generator --l 80 --o composite7 --c0 tmp1 --t0 rz=-45 tx=20 --c1 tmp1 --t1 rz=130 rx=90 tx=-20

# scoopex sign :)
../generator --o tmp1 --n pentagram 14
../generator --o tmp2 --n thorus 4 10 15 90
../generator --l 60 --o scoopex --c0 tmp1 --c1 tmp2

cd ..
echo "Start viewer"
./viewer objects cube3 cube1 thorus9 composite7 thorus7 cone1 cone2 scoopex cube2_1 cube2_2 cube2_3 composite4 composite7 tetrahedron3 composite6 composite7
#thorus4 thorus5 thorus6 thorus7 composite4 tetrahedron1 tetrahedron3
