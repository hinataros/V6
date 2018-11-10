/**
   @author Sho Miyahara 2018
*/

#include "quaternion.hpp"

RLS::Quaternion4d RLS::Quaternion4d::Identity()
{
  Quaternion4d q;

  q.w = 1.;
  q.v = Eigen::Vector3d::Zero();

  return q;
}

