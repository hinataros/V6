#include "config.hpp"
#include "common.hpp"

VectorXd RLS::Common::arrayd2Vector(int num, double *x)
{
  VectorXd X = VectorXd::Zero(num);

  for(int i(0); i<num; i++)
    X(i) = x[i];

  return X;
}
