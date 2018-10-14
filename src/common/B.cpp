/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "common.hpp"

MatrixXd RLS::Common::B(int num, ...)
{
  MatrixXd Bdiag = MatrixXd::Zero(num, num);

  va_list ptr;
  va_start(ptr, num);

  int b=0;
  for(int i=0; i<num; i++){
    Bdiag(i, i) = va_arg(ptr, int);

    if(Bdiag(i, i))
      b++;
  }

  va_end(ptr);

  MatrixXd B = MatrixXd::Zero(num, b);
  int j=0;
  for(int i=0; i<num; i++)
    if(Bdiag(i, i)){
      B.col(j) = Bdiag.col(i);
      j++;
    }

  return B;
}
