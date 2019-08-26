/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::relativeAccelerationCentroidalMap()
{
  if(debug) DEBUG;

  cal_dVcCBarRef = -constraintModel.cal_PcM.transpose()*fb.cal_dVCfb;

  cal_dVmCBarRef = constraintModel.Bm.transpose()*fb.cal_dVfb - constraintModel.cal_PmM.transpose()*fb.cal_dVCfb;
}
