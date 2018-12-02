/**
   @author Sho Miyahara 2018
*/

#include "quaternion.hpp"

RLS::Quaternion4d RLS::Quaternion4d::xi2q(const Eigen::Vector3d &xi)
{
  Quaternion4d qz, qy, qx;

  qz = qy = qx = Zero();

  qz.w = cos(xi(0)/2);
  qz.v(2) = sin(xi(0)/2);

  qy.w = cos(xi(1)/2);
  qy.v(1) = sin(xi(1)/2);

  qx.w = cos(xi(2)/2);
  qx.v(0) = sin(xi(2)/2);

  return qz*qy*qx;
}
