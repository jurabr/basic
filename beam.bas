REM Continuous beam without normal forces
REM Finite differences method

REM Data input:
REM      VVVVVVVVV
REM +----+---+---+----+
REM ^ 6  ^ 5 ^ 5 ^  6 ^
REM N   .. number of beams
REM E*I .. bending stiffness
REM L q (repeaing N times) .. lenght, load
REM L R .. (supports on ends: 1..simple, 0..full)
10 DATA 4 2000000000  6 0 6 1667 6 1667 6 0   1 1 
20 READ N
25 READ Y
30 DIM E(10)
35 DIM A(21)
36 DIM B(6)
38 DIM F(2)
40 FOR I = 1 TO N
50 LET J = 2*(I-1)+1
60 READ E(J), E(J+1)
70 NEXT I
80 READ F(0), F(1)
REM Number of unknowns:
90 LET Q = N-1+F(0)+F(1)

REM Assebling of stiffness matrix
100 FOR I=1 TO N
110 LET K = I-1+F(0)
120 LET H = I+F(0)
130 IF I=N THEN
134 H = 0
140 IF F(1)=1 THEN
150 LET H=Q
150 END IF
160 END IF
170 GOSUB 999
180 NEXT I

REM Pseudo-image of structure
190 GOSUB 5000

REM Control print of stiffness matrix:
199 PRINT "System of equations:"
200 FOR I=1 TO Q
210 FOR J=1 TO Q
211 LET K = I
212 LET L = J
220 IF I>J THEN
230 LET K = J
240 LET L = I
245 END IF
250 LET M = K +(L*L-L)/2 -1
260 PRINT A(M);
270 NEXT J
280 PRINT " | " ;B(I-1)
290 NEXT I

REM Gauss ellimination:
310 GOSUB 4300

REM Results:
320 FOR I=1 TO N
330 LET T=0
340 LET U=0
350 GOSUB 2000
360 PRINT "Ml";I;":";R
370 PRINT "Mr";I;":";U
399 NEXT I


REM BWBASIC end:
quit

998  END

REM Localisation procedure:
REM Member (2,1) is not needed IN THIS CASE
999  LET J = 2*(I-1)+1
1000 LET L = E(J)
1001 LET W = E(J+1)
1002 LET W = W*L*L/12
1010 IF K>0 THEN
1020 LET P = K +(K*K-K)/2-1
1030 LET A(P) = A(P) + 4*Y/L
1031 LET B(K-1) = B(K-1) + W
1033 END IF
1035 IF (K*H)>0 THEN
1040 LET P = K +(H*H-H)/2-1
1050 LET A(P) = A(P) + 2*Y/L
1095 END IF
1099 IF H>0 THEN
1100 LET P = H +(H*H-H)/2-1
1110 LET A(P) = A(P) + 4*Y/L
1111 LET B(H-1) = B(H-1) - W
1120 END IF
1130 RETURN 

REM Element results (V1,M1, V2,Q2)
2000 LET J = 2*(I-1)+1
2010 LET L = E(J)
2020 LET W = E(J+1)
2030 LET W = W*L*L/12
2040 LET A(1) = Y/L/L*6
2050 LET A(2) = Y/L*4
2110 LET P=F(0)+I-2
2115 LET D = 0
2116 IF P> -1 THEN
2120 LET D = B(P)
2121 END IF
2128 LET C = 0
2129 IF (P+1) <(Q+1) THEN
2130 LET C = B(P+1)
2131 END IF
2140 LET O = T -A(1)*D - A(1)*C
2140 LET R = U + A(2)*D +0.5*A(2)*C -W
2140 LET T = A(1)*D +A(1)*C
2140 LET U = 0.5*A(2)*D +A(2)*C +W
2200 RETURN 


REM GAUSS Ellimination (from gauss4.bas):
REM uses symmetric matrix (upper triangle)

REM Forward run:
4300 FOR K = 1 TO Q-1 
4310 FOR I = K+1 TO Q 
4311 LET L = K + (I*I-I)/2 -1
4312 LET M = K + (K*K-K)/2 -1
4320 LET C = A(L)/A(M)
4330 FOR J = I TO Q
4331 LET L = I +(J*J-J)/2 -1
4332 LET M = K +(J*J-J)/2 -1
4340 LET A(L) = A(L) - C*A(M)
4350 NEXT J
4360 LET B(I-1) = B(I-1) - C*B(K-1)
4370 NEXT I
4380 NEXT K
4385 LET L = Q +(Q*Q-Q)/2 -1
4390 LET B(Q-1) = B(Q-1) / A(L)

REM Backward run:
4400 FOR I = Q-1 TO 1 STEP -1
4410 LET S = 0
4420 FOR J = I+1 TO Q
4421 LET L = I +(J*J-J)/2 -1
4430 LET S = S + A(L) * B(J-1)
4440 NEXT J
4441 LET L = I +(I*I-I)/2 -1
4450 LET B(I-1) = (B(I-1)-S)/A(L)
4460 NEXT I

REM Results:
4500 PRINT "Deformations:"
4510 FOR I = 0 TO Q-1
4520 PRINT B(I)
4530 NEXT I
4600 RETURN

REM Pseudo-graphics image of structrure
5000 IF F(0)=1 THEN 5004
5001 PRINT "|";
5004 PRINT "+";
5010 FOR I=1 TO N 
5011 FOR J=1 TO 2
5012 LET K=2*(I-1)+2
5013 IF E(K) >0.0 THEN 5016
5014 PRINT "-";
5015 GOTO 5017
5016 PRINT "V";
5017 NEXT J
5018 PRINT "+";
5019 NEXT I
5020 IF F(1)=1 THEN 5024
5021 PRINT "|"
5022 GOTO 5030
5024 PRINT " "
5030 RETURN
