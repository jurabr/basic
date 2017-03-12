REM Computes V and M forces on beam if Va Ma, Mb, L, qa, qb are given
10 DATA 2 -2 5 2 2 
20 READ  A, B, L, Q, R
25 LET T = 1/8*L*L*(Q+R)/2 : LET K = 20/T : LET T = 160/L
26 LET G = 0 : LET E = 0 : LET F = 0 
27 LINE 0, 2*160/4, 160, 2*160/4
28 LINE 0, 3*160/4, 160, 3*160/4
29 LET C  = 0 : LET D = 0 : LET Z = 0 
30 FOR I = 0 TO 10
40 LET X = I / 10 * L
41 LET Y = L - X
42 LET P = Q*L/2 - Q*X + ((R-Q)*L/6 - (R-Q)*X*X/2/L)
43 LET V =  P - (B+A)/L
45 LET P = Q*X*L/2 - Q*X*X/2 + ((R-Q)*x*L/6 - (R-Q)*X*X*X/6/L)
46 LET M = P + (B*X - A*Y)/L
47 IF ABS(M) > ABS(D) THEN LET D = M : LET Z = X
48 IF ABS(V) > ABS(C) THEN LET C = V 
REM 50 PRINT I,X,V,M
51 LINE F*T, 2*160/4+E*K, X*T, 2*160/4+V*K
52 LINE F*T, 3*160/4+G*K, X*T, 3*160/4+M*K
59 LET G = M : LET E = V : LET F = X
60 NEXT I
61 LINE X*T-1, 2*160/4, X*T-1, 2*160/4+V*K
62 LINE X*T-1, 3*160/4, X*T-1, 3*160/4+M*K
63 PRINT "Internal forces on beam:"
64 PRINT "Vmax=", C
65 PRINT "Mmax=", D, "X=", Z
99 END
