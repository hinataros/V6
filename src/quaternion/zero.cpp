/**
   @author Sho Miyahara 2018
*/

#include "quaternion.hpp"

RLS::Quaternion4d RLS::Quaternion4d::Zero()
{
  Quaternion4d q;

  q.w = 0.;
  q.v = Eigen::Vector3d::Zero();

  return q;
}

