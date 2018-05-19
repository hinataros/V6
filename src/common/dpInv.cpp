/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "common.hpp"

MatrixXd RLS::Common::dpInv(MatrixXd A, MatrixXd dA)
{
  MatrixXd piA = pInv(A);

  return N(A)*dA.transpose()*(A*A.transpose()).inverse() - piA*dA*piA;
}
