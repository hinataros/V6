/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::relativeVelocityMixedMap()
{
  if(debug) DEBUG;

  cal_VcMBarRef = -constraintModel.cal_PcM.transpose()*fb.cal_VMfb;

  cal_VmMBarRef = constraintModel.Bm.transpose()*fb.cal_Vfb - constraintModel.cal_PmM.transpose()*fb.cal_VMfb;
}
