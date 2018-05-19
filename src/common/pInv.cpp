/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "common.hpp"

MatrixXd RLS::Common::pInv(MatrixXd A)
{
  return A.transpose()*(A*A.transpose()).inverse();
}

MatrixXd RLS::Common::pInv(MatrixXd A, MatrixXd W)
{
  return W.inverse()*A.transpose()*(A*W.inverse()*A.transpose()).inverse();
}

