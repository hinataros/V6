/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "common.hpp"

double RLS::Common::math(string type, int num, ...)
{
  va_list ptr;
  double sum = 0.;

  va_start(ptr, num);

  for(int i=0; i<num; i++)
    sum += va_arg(ptr, double);

  va_end(ptr);

  if(type=="s")
    return sin(sum);

  else if(type=="c")
    return cos(sum);

  else
    cout << "math error..." << endl;

  return -1;
}
