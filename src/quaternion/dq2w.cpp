/**
   @author Sho Miyahara 2018
*/

#include "quaternion.hpp"

Eigen::Vector3d RLS::Quaternion4d::dq2w(const Quaternion4d &q, const Quaternion4d &dq)
{
  Eigen::Matrix3d qCross = Eigen::Matrix3d::Zero();

  qCross <<
    0      ,-q.v(2), q.v(1),
    q.v(2) ,      0,-q.v(0),
    -q.v(1), q.v(0),      0;

  return 2*(q.w*dq.v - dq.w*q.v) + 2*qCross*dq.v;
}
