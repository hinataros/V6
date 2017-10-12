#include "config.hpp"
#include "common.hpp"

MatrixXd RLS::Common::pInv(MatrixXd A)
{
  return A.transpose()*(A*A.transpose()).inverse();
}
