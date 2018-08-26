/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::comZeroTrajectory(double &t)
{
  if(debug) DEBUG;

  rCDes = sequence[comTrajectoryNum].rCpreDes + rC0;
  vCDes = Vector3d::Zero();
  dvCDes = Vector3d::Zero();
}
