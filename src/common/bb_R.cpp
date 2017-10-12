#include "config.hpp"
#include "common.hpp"

Matrix6d RLS::Common::bb_R(string axis, double th)
{
  Matrix6d bb_R = Matrix6d::Zero();

  bb_R.block(0,0,3,3) = bb_R.block(3,3,3,3) = R(axis, th);

  return bb_R;
}
