/**
   @author Sho Miyahara 2018
*/

#include "quaternion.hpp"

Eigen::Vector3d RLS::Quaternion4d::ddq2dw(const Quaternion4d &q, const Quaternion4d &dq, const Quaternion4d &ddq)
{
  return 2*(q.w*ddq.v - ddq.w*q.v) + 2*(q.v.cross(ddq.v) + dq.v.cross(dq.v));
  // return 2*(q.w*ddq.v - ddq.w*q.v) - (2*(q.v.cross(ddq.v) + dq.v.cross(dq.v)));
}
