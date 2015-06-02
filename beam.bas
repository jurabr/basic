REM Continuous beam without normal forces
REM Finite differences method

REM Data input:
REM   VVVVV
REM --+---+---
REM   ^   ^
REM N   .. number of beams
REM E*I .. bending stiffness
REM L q (repeaing N times) .. lenght, load
REM L R .. (supports on ends: 2..free 1..simple, 0..full)
10 DATA 3 2000  6 0 5 1000 6 0   0 0 
20 READ N
30 DIM E(10)
35 DIM A(21)
36 DIM B(6)
40 FOR I = 1 TO N
50 READ E((i-1)*2+1), E((i-1)*2+2)
60 NEXT I
70 READ F(0), F(1)

REM Computation of DOFs number (just M's + DOFS on ends)
80 LET Q = N+F(0)+F(1)

REM Assebling of stiffness matrix
100 FOR I=1 TO N

199 NEXT I
