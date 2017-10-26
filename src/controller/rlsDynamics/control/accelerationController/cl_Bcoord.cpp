#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::cl_Bcoord(Config &config, Model &model)
{
  if(config.flag.debug) DEBUG;

  cal_dVcBarRef = -cal_Pc.transpose()*cal_dVBRef;
  ddthcRef = pInv(cal_Jc)*cal_dVcBarRef;

  cal_dVmBarRef = Bm.transpose()*cal_dVRef - cal_Pm.transpose()*cal_dVBRef;
  cal_dVmTildeRef = cal_dVmBarRef - cal_Jm*pInv(cal_Jc)*cal_dVcBarRef;
  cal_JmBar = cal_Jm*N(cal_Jc);
  ddthmRef = pInv(cal_JmBar)*cal_dVmTildeRef;

  hc = cal_dPc.transpose()*cal_VB + cal_dJc*model.all.dth;
  hm = -dBm.transpose()*cal_V + cal_dPm.transpose()*cal_VB + cal_dJm*model.all.dth;
  h = pInv(cal_Jc)*hc + pInv(cal_JmBar)*(hm - cal_Jm*pInv(cal_Jc)*hc);

  ddthRef = ddthcRef + ddthmRef - h;
}
