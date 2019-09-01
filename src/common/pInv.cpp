/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "common.hpp"

MatrixXd RLS::Common::pInv(MatrixXd A)
{
  if(A.rows() < A.cols()) // right pseudo
    return A.transpose()*(A*A.transpose()).inverse();

  if(A.rows() > A.cols()) // left pseudo
    return (A.transpose()*A).inverse()*A.transpose();

  // square
  return A.inverse();
}

MatrixXd RLS::Common::pInv(MatrixXd A, MatrixXd W)
{
  return W.inverse()*A.transpose()*(A*W.inverse()*A.transpose()).inverse();
}
