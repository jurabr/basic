REM Continuous beam without normal forces
REM Finite differences method

REM Data input:
REM   VVVVV
REM --+---+---
REM   ^   ^
REM N   .. number of beams
REM E*I .. bending stiffness
REM L q (repeaing N times) .. lenght, load
REM L R .. (supports on ends: 1..simple, 0..full)
10 DATA 3 2000  6 0 5 1000 6 0   0 0 
20 READ N
25 READ S
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
140 IF F(1)=1 THEN
150 LET H=9
150 END IF
160 END IF
170 GOSUB 999

199 NEXT I

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
280 PRINT " |"
290 NEXT I


REM LOCALISATION PROCEDURE
quit
998  END
999  LET J = 2*(I-1)+1
1000 LET L = E(J)
1001 PRINT "Position: ";I;K;H
1010 IF K>0 THEN
1020 LET P = K +(K*K-K)/2-1
1021 PRINT "P11";P
1030 LET A(P) = A(P) + 4*S/L
1033 END IF
1035 IF (K*H)>0 THEN
1040 LET P = K +(H*H-H)/2-1
1041 PRINT "P12";P
1050 LET A(P) = A(P) + 2*S/L
1080 LET P = H +(K*K-K)/2-1
1081 PRINT "P21";P
1090 LET A(P) = A(P) + 2*S/L
1095 END IF
1099 IF H>0 THEN
1100 LET P = H +(H*H-H)/2-1
1101 PRINT "P22 (H)";P;H
1110 LET A(P) = A(P) + 4*S/L
1120 END IF
1130 RETURN GOSUB

