/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::externalWrenchZeroTrajectory(double &t)
{
  if(debug) DEBUG;

  cal_FextDes = Vector6d::Zero();
}
