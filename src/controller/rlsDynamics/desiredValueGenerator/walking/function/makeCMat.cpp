/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "walkingFunction.hpp"


MatrixXd RLS::WalkingFunction::makeCMat(int n, double a)
{
  MatrixXd C = MatrixXd::Identity(n, n);
  int i, j;
  for(i=0; i<(n-1); i++){
    C(i,i+1) = (i+1)*a;
    for(j=i+2; j<n; j++){
      C(i,j) = C(i, j-1) * j*a;
    }
  }

  return C;
}
