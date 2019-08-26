#include "config.hpp"
#include "common.hpp"

#include "cfsqp.hpp"


RLS::CFSQP::CFSQP()
{
  mode=111;
  if(CFSQP_DEBUG)
    iprint=1;
  else
    iprint=0;
  miter=500;
  bigbnd=1.e10;
  eps=1.e-8;
  epsneq=0.e0;
  udelta=0.e0;
  nf=1;
  ncsrl=ncsrn=nfsr=mesh_pts[0]=0;
}

RLS::CFSQP::~CFSQP()
{
  free(bl);
  free(bu);
  free(x);
  free(f);
  free(g);
  free(lambda);
}


void RLS::CFSQP::configuration()
{
  bl=(double *)calloc(nparam,sizeof(double));
  bu=(double *)calloc(nparam,sizeof(double));
  x=(double *)calloc(nparam,sizeof(double));
  f=(double *)calloc(nf,sizeof(double));
  g=(double *)calloc(nineq+neq,sizeof(double));
  lambda=(double *)calloc(nineq+neq+nf+nparam,sizeof(double));

  for(int i(0); i<nparam; i++){
    bl[i] = -bigbnd;
    bu[i] = bigbnd;
  }
}
