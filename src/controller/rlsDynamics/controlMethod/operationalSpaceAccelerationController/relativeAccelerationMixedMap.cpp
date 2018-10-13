/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::relativeAccelerationMixedMap()
{
  if(debug) DEBUG;

  cal_dVcMBarRef = -cal_PcM.transpose()*fb.cal_dVMfb;

  cal_dVmMBarRef = Bm.transpose()*fb.cal_dVfb - cal_PmM.transpose()*fb.cal_dVMfb;
}
