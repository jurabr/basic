REM Gauss Elimination (full, dense matrix A)
REM Indexes start from 1
REM Only symmetric upper part of materix is used!

REM Data input:
10 DATA 3 1 2 3  2 1 3 3 3 7 5 5 5
20 READ N
30 DIM A(9,9)
35 DIM B(9)
40 FOR I = 1 TO N
50 FOR J = 1 TO N
60 READ A(I,J)
70 NEXT J
80 NEXT I
90 FOR I = 1 TO N STEP 1
95 READ B(I)
100 NEXT I

REM Control print of data:
140 FOR I = 1 TO N
150 FOR J = 1 TO N
160 PRINT A(I,J);
170 NEXT J
175 PRINT " |";B(I)
180 NEXT I

REM Forward run:
300 FOR K = 1 TO N-1 
310 FOR I = K+1 TO N 
320 LET C = A(K,I)/A(K,K)
330 FOR J = I TO N
340 LET A(I,J) = A(I,J) - C*A(K,J)
350 NEXT J
360 LET B(I) = B(I) - C*B(K)
370 NEXT I
380 NEXT K
390 LET B(N) = B(N) / A(N,N)

REM Backward run:
400 FOR I = N-1 TO 1 STEP -1
410 LET S = 0
420 FOR J = I+1 TO N
430 LET S = S + A(I,J) * B(J)
440 NEXT J
450 LET B(I) = (B(I)-S)/A(I,I)
460 NEXT I

REM Results:
500 PRINT "Results:"
510 FOR I = 1 TO N
520 PRINT B(I)
530 NEXT I


REM For testing in the ByWater BASIC:
quit
