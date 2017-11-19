#include "config.hpp"
#include "common.hpp"

MatrixXd RLS::Common::wPInv(MatrixXd A, MatrixXd W)
{
  return W.inverse()*A.transpose()*(A*W.inverse()*A.transpose()).inverse();
}
