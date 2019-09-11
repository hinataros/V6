/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::relativeVelocityBaseMap()
{
  if(debug) DEBUG;

  cal_VcBBarRef = -constraintModel.mbb_Cc.transpose()*fb.cal_VBfb;

  cal_VmBBarRef = constraintModel.Bm.transpose()*fb.cal_Vfb - constraintModel.mbb_Cm.transpose()*fb.cal_VBfb;
}
