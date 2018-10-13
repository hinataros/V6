/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::decomposeEndEffectorAcceleration()
{
  if(debug) DEBUG;

  // cal_dVcBarRef =

  cal_dVmBarRef = Bm.transpose()*fb.cal_dVfb;
}
