/**
   @author Sho Miyahara 2018
*/

#include "quaternion.hpp"

Eigen::Vector3d RLS::Quaternion4d::dq2w(const Quaternion4d &q, const Quaternion4d &dq)
{
  return 2*(q.w*dq.v - dq.w*q.v) + 2*q.v.cross(dq.v);
}
