#include "config.hpp"
#include "common.hpp"

MatrixXd RLS::Common::N(MatrixXd A)
{
  return MatrixXd::Identity(A.cols(),A.cols()) - pInv(A)*A;
}
