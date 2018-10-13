/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::relativeAccelerationBaseMap()
{
  if(debug) DEBUG;

  cal_dVcBBarRef = -cal_Pc.transpose()*fb.cal_dVBfb;

  cal_dVmBBarRef = Bm.transpose()*fb.cal_dVfb - cal_Pm.transpose()*fb.cal_dVBfb;
}
