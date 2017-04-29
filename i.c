/*
   File name: i.c
   Date:      2017/04/04 19:15
   Author:    Jiri Brozovsky

   Copyright (C) 2017 Jiri Brozovsky

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   in a file called COPYING along with this program; if not, write to
   the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA
   02139, USA.

   Computes moments of inertia of cross-section constructed from
   non-overlapping rectangles.

   ^ y    +---+
   |      |   h
   |      +-b-+
   +---> x
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define I_MAX 20 
#define DIMS  300
#define DIMS2 100
#define D10   10

/* Coputed data: */
int    n ;
double x[I_MAX] ;
double y[I_MAX] ;
double b[I_MAX] ;
double h[I_MAX] ;
double tx, ty, A ;
double Ix, Iy, Dxy, c, d, I1, I2, Dm, fi ;

/* PostScript plotting data: */
double mult = 0.0 ;
double x_0, y_0, x_1, y_1 ;


/** Reads input data from file
 * @param fr pointer to (already open) file stream */
int read_input(FILE *fr)
{
  int i ;

  fprintf(stderr,"Moments of inertia (input: Nparts;  Xi,Yi,Bi,Hi)...\n");

  fscanf(fr, "%i", &n);
  if (n < 1) { fprintf(stderr,"Number of parts too small!\n"); exit(-1); }
  if (n > I_MAX) { fprintf(stderr,"Number of parts too big!\n"); exit(-1); }
  
  fprintf(stderr,"Number of parts: %2i\n", n);

  for (i=0; i<n; i++)
  {
    fscanf(fr, "%lf %lf %lf %lf", &x[i], &y[i], &b[i], &h[i]);
    fprintf(stderr, "x=%1.4lf y=%1.4lf b=%1.4lf h=%1.4lf\n", x[i], y[i], b[i], h[i]);
  }

  return(0);
}

/** Centre of gravity: */
int compute_t(void)
{
  int i ;
  double Sx = 0.0 ;
  double Sy = 0.0 ;

  A  = 0.0 ;
  
  for (i=0; i<n; i++)
  {
    A += fabs(b[i]*h[i]) ;
    Sy += fabs(b[i]*h[i]) * (y[i] + fabs(h[i])/2.0) ;
    Sx += fabs(b[i]*h[i]) * (x[i] + fabs(b[i])/2.0) ;
  }

  tx =  Sx / A ;
  ty =  Sy / A ;

  fprintf(stderr,"\nCentre of gravity:\ntx = %1.4lf ty = %1.4lf   A = %1.4lf\n",tx,ty, A);

  return(0);
}

/* Moments of inertia: */
int compute_I(void)
{
  int i ;
  double A ;

  Ix  = 0 ;
  Iy  = 0 ;
  Dxy = 0 ;

  for (i=0; i<n; i++)
  {
    c = (x[i]+fabs(b[i])/2.0) - tx ;
    d = (y[i]+fabs(h[i])/2.0) - ty ;
    A = fabs(b[i]*h[i]) ;
    Ix += fabs(b[i]*pow(h[i],3)/12.0) + d*d*A ;
    Iy += fabs(h[i]*pow(b[i],3)/12.0) + c*c*A ; 
    
    Dxy = c*d*A ;
  }

  fprintf(stderr,"Moments of inertia:\nIx = %1.4lf Iy = %1.4lf Dxy = %1.4f\n",Ix,Iy, Dxy);

  return(0);
}

int compute_I_1_2(void)
{
  double A, B ;

  A = (Ix + Iy)/2.0 ;
  B = (sqrt(pow(Ix-Iy,2) - 4.0*Dxy*Dxy))/2.0;

  I1 = A + B ;
  I2 = A - B ;
  Dm = (I1-I2)/2.0 ;
  if (fabs(Dxy) < 1e-9 ) 
  {
    if (Ix<Iy) fi = 90 ;
    else       fi =  0 ;
  }
  else
  {fi = 180.0 * (atan((I1-Ix)/Dxy) / 3.141592653589793238462643383279502884);}


  fprintf(stderr,"I1 = %1.4lf I2 = %1.4lf, Dmax= %1.4lf\n",I1,I2,Dm);
  
  return(0);
}

/** Computes max. dimensions  */
int get_limits(double *x0, double *y0, double *x1, double *y1)
{
  int i ;

  for (i=0; i<n; i++) 
  {
    if (x == 0) /* initial values */
    {
      *x0 = x[i] ;
      *y0 = y[i] ;
      *x1 = x[i] + b[i] ;
      *y1 = y[i] + h[i] ;
    }
    else
    {
      if (*x0 > x[i]) {*x0 = x[i] ;}
      if (*y0 > y[i]) {*y0 = y[i] ;}

      if (*x1 < (x[i]+fabs(b[i]))) {*x1 = x[i]+fabs(b[i]) ;}
      if (*y1 < (y[i]+fabs(h[i]))) {*y1 = y[i]+fabs(h[i]) ;}
    }
  }

  if (((*x1)-(*x0)) > ((*y1)-(*y0)))
  {
    mult = (double)DIMS /  ((*x1)-(*x0)) ;
  }
  else
  {
    mult = (double)DIMS / ((*y1)-(*y0)) ;
  }
  fprintf(stderr,"Dimensions (control print):\n");
  fprintf(stderr,"x0=%e, y0=%e\nxm=%e, ym=%e\nb =%e, h =%e (mult=%e)\n",*x0,*y0,*x1,*y1,*x1-*x0,*y1-*y0,mult);
  
  return(0);
}

/** Recomputes coordinates */
int px(double x)
{
  return((int)(x*mult)) ;
}

/** Draws shape of the thing to a PostScript file
 * */
int draw_ps(FILE *fw, int x0, int y0, int x1, int y1)
{
  int i, j ;
  int ix[5] ;
  int iy[5] ;
  char str[80];

  fprintf(fw,"%%!PS-Adobe-2.0\n");
  fprintf(fw,"%%%%Creator: CrossSectioner \n");
  fprintf(fw,"%%%%BoundingBox: %i %i %i %i\n",
      0-D10,0-D10, DIMS+D10+DIMS2,DIMS+D10);
  fprintf(fw,"/Courier\nfindfont\n");
  fprintf(fw,"12 scalefont setfont\n");
  fprintf(fw,"0 setgray\n");

  /* coordinates: */
  fprintf(fw,"%i setlinewidth\n", 1);
  fprintf(fw,"%i %i moveto %i %i lineto\nclosepath\n", 0, 0, DIMS+D10, 0);
  fprintf(fw,"%i stroke\n", 1);
  fprintf(fw,"%i %i moveto %i %i lineto\nclosepath\n", DIMS+D10, 0, DIMS, (int)(-D10/4));
  fprintf(fw,"%i stroke\n", 1);
  fprintf(fw,"%i %i moveto %i %i lineto\nclosepath\n", DIMS+D10, 0, DIMS, (int)(+D10/4));
  fprintf(fw,"%i stroke\n", 1);

  fprintf(fw,"%i %i moveto %i %i lineto\nclosepath\n", 0, 0, 0, DIMS+D10);
  fprintf(fw,"%i stroke\n", 1);
  fprintf(fw,"%i %i moveto %i %i lineto\nclosepath\n", 0, DIMS+D10, (int)(-D10/4), DIMS);
  fprintf(fw,"%i stroke\n", 1);
  fprintf(fw,"%i %i moveto %i %i lineto\nclosepath\n", 0, DIMS+D10, (int)(+D10/4), DIMS);
  fprintf(fw,"%i stroke\n", 1);


  /* center of gravity: */
  fprintf(fw,"%i %i moveto %i %i lineto\nclosepath\n", px(tx)-D10, px(ty), px(tx)+D10, px(ty));
  fprintf(fw,"%i stroke\n", 1);
  fprintf(fw,"%i %i moveto %i %i lineto\nclosepath\n", px(tx), px(ty)-D10, px(tx), px(ty)+D10);
  fprintf(fw,"%i stroke\n", 1);
  fprintf(fw,"%i %i moveto\n (%s)show\n",px(tx)+4,px(ty)+5,"t");

  /* TODO stuff here: */
  for (i=0; i<n; i++)
  {
    ix[0] = px(x[i]) ;
    iy[0] = px(y[i]) ;

    ix[1] = ix[0] + px(fabs(b[i]));
    iy[1] = iy[0] ;

    ix[2] = ix[1] ;
    iy[2] = iy[1] + px(fabs(h[i]));

    ix[3] = ix[0] ;
    iy[3] = iy[2] ;

    ix[4] = ix[0] ;
    iy[4] = iy[0] ;

    fprintf(fw,"%i setlinewidth\n", 2);
    for (j=0; j<4; j++)
    {
      fprintf(fw,"%i %i moveto %i %i lineto\nclosepath\n", 
          ix[j], 
          iy[j], 
          ix[j+1],
          iy[j+1]);
      fprintf(fw,"%i stroke\n", 1);
    }

    if (b[i] < 0.0) /* hole */
    {
      fprintf(fw,"%i setlinewidth\n", 1);
      fprintf(fw,"%i %i moveto %i %i lineto\nclosepath\n", ix[0], iy[0], ix[2], iy[2]);
      fprintf(fw,"%i stroke\n", 1);
      fprintf(fw,"%i %i moveto %i %i lineto\nclosepath\n", ix[1], iy[1], ix[3], iy[3]);
      fprintf(fw,"%i stroke\n", 1);
    }
  }

  /* Texts: */
  for (i=0; i<10; i++) str[i]='\0'; sprintf(str,"tx = %2.4lf",tx);
  fprintf(fw,"%i %i moveto\n (%s)show\n",DIMS,DIMS+0*D10 - 2*D10,str);
  for (i=0; i<10; i++) str[i]='\0'; sprintf(str,"ty = %2.4lf",ty);
  fprintf(fw,"%i %i moveto\n (%s)show\n",DIMS,DIMS+0*D10 - 4*D10,str);
  for (i=0; i<10; i++) str[i]='\0'; sprintf(str,"A  = %2.4lf",A);
  fprintf(fw,"%i %i moveto\n (%s)show\n",DIMS,DIMS+0*D10 - 6*D10,str);

  for (i=0; i<10; i++) str[i]='\0'; sprintf(str,"Ix = %2.4lf",Ix);
  fprintf(fw,"%i %i moveto\n (%s)show\n",DIMS,DIMS+0*D10 - 10*D10,str);
  for (i=0; i<10; i++) str[i]='\0'; sprintf(str,"Iy = %2.4lf",Iy);
  fprintf(fw,"%i %i moveto\n (%s)show\n",DIMS,DIMS+0*D10 - 12*D10,str);
  for (i=0; i<10; i++) str[i]='\0'; sprintf(str,"Dxy= %2.4lf",Dxy);
  fprintf(fw,"%i %i moveto\n (%s)show\n",DIMS,DIMS+0*D10 - 14*D10,str);
  for (i=0; i<10; i++) str[i]='\0'; sprintf(str,"I1 = %2.4lf",I1);
  fprintf(fw,"%i %i moveto\n (%s)show\n",DIMS,DIMS+0*D10 - 18*D10,str);
  for (i=0; i<10; i++) str[i]='\0'; sprintf(str,"I2 = %2.4lf",I2);
  fprintf(fw,"%i %i moveto\n (%s)show\n",DIMS,DIMS+0*D10 - 20*D10,str);
  for (i=0; i<10; i++) str[i]='\0'; sprintf(str,"Dm = %2.4lf",Dm);
  fprintf(fw,"%i %i moveto\n (%s)show\n",DIMS,DIMS+0*D10 - 22*D10,str);
  for (i=0; i<10; i++) str[i]='\0'; sprintf(str,"phi= %2.4lf",fi);
  fprintf(fw,"%i %i moveto\n (%s)show\n",DIMS,DIMS+0*D10 - 24*D10,str);

  fprintf(fw,"showpage\n");
  return(0);
}


int main(int argc, char *argv[])
{
  read_input(stdin) ;
  compute_t() ;
  compute_I() ;
  compute_I_1_2() ;
  
  get_limits(&x_0, &y_0, &x_1, &y_1);
  draw_ps(stdout, x_0, y_0, x_1, y_1);
  return(0);
}


/* end of i.c */
