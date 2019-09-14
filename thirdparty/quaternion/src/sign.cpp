/**
   @author Sho Miyahara 2018
*/

#include "quaternion.hpp"


int RLS::Quaternion4d::sign(double x)
{
  return (x>=0) - (x<0);
}
