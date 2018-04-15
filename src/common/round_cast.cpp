/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "common.hpp"

int RLS::Common::round_cast(double x, int num)
{
  if(static_cast<int>(x*pow(10, num+1))%10<5)
    return static_cast<int>(x*pow(10, num));
  else
    return static_cast<int>(x*pow(10, num))+1;
}
