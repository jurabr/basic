REM Computes V and M forces on beam if Va Ma, Mb, L, qa, qb are given
10 DATA 2 -2 5 2 2 
20 READ  A, B, L, Q, R
30 FOR I = 0 TO 10
40 LET X = I / 10 * L
41 LET Y = L - X
42 LET P = Q*L/2 - Q*X + ((R-Q)*L/6 - (R-Q)*X*X/2/L)
43 LET V =  P - (B+A)/L
45 LET P = Q*X*L/2 - Q*X*X/2 + ((R-Q)*x*L/6 - (R-X)*x*x*x/6/L)
46 LET M = P + (B*X - A*Y)/L
50 PRINT I,X,V,M
99 NEXT I
quit
