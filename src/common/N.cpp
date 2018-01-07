/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "common.hpp"

MatrixXd RLS::Common::N(MatrixXd A)
{
  return MatrixXd::Identity(A.cols(),A.cols()) - pInv(A)*A;
}

MatrixXd RLS::Common::N(MatrixXd A, MatrixXd W)
{
  return MatrixXd::Identity(A.cols(),A.cols()) - pInv(A,W)*A;
}
