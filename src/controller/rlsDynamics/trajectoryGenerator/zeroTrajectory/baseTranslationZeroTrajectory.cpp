/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseTranslationZeroTrajectory(double &t)
{
  if(debug) DEBUG;

  rBDes = rB;
  vBDes = Vector3d::Zero();
  dvBDes = Vector3d::Zero();
}
