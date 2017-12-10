#include "config.hpp"
#include "common.hpp"

MatrixXd RLS::Common::diag(int num, ...)
{
  MatrixXd Diag = MatrixXd::Zero(num, num);
  va_list ptr;

  va_start(ptr, num);

  for(int i=0; i<num; i++)
    Diag(i,i) = va_arg(ptr, double);

  va_end(ptr);

  return Diag;
}
