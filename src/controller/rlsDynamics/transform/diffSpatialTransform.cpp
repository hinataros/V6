/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

Matrix6d RLS::RlsDynamics::diffSpatialTransform(Config &config, Info &info, Vector3d dr)
{
  if(config.flag.debug) DEBUG;

  Matrix6d bb_dT = Matrix6d::Zero();

  bb_dT.block(0,3,3,3) = -cross(dr);

  return bb_dT;
}
