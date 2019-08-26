#include "config.hpp"
#include "common.hpp"

#include "costFunctionQPpp.hpp"


namespace RLS{ // staticクラスメンバ変数は別に定義し直さないといけないらしい
  MatrixXd costFunctionQPpp::Go, costFunctionQPpp::CEo, costFunctionQPpp::CIo;
  VectorXd costFunctionQPpp::go, costFunctionQPpp::ceo, costFunctionQPpp::cio;
}

VectorXd a2v(int num, double *x)
{
  VectorXd X = VectorXd::Zero(num);

  for(int i(0); i<num; i++)
    X(i) = x[i];

  return X;
}


void RLS::costFunctionQPpp::objection(int nparam, int j, double *x, double *fj, void *cd)
{
  if(CFSQP_DEBUG) DEBUG;

  VectorXd X = a2v(nparam, x);
  VectorXd ans = VectorXd::Zero(1);

  ans = X.transpose() * Go * X + go.transpose() * X;
  // ans = X.transpose() * Go * X + 2.*go.transpose() * X; // ??
  *fj = ans(0);

  return;
}

void RLS::costFunctionQPpp::gradientObjection(int nparam, int j, double *x, double *gradfj, void (*dummy)(int, int, double*, double*, void*), void *cd)
{
  if(CFSQP_DEBUG) DEBUG;

  VectorXd X = a2v(nparam, x);
  for(int i(0); i<nparam; i++)
    gradfj[i] = 0;

  for(int i(0); i<nparam; i++) {
    gradfj[i] += 2*Go(i,i) * X(i) + go(i);
    for(int k(0); k<nparam; k++){
      if(k!=i)
      gradfj[i] += Go(k, i) * X(k) + Go(i, k) * X(k);
    }
  }

  return;
}


void RLS::costFunctionQPpp::constraint(int nparam, int j, double *x, double *gj, void *cd)
{
  if(CFSQP_DEBUG) DEBUG;

  VectorXd X = a2v(nparam, x);
  VectorXd ans = VectorXd::Zero(1);

  if(j <= CIo.rows()){
    ans = - CIo.row(j-1) * X;
    *gj = ans(0) + cio(j-1);  //<= 0
  }
  else {
    ans = CEo.row(j-CIo.rows()-1) * X;
    *gj = ans(0) - ceo(j-CIo.rows()-1); //=0
  }

  return;
}

void RLS::costFunctionQPpp::gradientConstraint(int nparam, int j, double *x, double *gradgj, void (*dummy)(int, int, double*, double*, void*), void *cd)
{
  if(CFSQP_DEBUG) DEBUG;

  if(j <= CIo.rows()){
    for(int i(0); i<nparam; i++)
      gradgj[i] = CIo(j-1, i);
  }
  else {
    for(int i(0); i<nparam; i++)
      gradgj[i] = CEo(j-CIo.rows()-1, i);
  }

  return;
}
