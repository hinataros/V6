#include "config.hpp"
#include "common.hpp"
#include "model.hpp"

#include "postureGenerator.hpp"


void RLS::postureGenerator::objection(int nparam, int j, double *x, double *fj, void *cd)
{
  if(CFSQP_DEBUG) DEBUG;



  return;
}

void RLS::postureGenerator::gradientObjection(int nparam, int j, double *x, double *gradfj, void (*dummy)(int, int, double*, double*, void*), void *cd)
{
  if(CFSQP_DEBUG) DEBUG;

  // VectorXd X = a2v(nparam, x);
  // for(int i(0); i<nparam; i++)
  //   gradfj[i] = 0;
  //
  // for(int i(0); i<nparam; i++) {
  //   gradfj[i] += 2*Go(i,i) * X(i) + go(i);
  //   for(int k(0); k<nparam; k++){
  //     if(k!=i)
  //     gradfj[i] += Go(k, i) * X(k) + Go(i, k) * X(k);
  //   }
  // }

  return;
}


void RLS::postureGenerator::constraint(int nparam, int j, double *x, double *gj, void *cd)
{
  if(CFSQP_DEBUG) DEBUG;

  VectorXd rC = calcCoM(x);


  return;
}

void RLS::postureGenerator::gradientConstraint(int nparam, int j, double *x, double *gradgj, void (*dummy)(int, int, double*, double*, void*), void *cd)
{
  if(CFSQP_DEBUG) DEBUG;



  return;
}
