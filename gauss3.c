#include<stdio.h>
int    i,j,k,n;
double A[20][20],b[20],c,x[10],sum=0.0;

int main(int argc, char *argv[])
{
  /* Vstupni data:*/
    printf("\nEnter the order of matrix: ");
    scanf("%d",&n);
    printf("\nEnter the elements A(i,j) b(i):\n\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<(n); j++)
        {
            printf("A[%d][%d] : ", i+1,j+1);
            scanf("%lf",&A[i][j]);
        }
        printf("b[%d] : ", i+1);
        scanf("%lf",&b[i]);
    }

    /* Kontrolni vypis */
    printf("\n\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            printf("%e  ",A[i][j]);
        }
        printf(" | %e\n",b[i]);
    }

    /* dopredny chod */
    for(j=0; j<n; j++) 
    {
        for(i=j+1; i<n; i++)
        {
              c=A[i][j]/A[j][j];
              for(k=0; k<n; k++)
              {
                  A[i][k]=A[i][k]-c*A[j][k];
              }
              b[i]=b[i]-c*b[j];
        }
    } 
    x[n-1]=b[n-1]/A[n-1][n-1];

    /* zpetny chod */
    for(i=n-2; i>=0; i--)
    {
        sum=0;
        for(j=i+1; j<n; j++)
        {
            sum=sum+A[i][j]*x[j];
        }
        x[i]=(b[i]-sum)/A[i][i];
    }

    printf("\nResults: \n");
    for(i=0; i<n; i++)
    {
        printf("x%d=%e\n",i,x[i]);
    }

    /* Kontrolni vypis 2 */
    printf("\n\n Eliminovana:\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            printf("%e  ",A[i][j]);
        }
        printf(" | %e\n",b[i]);
    }


    return(0);
}
