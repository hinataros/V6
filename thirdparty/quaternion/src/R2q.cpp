/**
   @author Sho Miyahara 2018
*/

#include "quaternion.hpp"

int sign(double x)
{
  return (x>=0) - (x<0);
}

RLS::Quaternion4d RLS::Quaternion4d::R2q(const Eigen::Matrix3d &R)
{
  Quaternion4d q = Zero();

  q.w = 0.5*sqrt(R(0,0) + R(1,1) + R(2,2) + 1);
  q.v <<
    (R(2,1) - R(1,2))/(4*q.w),
    (R(0,2) - R(2,0))/(4*q.w),
    (R(1,0) - R(0,1))/(4*q.w);

  // q.v <<
  //   0.5*sign(R(2,1) - R(1,2))*sqrt( R(0,0) - R(1,1) - R(2,2) + 1),
  //   0.5*sign(R(0,2) - R(2,0))*sqrt(-R(0,0) + R(1,1) - R(2,2) + 1),
  //   0.5*sign(R(1,0) - R(0,1))*sqrt(-R(0,0) - R(1,1) + R(2,2) + 1);

  return q;
}
