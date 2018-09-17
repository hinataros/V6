/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::dcmZeroTrajectory(const double &t)
{
  if(debug) DEBUG;

  rXDes = rX;
  drXDes = Vector3d::Zero();
}
