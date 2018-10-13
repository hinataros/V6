/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::relativeVelocityBaseMap()
{
  if(debug) DEBUG;

  cal_VcBBarRef = -cal_Pc.transpose()*fb.cal_VBfb;

  cal_VmBBarRef = Bm.transpose()*fb.cal_Vfb - cal_Pm.transpose()*fb.cal_VBfb;
}
