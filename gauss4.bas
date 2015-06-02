REM Gauss Elimination (full, dense matrix A)
REM Indexes start from 1
REM Only symmetric upper part of materix is used!
REM Attempt to use 1D arrays
REM "A" Indexes: L = I +(J*J-J)/2

REM Data input:
10 DATA 3 1 2 3  2 1 3 3 3 7 5 5 5
20 READ N
30 DIM A(6)
35 DIM B(3)
40 FOR I = 1 TO N
50 FOR J = 1 TO N
55 IF J >= I THEN
58 LET L = I +(J*J-J)/2 -1
60 READ A(L)
65 ELSE
66 READ C
67 END IF
70 NEXT J
80 NEXT I
90 FOR I = 1 TO N STEP 1
95 READ B(I)
100 NEXT I

REM Control print of data:
140 FOR I = 1 TO N
150 FOR J = 1 TO N
155 LET L = I +(J*J-J)/2
160 PRINT A(L);
170 NEXT J
175 PRINT " |";B(I)
180 NEXT I

REM Forward run:
300 FOR K = 1 TO N-1 
310 FOR I = K+1 TO N 
311 LET L = K + (I*I-I)/2 -1
312 LET M = K + (K*K-K)/2 -1
320 LET C = A(L)/A(M)
330 FOR J = I TO N
331 LET L = I +(J*J-J)/2 -1
332 LET M = K +(J*J-J)/2 -1
340 LET A(L) = A(L) - C*A(M)
350 NEXT J
360 LET B(I) = B(I) - C*B(K)
370 NEXT I
380 NEXT K
385 LET L = N +(N*N-N)/2 -1
390 LET B(N) = B(N) / A(L)

REM Backward run:
400 FOR I = N-1 TO 1 STEP -1
410 LET S = 0
420 FOR J = I+1 TO N
421 LET L = I +(J*J-J)/2 -1
430 LET S = S + A(L) * B(J)
440 NEXT J
441 LET L = I +(I*I-I)/2 -1
450 LET B(I) = (B(I)-S)/A(L)
460 NEXT I

REM Results:
500 PRINT "Results:"
510 FOR I = 1 TO N
520 PRINT B(I)
530 NEXT I


REM For testing in the ByWater BASIC:
quit
