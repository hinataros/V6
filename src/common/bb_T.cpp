#include "config.hpp"
#include "common.hpp"

Matrix6d RLS::Common::bb_T(Vector3d r)
{
  Matrix6d bb_T = Matrix6d::Identity();

  bb_T.block(3,0,3,3)  = cross(r).transpose();

  return bb_T;
}
