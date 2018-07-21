/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

Matrix6d RLS::RlsDynamics::spatialTransform(Config &config, Info &info, Vector3d r)
{
  if(config.flag.debug) DEBUG;

  Matrix6d bb_T = Matrix6d::Identity();

  bb_T.block(0,3,3,3) = -cross(r);

  return bb_T;
}
