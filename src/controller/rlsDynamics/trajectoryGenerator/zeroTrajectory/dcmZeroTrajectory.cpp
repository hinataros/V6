/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::dcmZeroTrajectory(double &t)
{
  if(debug) DEBUG;

  rXDes = sequence[dcmTrajectoryNum].rXpreDes + rX0;
  drXDes = Vector3d::Zero();
}
