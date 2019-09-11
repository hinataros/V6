/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::relativeVelocityMixedMap()
{
  if(debug) DEBUG;

  cal_VcMBarRef = -constraintModel.mbb_CcM.transpose()*fb.cal_VMfb;

  cal_VmMBarRef = constraintModel.Bm.transpose()*fb.cal_Vfb - constraintModel.mbb_CmM.transpose()*fb.cal_VMfb;
}
