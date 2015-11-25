/*
 * File name: gauss4.c
 * Date:      2015/11/25 20:19
 * Author:    Jiri Brozovsky
 */

#include <stdio.h>
#include <stdlib.h>

int    i,j,k,l,m,n;
double A[21],b[6],c,x[6],s=0.0;

int main(int argc, char *argv[])
{
  /* Vstupni data:*/
    printf("\nEnter the order of matrix: ");
    scanf("%d",&n);
    printf("\nEnter the elements A(i,j) b(i):\n\n");
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=(n); j++)
        {
          if (j>=i)
          {
            printf("A[%d][%d] : ", i,j);
            scanf("%lf",&A[i+(j*j-j)/2 -1]);
          }
        }
        printf("b[%d] : ", i+1);
        scanf("%lf",&b[i-1]);
    }

    /* Kontrolni vypis */
    printf("\n\n");
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=n; j++)
        {
            printf("%e  ",A[i+(j*j-j)/2 -1]);
        }
        printf(" | %e\n",b[i-1]);
    }

    /* dopredny chod */
    for (k=1; k<n; k++)
    {
      for (i=k+1; i<=n; i++)
      {
        l = k + (i*i-i)/2-1 ;
        m = k + (k*k-k)/2-1 ;
        c = A[l]/A[m] ;
        for (j=i; j<=n; j++)
        {
          l = i + (j*j-j)/2-1 ;
          m = k + (j*j-j)/2-1 ;
          A[l] -= c*A[m] ;
        }
        b[i-1] -= c*b[k-1] ;
      }
    }
    l = n + (n*n-n)/2-1 ;
    b[n-1] = b[n-1] / A[l] ;

    /* zpetny chod */
    for (i=n-1 ; i >=1; i--)
    {
      s = 0.0 ;
      for (j=i+1; j<=n; j++)
      {
        l = i + (j*j-j)/2-1 ;
        s += A[l] * b[j-1] ;
      }
      l = i + (i*i-i)/2-1 ;
      b[i-1] = (b[i-1]-s) / A[l] ;
    }
    

    printf("\nResults: \n");
    for(i=0; i<n; i++)
    {
       printf("x[%d] = %e\n",i+1,b[i]);
    }

    return(0);
}

/* end of gauss4.c */
