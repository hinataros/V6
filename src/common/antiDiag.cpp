/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "common.hpp"

MatrixXd RLS::Common::antiDiag(int num, ...)
{
  MatrixXd antiDiag = MatrixXd::Zero(num, num);
  va_list ptr;

  va_start(ptr, num);

  for(int i=0; i<num; i++)
    antiDiag(i,num-(i+1)) = va_arg(ptr, double);

  va_end(ptr);

  return antiDiag;
}
