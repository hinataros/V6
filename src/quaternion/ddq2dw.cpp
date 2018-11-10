/**
   @author Sho Miyahara 2018
*/

#include "quaternion.hpp"

Eigen::Vector3d RLS::Quaternion4d::ddq2dw(const Quaternion4d &q, const Quaternion4d &dq, const Quaternion4d &ddq)
{
  Eigen::Matrix3d qCross = Eigen::Matrix3d::Zero();
  Eigen::Matrix3d dqCross = Eigen::Matrix3d::Zero();

  qCross <<
    0      ,-q.v(2), q.v(1),
    q.v(2) ,      0,-q.v(0),
    -q.v(1), q.v(0),      0;
  dqCross <<
    0       ,-dq.v(2), dq.v(1),
    dq.v(2) ,       0,-dq.v(0),
    -dq.v(1), dq.v(0),       0;

  return 2*(q.w*ddq.v - ddq.w*q.v) + 2*(qCross*ddq.v + dqCross*dq.v);
}
