/**
   @author Sho Miyahara 2018
*/
#include "quaternion.hpp"

RLS::Quaternion4d RLS::Quaternion4d::inverse()
{
  RLS::Quaternion4d re = Zero();

  re.w = w;
  re.v = -v; // 共役

  return re;
}
