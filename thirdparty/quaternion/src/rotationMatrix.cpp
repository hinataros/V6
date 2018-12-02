/**
   @author Sho Miyahara 2018
*/
#include "quaternion.hpp"

Eigen::Matrix3d RLS::Quaternion4d::rotationMatrix()
{
  Eigen::Matrix3d vCross = Eigen::Matrix3d::Zero();

  vCross <<
    0    ,-v(2), v(1),
    v(2) ,    0,-v(0),
    -v(1), v(0),    0;

  return
    (w*w - v.transpose()*v)*Eigen::Matrix3d::Identity()
    + 2*v*v.transpose() + 2*w*vCross;
}
