/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseTranslationZeroTrajectory(double &t)
{
  if(debug) DEBUG;

  rBDes = sequence[baseTranslationTrajectoryNum].rBpreDes + rB0;
  vBDes = Vector3d::Zero();
  dvBDes = Vector3d::Zero();
}
