/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::relativeAccelerationMixedMap()
{
  if(debug) DEBUG;

  cal_dVcMBarRef = -constraintModel.mbb_CcM.transpose()*fb.cal_dVMfb;

  cal_dVmMBarRef = constraintModel.Bm.transpose()*fb.cal_dVfb - constraintModel.mbb_CmM.transpose()*fb.cal_dVMfb;
}
