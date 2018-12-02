/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::relativeAccelerationBaseMap()
{
  if(debug) DEBUG;

  cal_dVcBBarRef = -constraintModel.cal_Pc.transpose()*fb.cal_dVBfb;

  cal_dVmBBarRef = constraintModel.Bm.transpose()*fb.cal_dVfb - constraintModel.cal_Pm.transpose()*fb.cal_dVBfb;
}
