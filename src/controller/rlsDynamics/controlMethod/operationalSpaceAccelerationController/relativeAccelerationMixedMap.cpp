/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::relativeAccelerationMixedMap()
{
  if(debug) DEBUG;

  cal_dVcMBarRef = -constraintModel.cal_PcM.transpose()*fb.cal_dVMfb;

  cal_dVmMBarRef = constraintModel.Bm.transpose()*fb.cal_dVfb - constraintModel.cal_PmM.transpose()*fb.cal_dVMfb;
}
