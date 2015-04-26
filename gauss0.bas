REM Gauss Elimination (full, dense matrix A)
REM Fields are filled from 0 to M-1 (N numbers)

REM Data input:
10 DATA 3 1 2 3  2 1 3 3 3 7 5 5 5
20 READ M
25 LET N = M-1
30 DIM A(9,9)
35 DIM B(9)
36 DIM X(9)
40 FOR I = 0 TO N
50 FOR J = 0 TO N
60 READ A(I,J)
70 NEXT J
80 NEXT I
90 FOR I = 0 TO N
95 READ B(I)
100 NEXT I

REM Control print of data:
140 FOR I = 0 TO N
150 FOR J = 0 TO N
160 PRINT A(I,J);
170 NEXT J
175 PRINT " |";B(I)
180 NEXT I

REM Forward run:
300 FOR J = 0 TO N 
310 FOR I = J+1 TO N 
320 LET C = A(I,J)/A(J,J)
330 FOR K = 0 TO N
340 LET A(I,K) = A(I,K) - C*A(J,K)
350 NEXT K
360 LET B(I) = B(I) - C*B(J)
370 NEXT I
380 NEXT J
390 LET X(N) = B(N) / A(N,N)

REM Backward run:
400 FOR I = N-1 TO 0 STEP -1
410 LET S = 0
420 FOR J = I+1 TO N
430 LET S = S + A(I,J) * X(J)
440 NEXT J
450 LET X(I) = (B(I)-S)/A(I,I)
460 NEXT I

REM Results:
500 PRINT "Results:"
510 FOR I = 0 TO N
520 PRINT X(I)
530 NEXT I

REM For testing in the ByWater BASIC:
quit
