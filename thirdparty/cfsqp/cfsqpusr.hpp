/*************************************************************/
/*  CFSQP - Header file to be included in user's main        */
/*          program.                                         */
/*************************************************************/

#ifndef _CFSQP_HPP_
#define _CFSQP_HPP_

#include <cstdio>
#include <cmath>
#include <cstdlib>

#ifndef __STDC__
#ifdef apollo
extern char *calloc();
#else
#include <malloc.h>
#endif
#endif

#define TRUE 1
#define FALSE 0

namespace cfsqpspace {

  /* Declare and initialize user-accessible flag indicating    */
  /* whether x sent to user functions has been changed within  */
  /* CFSQP.				 		     */

  /**************************************************************/
  /*     Gradients - Finite Difference                          */
  /**************************************************************/

#ifdef __STDC__
  void    grobfd(int,int,double *,double *,void (*)(int,int,
                                                    double *,double *,void *),void *);
  void    grcnfd(int,int,double *,double *,void (*)(int,int,
                                                    double *,double *,void *),void *);
#else
  void    grobfd();
  void    grcnfd();
#endif

  /**************************************************************/
  /*     Prototype for CFSQP -   	                              */
  /**************************************************************/

#ifdef __STDC__
  void    cfsqp(int,int,int,int,int,int,int,int,int,int *,int,int,
                int,int *,double,double,double,double,double *,
                double *,double *,double *,double *,double *,
                void (*)(int,int,double *,double *,void *),
                void (*)(int,int,double *,double *,void *),
                void (*)(int,int,double *,double *,
                         void (*)(int,int,double *,double *,void *),void *),
                void (*)(int,int,double *,double *,
                         void (*)(int,int,double *,double *,void *),void *),
                void *);
#else
  void    cfsqp();
#endif

}

#endif
