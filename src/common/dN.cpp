/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "common.hpp"

MatrixXd RLS::Common::dN(MatrixXd A, MatrixXd dA)
{
  MatrixXd piA = pInv(A);
  MatrixXd NA = N(A);

  return -NA*dA.transpose()*piA.transpose() - piA*dA*NA;
}
