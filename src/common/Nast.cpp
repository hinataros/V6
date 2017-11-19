#include "config.hpp"
#include "common.hpp"

MatrixXd RLS::Common::Nast(MatrixXd A)
{
  return MatrixXd::Identity(A.cols(),A.cols()) - A.transpose()*pInv(A).transpose();
}

MatrixXd RLS::Common::Nast(MatrixXd A, MatrixXd W)
{
  return MatrixXd::Identity(A.cols(),A.cols()) - A.transpose()*wPInv(A,W).transpose();
}
