/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::comZeroTrajectory(double &t)
{
  if(debug) DEBUG;

  rCDes = rC;
  vCDes = Vector3d::Zero();
  dvCDes = Vector3d::Zero();
}
