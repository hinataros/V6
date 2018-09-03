/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseOrientationZeroTrajectory(double &t)
{
  if(debug) DEBUG;

  xiBDes = xiB;
  dxiBDes = Vector3d::Zero();
  ddxiBDes = Vector3d::Zero();
}
